El socket en sistemas Unix y Mac OS son vistos como archivos a los cuales se les asocia un file descriptor (un número no negativo para identificar cuál socket es). A estos se les asocian una dirección de red (puede ser IP en caso de que se utilice ese protocolo) y un puerto por el cual escuchan cualquier solicitud.

Por tanto, los pasos a la hora de iniciar un servidor serían los siguientes:

1. Escucha por conexiones (recibe el número de puerto en el que va a escuchar por parámetro) esto está en el [TcpServer](./network/TcpServer.cpp).

Para esto debe primero debe Buscar direcciones de red disponibles, esto lo hace porque nuestro socket aún no tiene una dirección desde la cual escuchar, por lo tanto la función getaddrinfo() nos da esas direcciones de red disponibles de acuerdo a nuestras necesidades (osea, si usamos IPv4 o IPv6, si es TCP o UDP, si el protocolo de red es IP, ICMP, …).

Una vez tenemos estas direcciones, buscamos cual de estas nos permite abrir un socket ya que al crear un socket este necesita por parámetro si es TCP o UDP, IPv4 o IPv6, IP o ICMP… Estos datos los tomamos de esas direcciones que logramos obtener.

En caso de que se lograra abrir, utilizamos el método bind para asociar el socket con esa direcciń de red y con el puerto en el que va a escuchar.

Ahora debe permitir al socket escuchar por conexiones con el método listen()

2. Empezar a aceptar conexiones cuando estas lleguen, esto se puede hacer con un while true para manejar todas las conexiones que vengan y que el servidor no se detenga hasta que no se lance una excepción o que uno mismo le haga ctr + c o algo similar.

While true {
	Aceptar solicitud de conexión ()
}

Entonces, para aceptar una solicitud de conexión debemos crear un socket para comunicarnos con el otro peer (podemos verlo como un Socket del cliente). Este socket tendrá algunos atributos esenciales:

* Un buffer input: por el cual recibe los datos del cliente
* Un buffer output: por el cual le envía datos al cliente
* El file descriptor asociado a este socket
* La dirección IP del peer que está del otro lado, del lado del cliente

Una vez creado el Socket, aceptamos la solicitud de conexión almacenando la dirección IP del cliente en nuestro atributo creado para esto y utilizando el file descriptor de nuestro Socket de escucha para conectar al cliente con el socket que teníamos escuchando desde el paso 1.
Al aceptar la conexión, obtenemos un file descriptor asociado al Socket del cliente, entonces le hacemos un set a ese socket.
Cuando la conexión es aceptada, entones ya se inicia el proceso de encolar los sockets para que los HttpHandlerConnections se encarguen de este trabajo. (Esta sería la parte que hicimos en paralela)

3. Cuando la conexión es aceptada, entones ya se inicia el proceso de encolar los sockets para que los HttpHandlerConnections se encarguen de este trabajo. (Esta sería la parte que hicimos en paralela)
