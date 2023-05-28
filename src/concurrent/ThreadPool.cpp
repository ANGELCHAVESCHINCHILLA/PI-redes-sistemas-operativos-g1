// Copyright © 2023 Camilo Suárez Sandí

#include "ThreadPool.hpp"

ThreadPool::ThreadPool() : stop(false) {
  //
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->stop = true;
  }

  // Releases the threads
  this->condition_variable.notify_all();

  // Joins the threads
  for (std::thread& worker_thread : this->workers) {
    worker_thread.join();
  }
}

void ThreadPool::start(size_t count) {
  this->count = count;

  for (size_t index = 0; index < this->count; index++) {
    // Create the thread
    this->workers.push_back(std::thread([this]() {
      while (true) {
        std::function<void(void)> task;

        {
          std::unique_lock<std::mutex> lock(this->mutex);

          // Wait for a signal to execute a task
          while (this->tasks.empty()) {
            this->condition_variable.wait(lock);
          }

          // Stop condition
          if (this->stop && this->tasks.empty()) {
            return;
          }

          // Pop a task from the queue
          task = this->tasks.front();
          this->tasks.pop();
        }

        // Execute the task
        task();
      }
    }));
  }
}

void ThreadPool::execute(std::function<void(void)> task) {
  {
    // Add a task to the queue
    std::lock_guard<std::mutex> lock(this->mutex);
    this->tasks.push(task);
  }

  // Send a signal to execute a task
  this->condition_variable.notify_one();
}
