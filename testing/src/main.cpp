#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
  int resultado = 0;
  int s = 0, n = 0;
  char datos[256];
  struct sockaddr_in ipServidor;

  memset(datos, '0', sizeof(datos));

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "Error de creación de socket" << endl;
    resultado = 1;
  } else {
    ipServidor.sin_family = AF_INET;
    ipServidor.sin_port = htons(8000);
    ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    int error = 0;
    if ((error = connect(s, (struct sockaddr *)&ipServidor,
                         sizeof(ipServidor))) < 0) {
      cout << endl << "Error de conexión por IP o puerto" << endl;
      cout << "error was: " << error << endl;
      fprintf(stderr, "connect: %s\n", strerror(errno));
      resultado = 2;
    } else {
      string msj;
      std::cin >> msj;

      msj.copy(datos, msj.size() + 1);
      write(s, datos, strlen(datos));
      if (n < 0) {
        cout << endl << "Error de lectura" << endl;
      }
    }
  }

  return resultado;
}