#ifndef LISPINO_ERRORS_COMPILEERROR_H_
#define LISPINO_ERRORS_COMPILEERROR_H_

#include <string>
#include <sstream>
#include <exception>

#include "../SourceCodePosition.h"

namespace Lispino {

namespace Errors {

class CompileError : public std::exception {
 public:

  CompileError(const std::string&& message, const SourceCodePosition& position) {
    buildMessage(message, position);
  }

  CompileError(const std::string&& message, const SourceCodePosition&& position) {
    buildMessage(message, position);
  }

  std::string getMessage() const {
    return message;
  }

 private:
  std::string message;

  void buildMessage(const std::string& message, const SourceCodePosition& position) {
    std::stringstream buf;
    buf << position.getFilename() << ":"
        << position.getLine() << ":"
        << position.getColumn() << ": "
        << message;
    this->message = buf.str();
  }
};

}

}

#endif // LISPINO_ERRORS_COMPILEERROR_H_
