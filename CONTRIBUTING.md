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
    * Incluir el header: `<jsoncpp/json/json.hpp>`
    * Flag para el linker: `-ljsoncpp`

* GoogleTest
    * Instalar en Ubuntu: `sudo apt install libgtest-dev`
    * Incluir el header: `#include <gtest/gtest.h>`
    * Flags para el linker: `-lgtest -lgtest_main`

Ejecutar `make install` para installar todas las dependencias.

# Configuración

Existen 3 aplicaciones en este sistema:

| Aplicación | Descripción                                                        |
| ---------- | ------------------------------------------------------------------ |
| web        | Servidor Web para ver las páginas web.                             |
| fs         | Servidor File System para la creación y autenticación de usuarios. |
| db         | Servidor Database para guardar los datos de Recursos Humanos.      |

Editar el archivo `configuration.json`.

Editar el atributo `apps` para ejecutar diferentes aplicaciones.

Editar el atributo `servers` para configurar las direcciones y los puertos de los diferentes servidores de las aplicaciones.

Ejemplo:

```json
{
    "apps": [
        "web",
        "fs",
        "db"
    ],
    "servers": {
        "web": {
            "address": "192.168.1.11",
            "port": 8000
        },
        "fs": {
            "address": "192.168.1.12",
            "port": 8000
        },
        "db": {
            "address": "192.168.1.13",
            "port": 8000
        },
        "default": {
            "address": "127.0.0.1",
            "port": 8000
        }
    }
}
```

# Ejecución

## En un dispositivo

Para ejecutar en un dispositivo compilar el programa y ejecutar en diferentes terminales de comando en las que las aplicaciones tienen la misma dirección y diferentes puertos. 

Puede usar los archivos de configuración de prueba ya creados en el directorio `test` para hacer pruebas.

Ejemplo:

Terminal 1:
```
make run ARGS="test/configuration_web.json"
```
Terminal 2:
```
make run ARGS="test/configuration_fs.json"
```
Terminal 3:
```
make run ARGS="test/configuration_db.json"
```

## En varios dispositivos

Para ejecutar en varios dispositivos compilar el programa y ejecutar en cada uno de los dispositivos, es necesario configurar los servidores con las direcciones de los otros dispositivos.

Ejemplo:

Dispositivo A (192.168.1.11):
```json
{
    "apps": [
        "web"
    ],
    "servers": {
        "fs": {
            "address": "192.168.1.12",
            "port": 8000
        },
        "db": {
            "address": "192.168.1.13",
            "port": 8000
        }
    }
}
```

Dispositivo B (192.168.1.12):
```json
{
    "apps": [
        "fs"
    ],
    "servers": {
        "web": {
            "address": "192.168.1.11",
            "port": 8000
        },
        "db": {
            "address": "192.168.1.13",
            "port": 8000
        }
    }
}
```

Dispositivo C (192.168.1.13):
```json
{
    "apps": [
        "db"
    ],
    "servers": {
        "web": {
            "address": "192.168.1.11",
            "port": 8000
        },
        "fs": {
            "address": "192.168.1.12",
            "port": 8000
        }
    }
}
```
