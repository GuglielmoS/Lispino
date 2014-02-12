#ifndef __BUILTIN_DISPLAY_H__
#define __BUILTIN_DISPLAY_H__

#include "BuiltinFunction.h"
#include "../VM.h"

#include <iostream>
#include <sstream>
#include <string>

namespace Lispino {
    
    class BuiltinDisplay : public BuiltinFunction {
        
        public:

            Object* apply(std::vector<Object*>& args) {
                if (args.size() == 0)
                    throw std::runtime_error("display: wrong number of arguments!");
            
                std::stringstream buf;
                for (unsigned int i = 0; i < args.size(); i++) {
                    std::string currentValue;

                    if (args[i]->isString())
                        currentValue = static_cast<String*>(args[i])->getValue();
                    else
                        currentValue = args[i]->toString();

                    std::cout << currentValue;
                    buf << currentValue;
                }

                return VM::getAllocator().createString(buf.str());
            }

    };
};

#endif // _BUILTIN_ADD_H__
