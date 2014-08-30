#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>

namespace Lispino {

	const std::string LIB_DIR = "lib";
	const std::string STDLIB_FILE = "std.scm";

    class Interpreter {
    
        std::string humanTime(double time_spent);
    
        public:

			void init();
            int repl(bool verbose=false);
            int execute(std::string filename);

    };
};

#endif // __INTERPRETER_H__
