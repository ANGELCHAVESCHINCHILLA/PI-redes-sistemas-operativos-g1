//

# include "jwt.hpp"

#include <iostream>

JWT::JWT(const std::string& secretKey)
  : secretKey(secretKey) {
  this->generateJWT();
}

void JWT::generateJWT() {
  // Header
  this->encodeHeader = JWT::base64Encode(this->stringHeader());

  // Payload (claims)
  // std::string payload = "{\"sub\":\"\' + subject + \'\"}" + subject + "\"}";
  this->encodeClaims = base64Encode(this->stringClaims());

  // Signature
  this->dataToSign = this->encodeHeader + '.' + this->encodeClaims;

  unsigned int digestLength;
  unsigned char* hmacDigest = HMAC(EVP_sha256(), this->secretKey.c_str()
    , this->secretKey.length(),
    reinterpret_cast<const unsigned char*>(this->dataToSign.data())
    , this->dataToSign.length(), nullptr, &digestLength);

  std::string uncodeSignature(hmacDigest, hmacDigest + digestLength);

  this->signature = base64Encode(uncodeSignature);
}

// "{\"alg\":\"HS256\",\"typ\":\"JWT\"}"
std::string JWT::stringHeader() const {
  std::string stringHeaders;
  this->stringMaps(this->headers, stringHeaders);
  return stringHeaders;
}

// "{\"sub\":\"\' + subject + \'\"}" + username + "\"}";
std::string JWT::stringClaims() const {
  std::string stringClaims;
  this->stringMaps(this->claims, stringClaims);
  return stringClaims;
}

void JWT::stringMaps(const std::map<std::string, std::string>& maps
    , std::string& result) {
  result = "{";
  std::map<std::string, std::string>::const_iterator it;
  for (it = maps.cbegin(); it != maps.cend(); ++it) {
    if (it != maps.cbegin()) {
      result += ",";
    }
    const std::string& key = it->first;
    result += "\"" + key + "\": "; 
    const std::string& value = it->second;
    result += "\'" + value + "\""; 
  }
  result += "}";
}

void JWT::addHeader(const std::string& key, const std::string& value) {
  this->headers.insert({key, value});
}

void JWT::addClaim(const std::string& key, const std::string& value) {
  this->claims.insert({key, value});
}

std::string JWT::base64Encode(const std::string& data) {
  BIO* bio;
  BIO* b64;
  BUF_MEM* bufferPointer;

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  BIO_write(bio, data.data(), data.length());
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPointer);

  std::string result(bufferPointer->data, bufferPointer->length);
  BIO_free_all(bio);

  return result;
}

bool JWT::verifyJWT(const std::string& token, const std::string& secretKey) {
  std::vector<std::string> parts;
  std::istringstream iss(token);
  std::string part;

  while (std::getline(iss, part, '.')) {
      parts.push_back(part);
  }

  if (parts.size() != 3) {
    // El token no tiene el formato correcto
    // std::cout << "Formato incorrecto" << std::endl;
    return false;
  }

  std::string dataToSign2 = parts[0] + '.' + parts[1];
  std::string receivedSignature = parts[2];

  unsigned int digestLength;
  unsigned char* hmacDigest = HMAC(EVP_sha256(), secretKey.c_str(), secretKey.length(),
                                    reinterpret_cast<const unsigned char*>(dataToSign2.data()), dataToSign.length(),
                                    nullptr, &digestLength);


  std::string calculatedSignature(hmacDigest, hmacDigest + digestLength);

  calculatedSignature = JWT::base64Encode(calculatedSignature);

  // std::cout << "CALCULADA: " << calculatedSignature << std::endl;

  // std::cout << "RECBIDA: " << receivedSignature << std::endl;

  return (receivedSignature == calculatedSignature);
}

std::string JWT::generateRandomKey(unsigned int keySize) {
  std::vector<unsigned char> key(keySize);

  if (RAND_bytes(key.data(), keySize) != 1) {
      throw std::runtime_error("Error al generar la clave aleatoria");
  }

  std::string secretKey(key.begin(), key.end());

  return secretKey;
}

// std::vector<unsigned char> generateRandomKey(unsigned int keySize, std::string& copia);

// std::string base64Encode(const std::string& data) {
//     BIO *bio, *b64;
//     BUF_MEM *bufferPtr;

//     b64 = BIO_new(BIO_f_base64());
//     bio = BIO_new(BIO_s_mem());
//     bio = BIO_push(b64, bio);

//     BIO_write(bio, data.data(), data.length());
//     BIO_flush(bio);
//     BIO_get_mem_ptr(bio, &bufferPtr);

//     std::string result(bufferPtr->data, bufferPtr->length);
//     BIO_free_all(bio);

//     return result;
// }

// std::string generateJWT(const std::string& secretKey, const std::string& subject) {
//     // Header
//     std::string header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
//     header = base64Encode(header);

//     // Payload (claims)
//     std::string payload = "{\"sub\":\"\' + subject + \'\"}" + subject + "\"}";
//     payload = base64Encode(payload);

//     // Signature
//     std::string dataToSign = header + '.' + payload;

//     unsigned int digestLength;
//     unsigned char* hmacDigest = HMAC(EVP_sha256(), secretKey.c_str(), secretKey.length(),
//                                      reinterpret_cast<const unsigned char*>(dataToSign.data()), dataToSign.length(),
//                                      nullptr, &digestLength);

//     std::string signature(hmacDigest, hmacDigest + digestLength);

//     signature = base64Encode(signature);

//     // JWT
//     std::string jwt = dataToSign + '.' + signature;

//     return jwt;
// }

// bool verifyJWT(const std::string& token, const std::string& secretKey) {
//     std::vector<std::string> parts;
//     std::istringstream iss(token);
//     std::string part;
//     while (std::getline(iss, part, '.')) {
//         parts.push_back(part);
//     }

//     if (parts.size() != 3) {
//         return false; // El token no tiene el formato correcto
//     }

//     std::string dataToSign = parts[0] + '.' + parts[1];
//     std::string receivedSignature = parts[2];

//     unsigned int digestLength;
//     unsigned char* hmacDigest = HMAC(EVP_sha256(), secretKey.c_str(), secretKey.length(),
//                                      reinterpret_cast<const unsigned char*>(dataToSign.data()), dataToSign.length(),
//                                      nullptr, &digestLength);

//     unsigned char* tmp = hmacDigest;
//     unsigned count = 0;
//     std::cout << "Signature calculada 1: ";
//     while(count < digestLength) {
//         std::cout << *tmp;
//         tmp++;
//         ++count;
//     }
//     std::cout << std::endl;


//     std::string calculatedSignature(hmacDigest, hmacDigest + digestLength);

//     calculatedSignature = base64Encode(calculatedSignature);

//     std::cout << "Signature calculada 2 : " << calculatedSignature << std::endl;

//     std::cout << "Signature recibida 1 : " << receivedSignature << std::endl;

//     return (receivedSignature == calculatedSignature);
// }


// int main() {
//     unsigned int keySize = 32; // Longitud de la clave en bytes (256 bits)

//     std::string copia;

//     std::vector<unsigned char> secretKey = generateRandomKey(keySize, copia);

//     // Imprimir la clave secreta generada
//     std::cout << "clave secreta generada: ";
//     for (const auto& byte : secretKey) {
//         printf("%02x", byte);
//     }
//     printf("\n");
//     std::cout << "Copia generada" << copia << std::endl;

//     std::string subject = "user123";

//     std::string token = generateJWT(copia, subject);

//     std::cout << "Token JWT: " << token << std::endl;

//     if (verifyJWT(token, copia)) {
//         std::cout << "Token JWT válido" << std::endl;
//     } else {
//         std::cout << "Token JWT inválido" << std::endl;
//     }

//     return 0;
// }

// std::vector<unsigned char> generateRandomKey(unsigned int keySize, std::string& copia) {
//     std::vector<unsigned char> key(keySize);

//     if (RAND_bytes(key.data(), keySize) != 1) {
//         throw std::runtime_error("Error al generar la clave aleatoria");
//     }

//     std::string copia2(key.begin(), key.end());

//     copia = copia2;

//     return key;
// }
