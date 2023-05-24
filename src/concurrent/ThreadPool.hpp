// Copyright © 2023 Camilo Suárez Sandí

#ifndef THREAD_POOL_HPP_
#define THREAD_POOL_HPP_

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/**
 * @brief Stores a vector of threads to reuse and execute tasks. The threads
 * wait to execute the tasks in a queue.
 *
 */
class ThreadPool {
 private:
  /**
   * @brief The amount of threads.
   *
   */
  size_t count;

  /**
   * @brief A stop condition.
   *
   */
  bool stop;

  /**
   * @brief A vector that stores the threads.
   *
   */
  std::vector<std::thread> workers;

  /**
   * @brief A queue that stores the tasks.
   *
   */
  std::queue<std::function<void(void)>> tasks;

  /**
   * @brief A mutex for the queue and the condition variable.
   *
   */
  std::mutex mutex;

  /**
   * @brief A condition variable to wait for the threads.
   *
   */
  std::condition_variable condition_variable;

 public:
  /**
   * @brief Default constructor.
   *
   */
  explicit ThreadPool();

  /**
   * @brief Destructor. Joins the worker threads.
   *
   */
  ~ThreadPool();

  // Copy Constructor
  ThreadPool(const ThreadPool& other) = delete;

  // Copy Assignment Operator
  ThreadPool& operator=(const ThreadPool& other) = delete;

  // Move Constructor
  ThreadPool(ThreadPool&& other) = delete;

  // Move Assignment Operator
  ThreadPool& operator=(ThreadPool&& other) = delete;

  /**
   * @brief Creates the worker threads. Only call once.
   *
   * @param count The amount of threads.
   */
  void start(size_t count);

  /**
   * @brief Adds a task to the queue.
   *
   * @param task A closure.
   */
  void execute(std::function<void(void)> task);
};

#endif  // THREAD_POOL_HPP_
