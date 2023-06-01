// Copyright © 2023 Camilo Suárez Sandí

#ifndef ANNOTATION_HPP_
#define ANNOTATION_HPP_

#include <string>

class Annotation {
 private:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

  std::string user;
  int id;
  std::string information;

  // Constructor
  Annotation() = default;

  // Destructor
  ~Annotation() = default;

  // Copy Constructor
  Annotation(const Annotation& other) = delete;

  // Copy Assignment Operator
  Annotation& operator=(const Annotation& other) = delete;

  // Move Constructor
  Annotation(Annotation&& other) = default;

  // Move Assignment Operator
  Annotation& operator=(Annotation&& other) = default;

 public:
  const std::string& getUser() const;
  int getID() const;
  const std::string& getInformation() const;

  std::string getInsertIntoQuery() const;

  // Inner Class
  class Builder;
};

class Annotation::Builder {
 private:
  Annotation object;

 public:
  Builder& setUser(const std::string& value);
  Builder& setID(int value);
  Builder& setInformation(const std::string& value);

  Annotation build();
};

#endif  // ANNOTATION_HPP_
