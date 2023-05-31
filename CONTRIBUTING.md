# Proyecto Integrador

# Dependencias

Para compilar el programa es necesario tener las siguientes librerías:

* OpenSSL
    * Instalar en Ubuntu: `sudo apt install openssl libssl-dev`
    * Incluir el header: `<openssl/ssl.h>`
    * Flag para el linker: `-lcrypto`

* SQLite
    * Instalar en Ubuntu: `sudo apt install sqlite3 libsqlite3-dev`
    * Incluir el header: `<sqlite3.h>`
    * Flag para el linker: `-lsqlite3`

* JsonCpp
    * Instalar en Ubuntu: `sudo apt install libjsoncpp-dev`
    * Incluir el header: `<json/json.hpp>`
    * Flag para el linker: `-ljsoncpp`

Ejecutar `make install` para installar todas las dependencias.
