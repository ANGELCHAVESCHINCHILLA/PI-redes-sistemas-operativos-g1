# File System Web App

Consider all URL on this list going to have *'localhost'* as address and *8080* as port, but it
could change depending on where server is hosted.

## Requests

### Add User

#### Request

* Method: POST
* URL: /auth/user or /adduser
* Body:
```json
{
  "username": "AngelSuare",
  "password": "YdntnTQSY4nmWkM",
  "salt": "G9cB0Lh16HEp862",
  "type": 5
}
```

#### Response:

* If successful: 200
* If unsuccessful: 400

---

### Permissions and User Type

#### Request

* Method: GET
* URL: /permissions?username=AngelSuare

#### Response:

* If successful: The user type, an integer from 1 to 5
* Body: `0`
* If unsuccessful: `-1`

---

### Authenticate User

#### Request

* Method: POST
* URL: /auth or /login
* Body:
```json
{
  "username": "AngelSuare",
  "password": "NStt6+CwRVxk1gVCQGr0m88zUZ"
}
```

#### Response:

* If successful: 200
* If unsuccessful: 400

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

---

### Remove User

#### Request

* Method: DELETE
* URL: /auth/user
* Body:
```json
{
  "username": "AngelSuare"
}
```

#### Response:

* If successful: 200
* If unsuccessful: 401

---

### Edit User

#### Request

* Method: PUT
* URL: /auth/user
* Body:
```json
{
  "username": "AngelSuare"
}
```

#### Response:

* If successful: 200
* If unsuccessful: 401
