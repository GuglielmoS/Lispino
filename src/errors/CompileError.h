#ifndef LISPINO_ERRORS_COMPILEERROR_H_
#define LISPINO_ERRORS_COMPILEERROR_H_

#include <exception>

namespace Lispino {

namespace Errors {

class CompileError : public std::exception {};

}

}

#endif // LISPINO_ERRORS_COMPILEERROR_H_
