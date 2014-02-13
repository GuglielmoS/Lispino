#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>

namespace Lispino {

    class Interpreter {
    
        static std::string humanTime(double time_spent);
    
        public:

            static int repl(bool verbose=false);
            static int execute(std::string filename);

    };
};

#endif // __INTERPRETER_H__
