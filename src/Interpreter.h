#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>

namespace Lispino {

    class Interpreter {
    
        static std::string humanTime(double time_spent);
    
        public:

            static int repl();

    };
};

#endif // __INTERPRETER_H__
