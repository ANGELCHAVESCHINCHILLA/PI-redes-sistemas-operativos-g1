// EJEMPLO DE SOCKETS - SOCKETS LINUX - ricardo.gang@ucr.ac.cr

// OJO:
// g++ server.cpp -o server y luego ./server en 'Console'
// g++ client.cpp -o client y luego ./client en 'Shell'

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
  char datos[256];
  int socketServidor = 0, conexion = 0;
  struct sockaddr_in ip;
  socketServidor = socket(AF_INET, SOCK_STREAM, 0);

  memset(&ip, '0', sizeof(ip));
  memset(datos, '0', sizeof(datos));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(1337);

  bind(socketServidor, (struct sockaddr *)&ip, sizeof(ip));
  int listen_error = listen(socketServidor, 20);
  // std::cout << "Listen error:" + to_string(listen_error) << std::endl;

  int msjs = 0;
  sleep(1);
  struct sockaddr_storage ipRemoto;
  socklen_t l = sizeof(ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  cout << endl << "[SERVIDOR ESCUCHANDO]" << endl;
  while (msjs < 5000) {
    // std::cout << "1" << std::endl;
    conexion = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);
    // std::cout << "2" << std::endl;
    if (conexion != -1) {
      cout << "[MENSAJE RECIBIDO] #" << ++msjs << endl;
      struct sockaddr_in *s = (struct sockaddr_in *)&ipRemoto;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
      cout << " IP Remoto: " << strIpRemoto << endl;
      int n = 0;
      n = read(conexion, datos, sizeof(datos));
      if (n > 0) {
        datos[n] = '\0';
        cout << endl << string(datos) << endl;
      } else {
        std::cout << "error de lectura";
      }

      string msj = "El servidor ha recibido " + to_string(msjs) + " mensajes.";
      msj.copy(datos, msj.size() + 1);

      // write(conexion, datos, strlen(datos));

      close(conexion);
    } else {
      cout << endl << "Connection closed" << endl;
    }
    close(conexion);
    sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;
  return 0;
}