#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../../../src/net/TcpClient.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc == 4) {
      TcpClient client;
      Socket& socket = client.connect(argv[1], argv[2]);
      std::ostringstream output;

      output << "GET " << argv[3] << " HTTP/1.0\r\n";
      output << "Host: " << argv[1] << "\r\n\r\n";
      socket.send(output.str());

      // std::string line;
      // while (socket.readLine(line)) {
      //   std::cout << line << std::endl;
      // }
    } else {
      std::cout << "usage: client SERVER PORT URI" << std::endl;
    }
  } catch (std::runtime_error& error) {
    std::cerr << error.what() << std::endl;
  }
}

// using namespace std;

// int main() {
//   int resultado = 0;
//   int s = 0, n = 0;
//   char datos[256];
//   struct sockaddr_in ipServidor;

//   memset(datos, '0', sizeof(datos));

//   if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//     cout << "Error de creación de socket" << endl;
//     resultado = 1;
//   } else {
//     ipServidor.sin_family = AF_INET;
//     ipServidor.sin_port = htons(8080);
//     ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
//     int error = 0;
//     if ((error = connect(s, (struct sockaddr *)&ipServidor,
//                          sizeof(ipServidor))) < 0) {
//       cout << endl << "Error de conexión por IP o puerto" << endl;
//       cout << "error was: " << error << endl;
//       fprintf(stderr, "connect: %s\n", strerror(errno));
//       resultado = 2;
//     } else {
//       string msj;
//       std::cin >> msj;

//       msj.copy(datos, msj.size() + 1);
//       write(s, datos, strlen(datos));
//       if (n < 0) {
//         cout << endl << "Error de lectura" << endl;
//       }
//     }
//   }

//   return resultado;
// }