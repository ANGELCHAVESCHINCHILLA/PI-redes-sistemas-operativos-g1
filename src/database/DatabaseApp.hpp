// Copyright © Ignacio Robles Mayorga

#ifndef DATABASE_APP_HPP_
#define DATABASE_APP_HPP_

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "./Database.hpp"
#include "../http/HttpApp.hpp"
#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"
#include "../url/URL.hpp"
// TODO: include the requestHandler interface

class DatabaseApp : public HttpApp {
  DISABLE_COPY(DatabaseApp);

 protected: 
  // vector de requestHandlers

 public:
  // Default constructor
  DatabaseApp();

  // Default destructor
  ~DatabaseApp();

  Database& database = Database::getInstance("database.bd");

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;

  /**
   * @brief consults the vacation balance a user has
   * 
   * @param user the user whose vacation balance will be returned
   * @return std::string the user's vacation balance
   */
  std::string consultVacationBalanceByUser(const std::string user) const;

  /**
   * @brief consults the salary information of a certain user
   * 
   * @param user the user whose salaty info will be returned
   * @return std::vector<std::vector<std::string>> a list of all salaries a given user has had
   */
  std::vector<std::vector<std::string>> consultSalaryByUser(const std::string user) const;

  /**
   * @brief consults all annotations to the record of a user
   * 
   * @param user the user whose annotions will be consulted
   * @return std::vector<std::string> the list of all annotations made to the 
   record of the user
   */
  std::vector<std::string> consultRecordAnnotationsByUser(const std::string user) const;

  /**
   * @brief consults the name and the enterprise of a user
   * 
   * @param user the user whose name and enterprise will be consulted
   * @return std::vector<std::string> the vector containing the name and the enterprise of the user
   */
  std::vector<std::string> consultNameAndEnterpriseByUser(const std::string user) const;

  /**
   * @brief consults all requests made by a user
   * 
   * @param user the user whose requests will be consulted
   * @return std::vector<std::vector<std::string>> a vector containing vectors 
    (the requests) that contain strings of the requests data
   */
  std::vector<std::vector<std::string>> consultRequestsMadeByUser(const std::string user) const;
  

  /**
   * @brief it makes a request, creating a new row in the HRRequest table
   * 
   * @param user the user who makes the request
   * @param requestType the request's type
   * @param information the information associated to that request
   * @param vacationDays the amount of vacation days asked (in case its a vacation request)
   * @param vacationStartDate the date where the vacations start (in case its a vacation request)
   * @param vacationEndDate the date where the vacations end (in case its a vacation request)
   * @return true if the inserting of the row was successfull
   * @return false if it wasn't possible to insert the row
   */
  bool makeRequest(const std::string user, const std::string requestType, const std::string information, const int vacationDays = 0, const int vacationStartDate = 0, const int vacationEndDate = 0) const;

  /**
   * @brief Get the Requests Made in a certain Area
   * 
   * @param area the area in which the requests were made
   * @return std::vector<std::vector<std::string>> the list of requests made in that area
   */
  std::vector<std::vector<std::string>> getRequestsMadeByArea(const std::string area) const;

  /**
   * @brief it changes the state of the request to either approved or denied
   * 
   * @param requestID the id of the request to be checked
   * @param state the new state of the request (approved or denied)
   * @param feedback the reason of the state given
   * @return true if it was able to edit the state of the request
   * @return false if it was not able to edit the state of the request
   */
  bool checkRequest(const int requestID, const std::string state, const std::string feedback) const;

  /**
   * @brief Get the Request By ID
   * 
   * @param requestID the id of the request to be obtained
   * @return std::vector<std::string> the request of id requestID
   */
  std::vector<std::string> getRequestByID(const int requestID) const;

 private:

  void initHandlers();
  
};

#endif  // DATABASE_APP_HPP_
