#ifndef LISPINO_INTERPRETER_H_
#define LISPINO_INTERPRETER_H_

#include <string>

namespace Lispino {

	const std::string LIB_DIR = "lib";
	const std::string STDLIB_FILE = "std.scm";
	const std::string TESTLIB_FILE = "unittest.scm";

    class Interpreter {
    
        std::string humanTime(double time_spent);
    
        public:

			void init();
            int repl(bool verbose=false);
            int execute(std::string filename);

    };
};

#endif // LISPINO_INTERPRETER_H_
