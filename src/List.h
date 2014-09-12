#ifndef LISPINO_LIST_H_
#define LISPINO_LIST_H_

#include <vector>
#include <string>

#include "Object.h"

namespace Lispino {

    class List : public Object {

        Object *head;
        Object *tail;

        bool cachedArgs;
        std::vector<Object*> args;

        std::string toStringHelper(bool parentheses) const;

        public:

            List() : head(nullptr), tail(nullptr), cachedArgs(false) {}
            List(Object* head, Object* tail) : head(head), tail(tail), cachedArgs(false) {}

            Object* eval(Environment& env);

            int compare(Object* obj);
            int compareList(List* obj);

            void setFirst(Object *first);
            void setRest(Object *rest);
            Object* getFirst();
            Object* getRest();

            void mark();

            bool isList() const;

            std::string toString() const;
    };
};

#endif // LISPINO_LIST_H_
