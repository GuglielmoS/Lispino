#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Object.h"
#include "Symbol.h"
#include "IntNumber.h"
#include "FloatNumber.h"
#include "Boolean.h"
#include "List.h"
#include "String.h"
#include "Lambda.h"
#include "Closure.h"
#include "GarbageCollector.h"
#include "Nil.h"
#include "Quote.h"
#include "Define.h"

#include <iostream>
#include <memory>

namespace Lispino {

    class Memory {

        // This struct contains a pointer to an allocated object and the pointer
        // to the next element in memory
        struct MemoryNode {
            std::unique_ptr<Object> object;
            MemoryNode *next;

            MemoryNode(Object* obj, MemoryNode* next) : object(obj), next(next) {}
        };
        
        // reference to the garbage collector
        GarbageCollector &gc;

        // pointer to the first object in memory
        MemoryNode *first;

        // number of objects stored
        size_t allocatedObjects;

        // remove the unused objects and return the number of objects deleted
        size_t releaseUnusedObjects() {
            MemoryNode *current = first, *prev = nullptr;
            size_t releasedObjects = 0;

            while (current != nullptr) {
                // if the current object is not marked, then it is not visibile
                // and it must be removed from the memory
                if (!current->object->isMarked()) {

                    // if we have the first node
                    if (prev == nullptr) {
                        first = current->next;
                        delete current;
                        current = first;
                    } else {
                        prev->next = current->next;
                        delete current;
                        current = prev->next;
                    }

                    // increase the counter for statistics
                    releasedObjects++;

                    // decrease the number of allocated objects
                    allocatedObjects--;
                } else {
                    // unmark the current object and skip to the next
                    current->object->unmark();
                    prev = current;
                    current = current->next;
                }
            }

            return releasedObjects;
        }

        public:

            Memory(GarbageCollector& gc) : gc(gc), first(nullptr), allocatedObjects(0) {}

            Object* allocate(Object::ObjectType type) {
                Object *allocatedObject = nullptr;

                switch (type) {
                    case Object::NIL:
                        allocatedObject = new Nil();
                        break;
                    case Object::SYMBOL:
                        allocatedObject = new Symbol();
                        break;
                    case Object::INT_NUMBER:
                        allocatedObject = new IntNumber();
                        break;
                    case Object::FLOAT_NUMBER:
                        allocatedObject = new FloatNumber();
                        break;
                    case Object::BOOLEAN:
                        allocatedObject = new Boolean();
                        break;
                    case Object::STRING:
                        allocatedObject = new String();
                        break;
                    case Object::LIST:
                        allocatedObject = new List();
                        break;
                    case Object::LAMBDA:
                        allocatedObject = new Lambda();
                        break;
                    case Object::CLOSURE:
                        allocatedObject = new Closure();
                        break;
                    case Object::QUOTE:
                        allocatedObject = new Quote();
                        break;
                    case Object::DEFINE:
                        allocatedObject = new Define();
                        break;
                    default:
                        throw std::runtime_error("[MEMORY-allocate ERROR] invalid ObjectType!");
                }

                // add the allocated object to the memory linked list
                MemoryNode *newNode = new MemoryNode(allocatedObject, first);
                first = newNode;

                // increase the counter
                allocatedObjects++;

                return allocatedObject;
            }

            size_t getAllocatedObjects() const {
                return allocatedObjects;
            }
            
            size_t cleanup() {
                gc.collect();
                return releaseUnusedObjects();
            }

            ~Memory() {
                MemoryNode *current = first;
                
                while (current != nullptr) {
                    MemoryNode *temp = current;
                    current = current->next;
                    delete temp;
                }
            }
    };
};

#endif // __MEMORY_H__
