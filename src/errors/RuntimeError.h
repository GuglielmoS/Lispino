#ifndef LISPINO_ERRORS_RUNTIMEERROR_H_
#define LISPINO_ERRORS_RUNTIMEERROR_H_

#include <exception>

namespace Lispino {

namespace Errors {

class RuntimeError : public std::exception {};

}

}

#endif // LISPINO_ERRORS_RUNTIMEERROR_H_
