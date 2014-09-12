#ifndef LISPINO_BUILTIN_DISPLAY_H_
#define LISPINO_BUILTIN_DISPLAY_H_

#include <iostream>
#include <sstream>
#include <string>

#include "BuiltinFunction.h"
#include "../VM.h"

namespace Lispino {
    
    class BuiltinDisplay : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args, Environment& env) {
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

    };
};

#endif // LISPINO_BUILTIN_ADD_H_
