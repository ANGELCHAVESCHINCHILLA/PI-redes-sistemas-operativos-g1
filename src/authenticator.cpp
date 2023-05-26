#include "authenticator.hpp"
#include "hash.hpp"
#include "iostream"

Authenticator::Authenticator() {
    this->fs = new FS();
}
Authenticator::Authenticator(FS* fs) {
    this->fs = fs;
}

Authenticator::~Authenticator() {
    delete this->fs;
}
bool Authenticator::authUser(const std::string& username, const std::string& hashKey) {
   /** TODO(any): do this*/
}

