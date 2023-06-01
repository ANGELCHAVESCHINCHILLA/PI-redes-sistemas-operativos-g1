// 

#include <vector>
#include <algorithm>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include <openssl/rand.h>
#include <openssl/buffer.h>

#include "../common/common.hpp"

class JWT {
  DISABLE_COPY(JWT);

 private:
  std::string dataToSign;

  std::string header;

  std::string payload;

  std::string signature;

  std::string secretKey;

 public:
  JWT(const std::string& secretKey, const std::string& claims
        , const std::string& header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}");
 public:
  bool verifyJWT(const std::string& token, const std::string& secretKey);
  
  static std::string generateRandomKey(unsigned int keySize);

  inline std::string toString() const { return this->dataToSign + '.'
    + this->signature; }

 private:
  void generateJWT();

  std::string base64Encode(const std::string& data);

};