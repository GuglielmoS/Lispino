#ifndef __LIST_H__
#define __LIST_H__

#include "Object.h"

#include <vector>
#include <string>

namespace Lispino {

    class List : public Object {

        Object *head;
        Object *tail;

        std::string toStringHelper(bool parentheses) const;
        std::vector<Object*> extractArguments(Environment& env);

        public:

            List() : head(nullptr), tail(nullptr) {}
            List(Object* head, Object* tail) : head(head), tail(tail) {}

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


            void setFirst(Object *first) {
                this->head = first;
            }

            void setRest(Object *rest) {
                this->tail = rest;
            }

            Object* getFirst() {
                return head;
            }

            Object* getRest() {
                return tail;
            }

            bool isList() const {
                return true;
            }

            void mark() {
                // mark the current object
                Object::mark();

                // mark its sub-components
                if (head != nullptr)
                    head->mark();
                if (tail != nullptr)
                    tail->mark();
            }

            std::string toString() const {
                return toStringHelper(true);
            }

    };
};

#endif // _LIST_H__
