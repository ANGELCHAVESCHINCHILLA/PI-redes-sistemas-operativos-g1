# Database Web App

Consider all URLs on this list are going to have *'localhost'* as address and *8080* as port, but it could change depending on where server is hosted.

## Request List:

### MakeRequest
**RequestType: POST**

URL: http://localhost:8080/makeRequest

Body: Simple text in format
```json
{
  "user": "CamiloSua",
  "request_type": "Vacation",
  "information": "Deseo pedir vacaciones por favor",
  "area": "San Jose",
  "vacation_days": 14,
  "vacation_start_date": 10623,
  "vacation_end_date": 150623
}
```

#### **status code 200:**
If request was made successfully by makeRequest method
Response body: "Post success"

#### **status code 400**:
If request was not made successfully by makeRequest method
Response body: "Post fail"

If request was not made successfully because of invalid json values
Response body: "Json values error"

If request was not made successfully because of invalid json format
Response body: "Json format error"

---

### CheckRequest
**RequestType: POST**

URL: http://localhost:8080/checkRequest

Body: Simple text in format
```json
{
  "request_id": 5,
  "state": "1",
  "feedback": "Su solicitud queda aprobada."
}
```

#### **status code 200:**
If request was checked successfully by checkRequest method
Response body: "Post success"

#### **status code 400:**
If request was not checked successfully by checkRequest method
Response body: "Post fail"

If request was not checked successfully because of invalid json values
Response body: "Json values error"

If request was not checked successfully because of invalid json format
Response body: "Json format error"

---

### ConsultAnnotationsByUser
**RequestType: GET**

URL: http://localhost:8080/consultAnnotationsByUser?user='user'

Replace literal 'user' for real user username, like AngelSuare. Username must not go with quotes.

#### **status code 200:**
If the annotations of the user were found by consultAnnotationsByUser method

Response body:
```json
{
  "name": "Miranda Jop",
  "company_name": "Amazon",
  "annotations": {
    "annotation1": "Miranda chocó el carro en el parqueo de la compañía el día 22/3/23",
    "annotation2": "Miranda se robó una computadora el día 23/3/23",
  }
}
```

#### **status code 400:**
If user was not found by consultAnnotationsByUser method
Response body: "User not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

---

### ConsultRequestsByArea
**RequestType: GET**

URL: http://localhost:8080/consultRequestsByArea?area='area'

Replace literal 'area' for real area, like "San Jose". Area must not go with quotes.

#### **status code 200:**
If the requests of the area were found by consultRequestsByArea method

Response body:
```json
{
  "request1": {
    "user": "Juan",
    "ID": 3,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi constancia salarial?",
    "feedback": "   ",
    "request_type": "ConstanciaSalarial",
    "vacation_days": 0,
    "vacation_start_date": 0,
    "vacation_end_date": 0,
    "area": "Cartago"
  },
  "request2": {
    "user": "Gabriel",
    "ID": 7,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi 13 dias de vacaciones?",
    "feedback": "   ",
    "request_type": "Vacaciones",
    "vacation_days": 13,
    "vacation_start_date": 11223,
    "vacation_end_date": 151223,
    "area": "San Jose"
  },
}
```

#### **status code 400:**
If area was not found by consultRequestsByArea method
Response body: "Area not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

---

### ConsultRequestsByID
**RequestType: GET**

URL: http://localhost:8080/consultRequestsByID?id='id'

Replace literal 'id' for real id, like 37. Id must not go with quotes.

#### **status code 200:**
If the requests of the id were found by consultRequestsByID method

Response body:
```json
{
  "user": "Juan",
  "ID": 3,
  "state": 0,
  "padding": "          ",
  "information": "Hola, por favor puedo tener mi constancia salarial?",
  "feedback": "   ",
  "request_type": "ConstanciaSalarial",
  "vacation_days": 0,
  "vacation_start_date": 0,
  "vacation_end_date": 0,
  "area": "Cartago"
}
```

#### **status code 400:**
If id was not found by consultRequestsByID method
Response body: "Id not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

If id entered is not an integer
Response body: "Param given was not an integer"

---

### ConsultRequestsByUser
**RequestType: GET**

URL: http://localhost:8080/consultRequestsByUser?user='user'

Replace literal 'user' for real user username, like "angelSuare". User must not go with quotes.

#### **status code 200:**
If the requests of the user were found by consultRequestsByUser method

Response body:
```json
{
  "request1": {
    "user": "Juan",
    "ID": 3,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi constancia salarial?",
    "feedback": "   ",
    "request_type": "ConstanciaSalarial",
    "vacation_days": 0,
    "vacation_start_date": 0,
    "vacation_end_date": 0,
    "area": "Cartago"
  },
  "request2": {
    "user": "Juan",
    "ID": 7,
    "state": 0,
    "padding": "          ",
    "information": "Hola, por favor puedo tener mi 13 dias de vacaciones?",
    "feedback": "   ",
    "request_type": "Vacaciones",
    "vacation_days": 13,
    "vacation_start_date": 11223,
    "vacation_end_date": 151223,
    "area": "Cartago"
  },
}
```

#### **status code 400:**
If user was not found by consultRequestsByUser method
Response body: "User not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

---

### ConsultSalaryByUser
**RequestType: GET**

URL: http://localhost:8080/consultSalaryByUser?user='user'

Replace literal 'user' for real user username, like "angelSuare". User must not go with quotes.

#### **status code 200:**
If the salaries of the user were found by consultSalaryByUser method

Response body:
```json
{
  "name": "Carlos Montoya",
  "company_name": "Apple",
  "salaries": {
    "salary1": {
      "gross_salary": 2000,
      "net_salary": 3000,
      "salary_start_date": 230323
    },
    "salary2": {
      "gross_salary": 3000,
      "net_salary": 4000,
      "salary_start_date": 230523
    },
  }
}
```

#### **status code 400:**
If user was not found by consultRequestsByUser method
Response body: "User not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

---

### ConsultVacationBalanceByUser
**RequestType: GET**

URL: http://localhost:8080/consultVacationBalanceByUser?user='user'

Replace literal 'user' for real user username, like "angelSuare". User must not go with quotes.

#### **status code 200:**
If the vacation balance of the user was found by consultVacationBalanceByUser method

Response body:
```json
{
  "vacation_balance": 23
}
```

#### **status code 400:**
If user was not found by consultRequestsByUser method
Response body: "User not found"

If request url has invalid syntax after '?' char
Response body: "Error in the url given"

---

### GetPersonalData

#### Request
* Method: GET
* URL: /data/personal_data
* Body:
```json
{
  "user": "abc"
}
```

#### Response
* If successful: 200
* Body:
```json
{
  "user": "abc",
  "employee_name": "A B C",
  "job_name": "A B C",
  "company_name": "A B C",
  "email": "a@b.c",
  "phone_number": 123
}
```
* If unsuccessful: 401

---

### AddPersonalData

#### Request
* Method: POST
* URL: /data/personal_data
* Body:
```json
{
  "user": "abc",
  "employee_name": "A B C",
  "job_name": "A B C",
  "company_name": "A B C",
  "email": "a@b.c",
  "phone_number": 123
}
```

#### Response
* If successful: 200
* If unsuccessful: 401

---

### RemovePersonalData

#### Request
* Method: DELETE
* URL: /data/personal_data
* Body:
```json
{
  "user": "abc"
}
```

#### Response
* If successful: 200
* If unsuccessful: 401

---

### EditPersonalData

#### Request
* Method: PUT
* URL: /data/personal_data
* Body:
```json
{
  "user": "abc",
  "employee_name": "A B C",
  "job_name": "A B C",
  "company_name": "A B C",
  "email": "a@b.c",
  "phone_number": 123
}
```

#### Response
* If successful: 200
* If unsuccessful: 401

---

### GetJobData

#### Request
* Method: GET
* URL: /data/job_data
* Body:
```json
{
  "user": "abc"
}
```

#### Response
* If successful: 200
* Body:
```json
{
  "user": "abc",
  "vacation_days": 1,
  "gross_salary": 1.0,
  "net_salary": 1.0,
  "salary_start_date": 1000,
  "salary_end_date": 1000
}
```
* If unsuccessful: 401

---

### AddJobData

#### Request
* Method: POST
* URL: /data/job_data
* Body:
```json
{
  "user": "abc",
  "vacation_days": 1,
  "gross_salary": 1.0,
  "net_salary": 1.0,
  "salary_start_date": 1000,
  "salary_end_date": 1000
}
```

#### Response
* If successful: 200
* If unsuccessful: 401

---

### RemoveJobData

#### Request
* Method: DELETE
* URL: /data/job_data
* Body:
```json
{
  "user": "abc"
}
```

#### Response
* If successful: 200
* If unsuccessful: 401

---

### EditJobData

#### Request
* Method: PUT
* URL: /data/job_data
* Body:
```json
{
  "user": "abc",
  "vacation_days": 1,
  "gross_salary": 1.0,
  "net_salary": 1.0,
  "salary_start_date": 1000,
  "salary_end_date": 1000
}
```

#### Response
* If successful: 200
* If unsuccessful: 401
