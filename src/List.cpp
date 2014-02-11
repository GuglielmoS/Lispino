#include "List.h"
#include "VM.h"

#include <sstream>

using namespace Lispino;

std::string List::toStringHelper(bool parentheses) const {
    std::stringstream buf;
    if (parentheses)
        buf << "(";

    if (head != nullptr)
        buf << head->toString();

    if (tail != nullptr) {
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

    if (lst != nullptr) {
        std::cout << indent << "-> ";
        if (lst->getFirst() != nullptr) {
            if (lst->getFirst()->isList()) {
                std::cout << std::endl;
                inspect(static_cast<List*>(lst->getFirst()), level+1);
            }
            else
                std::cout << indent << " " << lst->getFirst()->toString();

            std::cout << std::endl;
        }

        std::cout << indent << "-> ";
        if (lst->getRest() != nullptr) {
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

std::vector<Object*> List::extractArguments(Environment& env) {
    std::vector<Object*> args;

    if (tail != nullptr) {
        List *current = nullptr;

        if (tail->isList())
            current = static_cast<List*>(tail);
        else {
            args.push_back(tail->eval(env));
            return args;
        }

        while (current != nullptr) {
            if (current->head != nullptr) {
                args.push_back(current->head->eval(env));
                if (current->tail != nullptr) {
                    if (current->tail->isList())
                        current = static_cast<List*>(current->tail);
                    else {
                        args.push_back(current->tail->eval(env));
                        break;
                    }
                } else break;
            } else break;
        }
    }

    return args;
}

Object* List::eval(Environment& env) {
    if (head == nullptr)
        return VM::getAllocator().createNil();
    
    std::vector<Object*> args = extractArguments(env);

    /*
    std::cout << "GENERAL INSPECTION:\n";
    inspect(this);

    std::cout << "OPERANDS: ";
    for (unsigned int i = 0; i < args.size(); i++)
        std::cout << args[i]->toString() << ", ";
    std::cout << std::endl;
    */
    
    if (head->isSymbol()) {
        Symbol *sym = static_cast<Symbol*>(head);
        if (env.isBuiltinFunction(sym))
            return env.getBuiltinFunction(sym)->apply(args);
    }

    Object *op = head->eval(env);
    if (op->isLambda())
        return static_cast<Closure*>(op->eval(env))->apply(args);
    else if (op->isClosure())
        return static_cast<Closure*>(op)->apply(args);
    
    throw std::runtime_error("Invalid function call, the operator cannot be used: " + op->toString());
}
