# File System Web App

Consider all URL on this list going to have *'localhost'* as address and *8080* as port, but it
could change depending on where server is hosted.

## Request List:

### Login
**RequestType: POST**

URL: http://localhost:8080/login

Body: Simple text in format
```json
{
  "username": "AngelSuare",
  "password": "NStt6+CwRVxk1gVCQGr0m88zUZ"
}
```

Response: 'Successfully' in body with CodeStatus with value 200 if authenticated successfully. 
'Failed' and CodeStatus 400 if not.

---

### AddUser
**RequestType: POST**

URL: http://localhost:8080/adduser

Body: Simple text in format
```json
{
  "username": "Testing123",
  "password": "NStt6+CwRVxk1gVCQGr0m33zUZ",
  "type": 5
}
```

Response: Successfully in body with CodeStatus with value 200 if user added successfully.
Failed and CodeStatus 400 if not.

---

### Permissions/Type
**RequestType: GET**

URL: http://localhost:8080/permissions?username='username'

Replace literal 'username' for real user username, as AngelSuare. Username must not going with quotes

Response: An integer larger or equal than 0 if successfully. -1 if not. The integer in the response is the user type.

---

### Salt

#### Request

* Method: GET
* URL: /auth/salt
* Body:
```json
{
  "username": "AngelSuare"
}
```

#### Response:

* If successful: 200
* Body:
```json
{
  "salt": "wPbzAL6WVGJEzUh5"
}
```
* If unsuccessful: 401
