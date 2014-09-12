#include "Display.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../VM.h"

namespace Lispino {

    namespace Builtins {

        Object* Display::apply(std::vector<Object*>& args, Environment& env) {
            if (args.size() == 0)
                throw std::runtime_error("display: wrong number of arguments!");

            std::stringstream buf;
            for (unsigned int i = 0; i < args.size(); i++) {
                std::string currentValue;
                Object *currentObject = args[i]->eval(env);

                if (currentObject->isString())
                    currentValue = static_cast<String*>(currentObject)->getValue();
                else
                    currentValue = currentObject->toString();

                std::cout << currentValue;
                buf << currentValue;
            }

            return VM::getAllocator().createString(buf.str());
        }
    }
}
