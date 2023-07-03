# Manual de usuario

Este documento ofrece una guía completa para poder ejecutar el sistema en diferentes terminales de comando o en diferentes dispositivos. Además explica las funcionalidades de las pantallas más significativas del sitio web.

## 1. Instalación

### 1.1. Requerimientos mínimos de Hardware

* Procesador: Core i3  
* Memoria: 2GB de RAM  
* Almacenamiento: 1MB  

### 1.2 Requerimientos de Software

* Sistema operativo: Distribución de Linux  
* El compilador GCC 12.2  
* La herramienta Make
* Dependencias adicionales (ver sección **1.3 Instalación de dependencias**)

### 1.3 Instalación de dependencias

Abra una terminal y ubíquese en la carpeta del proyecto, después proceda a ejecutar el comando `make install` el cuál instalará las siguientes dependencias:

* python3
* python3-pip
* cpplint
* Las especificados en la variable `DEPENDENCIES` del archivo [Makefile](../Makefile)

## 2. Ejecución

### 2.1 Archivos de configuración

Antes de mostrar ejemplos de ejecución, es importante entender la funcionalidad de los archivos de configuración ubicados en la carpeta [test](../test/), tomaremos como ejemplo el archivo [configuration_web.json](../test/configuration_web.json) que contiene lo siguiente:

```json
{
    "apps": [
        "web"
    ],
    "port": 8080,
    "servers": {
        "web": {
            "address": "127.0.0.1",
            "port": 8001
        },
        "fs": {
            "address": "127.0.0.1",
            "port": 8002
        },
        "db": {
            "address": "127.0.0.1",
            "port": 8003
        },
        "default": {
            "address": "127.0.0.1",
            "port": 8000
        }
    }
}
```

1. La propiedad `apps` indica cuál servidor será configurado por este archivo, en este caso configurará el servidor web.
2. La propiedad `servers` contiene características de este servidor y de los demás servidores:

    a. Propiedad `web`: el `address` (para este ejemplo) será la dirección IP del `localhost` ya que el servidor web será el que corra en el dispocitivo actual. El `port` indica el puerto en que estará escuchando el servidor web.

    b. Propiedad `fs`: el `address` será la dirección IP en que el servidor del FileSystem estará ejecutándose y el `port` indica el puerto en que el servidor del FileSystem estará escuchando por conexiones.

    c. Propiedad `db`: Representa los mismo que la propiedad `fs` pero para el servidor de DataBase


### 2.2 En un dispositivo

Si desea ejecutar el sistema en un solo dispositivo, primero debe tener en claro que el servidor web, el servidor de base de datos y el servidor de filesystem escuchan por conexiones en distintos puertos, por lo tanto se ofrece archvivos de configuración donde puede indicar el puerto en que desea que cada servidor escuche por conexiones, los pasos a seguir son los siguientes:

1. Configure los archivos de configuración ubicados en la carpeta [test](../test/):

Cada archivo de configuración especifica la dirección IP y el puerto en que cada servidor escuchará por conexiones, para el ejemplo de un solo dispotivo las direcciones IP siempre serán `127.0.0.1` para indicar que el servidor corre en el *localhost*. Puede modificar los puertos en que escuchan los servidores, tome en cuenta que estas modificaciones tendrá que hacerlas en los 3 archivos de configuración para que los servidores puedan comunicarse entre si.

Un ejmplo de cómo se verían los archivos de configuración para la ejecución en un sólo dispositivo es el siguiente:

Archivo [configuration_web](../test/configuration_web.json):

```json
{
    "apps": [
        "web"
    ],
    "port": 8080,
    "servers": {
        "web": {
            "address": "127.0.0.1",
            "port": 8001
        },
        "fs": {
            "address": "127.0.0.1",
            "port": 8002
        },
        "db": {
            "address": "127.0.0.1",
            "port": 8003
        },
        "default": {
            "address": "127.0.0.1",
            "port": 8000
        }
    }
}
```

Archivo [configuration_db](../test/configuration_db.json):

```json
{
    "apps": [
        "db"
    ],
    "port": 8080,
    "servers": {
        "web": {
            "address": "127.0.0.1",
            "port": 8001
        },
        "fs": {
            "address": "127.0.0.1",
            "port": 8002
        },
        "db": {
            "address": "127.0.0.1",
            "port": 8003
        },
        "default": {
            "address": "127.0.0.1",
            "port": 8000
        }
    }
}
```

Archivo [configuration_fs](../test/configuration_fs.json):

```json
{
    "apps": [
        "fs"
    ],
    "port": 8080,
    "servers": {
        "web": {
            "address": "127.0.0.1",
            "port": 8001
        },
        "fs": {
            "address": "127.0.0.1",
            "port": 8002
        },
        "db": {
            "address": "127.0.0.1",
            "port": 8003
        },
        "default": {
            "address": "127.0.0.1",
            "port": 8000
        }
    }
}
```


1. Abra 3 terminales ubicadas en el directorio del proyecto, cada una de estas ejecutará un servidor distinto.

2. Ejecute los siguientes comandos dependiendo de la terminal:

Terminal 1:

`make run ARGS="test/configuration_web.json"`

Terminal 2:

`make run ARGS="test/configuration_fs.json"`

Terminal 3:

`make run ARGS="test/configuration_db.json"`

3. Abra el navegador web de su preferencia y escriba la URI `http://127.0.0.1:8001/`, de esta forma podrá hacer uso de las funcionalidades del sistema las cuales son explicadas en la sección **3. Guía de funcionalidades** de este documento.


### 2.3 En varios dispositivos

Para ejecutar en varios dispositivos, compilar el programa y ejecutar en cada uno de los dispositivos, es necesario configurar los servidores con las direcciones de los otros dispositivos.

### Ejemplo

Dispositivo A con dirección IP `192.168.1.11`:
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

Dispositivo B con dirección IP `192.168.1.12`:
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

Dispositivo C con dirección IP `192.168.1.13`:

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



## 3. Guía de funcionalidades

### 3.1 Login
