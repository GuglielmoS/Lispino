#ifndef LISPINO_ERRORS_COMPILEERROR_H_
#define LISPINO_ERRORS_COMPILEERROR_H_

#include <string>
#include <exception>

namespace Lispino {

namespace Errors {

class CompileError : public std::exception {
 public:
  CompileError(const std::string&& message) : message(message) {}

  std::string getMessage() const {
    return message;
  }

 private:
  std::string message;
};

}

}

#endif // LISPINO_ERRORS_COMPILEERROR_H_
