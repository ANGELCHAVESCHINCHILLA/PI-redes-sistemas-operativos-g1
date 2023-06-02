// 

#include <vector>
#include <map>
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

  std::map<std::string, std::string> headers;

  std::string encodeHeader;

  std::map<std::string, std::string> claims;

  std::string encodeClaims;

  std::string signature;

  std::string secretKey;

 public:
  JWT(const std::string& secretKey/*, const std::string& claims
        , const std::string& header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}"*/);
 public:
  void generateJWT();

  bool verifyJWT(const std::string& token, const std::string& secretKey);
  
  static std::string generateRandomKey(unsigned int keySize);

  inline std::string toString() const { return this->dataToSign + '.'
    + this->signature; }

  void addHeader(const std::string& key, const std::string& value);

  void addClaim(const std::string& key, const std::string& value);

  std::string stringHeader() const;
  std::string stringClaims() const;

 private:
  static void stringMaps(const std::map<std::string, std::string>& maps
    , std::string& result);

  std::string base64Encode(const std::string& data);
};