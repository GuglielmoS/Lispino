#ifndef LISPINO_ERRORS_RUNTIMEERROR_H_
#define LISPINO_ERRORS_RUNTIMEERROR_H_

#include <string>
#include <exception>

namespace Lispino {

namespace Errors {

class RuntimeError : public std::exception {
 public:
  RuntimeError() : message("Generic runtime error") {}

  RuntimeError(const std::string&& message) : message(message) {}

  std::string getMessage() const {
    return message;
  }

 private:
  std::string message;
};

}

}

#endif // LISPINO_ERRORS_RUNTIMEERROR_H_
