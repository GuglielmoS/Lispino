#ifndef __LIST_H__
#define __LIST_H__

#include "Object.h"

#include <vector>
#include <string>

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

            bool equals(Object *obj) const {
                if (this == obj)
                    return true;
                else if (obj->isList()) {
                    List *lst = static_cast<List*>(obj);

                    if (head == nullptr) {
                        if (lst->head != nullptr)
                            return false;
                    } else {
                        if (lst->head == nullptr)
                            return false;
                        else if (!head->equals(lst->head))
                            return false;
                    }

                    if (tail == nullptr) {
                        if (lst->tail != nullptr)
                            return false;
                    } else {
                        if (lst->tail == nullptr)
                            return false;
                        else if (!tail->equals(lst->tail))
                            return false;
                    }

                    return true;
                } else
                    return false;
            }

            inline void setFirst(Object *first) {
                this->head = first;
            }

            inline void setRest(Object *rest) {
                this->tail = rest;
                cachedArgs = false;
            }

            inline Object* getFirst() {
                return head;
            }

            inline Object* getRest() {
                return tail;
            }

            bool isList() const {
                return true;
            }

            void mark() {
                // mark the current object
                Object::mark();

                // mark its sub-components
                head->mark();
                tail->mark();
                for (unsigned int i = 0; i < args.size(); i++)
                    args[i]->mark();
            }

            std::string toString() const {
                return toStringHelper(true);
            }

    };
};

#endif // _LIST_H__
