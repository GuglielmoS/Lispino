#include "List.h"
#include "VM.h"

#include <sstream>

using namespace Lispino;

std::string List::toStringHelper(bool parentheses) const {
    std::stringstream buf;
    if (parentheses)
        buf << "(";

    if (!head->isNil())
        buf << head->toString();

    if (!tail->isNil()) {
        if (tail->isList() || tail->isQuote() || tail->isDefine() || tail->isLambda())
            buf << " ";
        else
            buf << " . ";

        if (tail->isList())
            buf << static_cast<List*>(tail)->toStringHelper(false);
        else
            buf << tail->toString();
    }

    if (parentheses)
        buf << ")";

    return buf.str();   
} 

void inspect(List *lst, int level=0) {
    std::string indent = "";
    for (int i = 0; i < level; i++) indent += " ";

    if (!lst->isNil()) {
        std::cout << indent << "-> ";
        if (!lst->getFirst()->isNil()) {
            if (lst->getFirst()->isList()) {
                std::cout << std::endl;
                inspect(static_cast<List*>(lst->getFirst()), level+1);
            }
            else
                std::cout << indent << " " << lst->getFirst()->toString();

            std::cout << std::endl;
        }

        std::cout << indent << "-> ";
        if (!lst->getRest()->isNil()) {
            if (lst->getRest()->isList()) {
                std::cout << std::endl;
                inspect(static_cast<List*>(lst->getRest()), level+1);
            }
            else
                std::cout << indent << " " << lst->getRest()->toString();

            std::cout << std::endl;
        }
    }
}

Object* List::eval(Environment& env) {
    if (head->isNil())
        return VM::getAllocator().createNil();
    
    // extract the arguments if needed
    if (!cachedArgs) {
        cachedArgs = true;

        if (tail != nullptr) {
            List *current = nullptr;

            if (tail->isList()) {
                current = static_cast<List*>(tail);

                while (!current->isNil()) {
                    if (current->head != nullptr) {
                        args.push_back(current->head);
                        if (!current->tail->isNil()) {
                            if (current->tail->isList())
                                current = static_cast<List*>(current->tail);
                            else {
                                args.push_back(current->tail);
                                break;
                            }
                        } else break;
                    } else break;
                }
            }
            else if (!tail->isNil()) {
                args.push_back(tail);
            }
        }
    }

    // evaluate the arguments
    std::vector<Object*> evaluatedArgs;
    for (unsigned int i = 0; i < args.size(); i++)
        evaluatedArgs.push_back(args[i]->eval(env));

    Object *op = head->eval(env);
    if (op->isBuiltinFunction())
        return static_cast<BuiltinFunction*>(op)->apply(evaluatedArgs);
    else if (op->isLambda())
        return static_cast<Closure*>(op->eval(env))->apply(evaluatedArgs);
    else if (op->isClosure())
        return static_cast<Closure*>(op)->apply(evaluatedArgs);
    else 
        throw std::runtime_error("Invalid function call, the operator cannot be used: " + op->toString());
}
