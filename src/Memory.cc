#include "Memory.h"

namespace Lispino {
    Memory::Memory(GarbageCollector& gc) : gc(gc), first(nullptr), allocatedObjects(0) {
        nilInstance = new Nil();
        trueInstance = new Boolean(true);
        falseInstance = new Boolean(false);
    }

    Memory::~Memory() {
        // delete the objects stored in the virtual memory
        MemoryNode *current = first;
        while (current != nullptr) {
            MemoryNode *temp = current;
            current = current->next;
            delete temp;
        }

        // delete the cached instances
        delete nilInstance;
        delete trueInstance;
        delete falseInstance;
    }

    Nil* Memory::getNilInstance() {
        return nilInstance;
    }

    Boolean* Memory::getTrueInstance() {
        return trueInstance;
    }

    Boolean* Memory::getFalseInstance() {
        return falseInstance;
    }

    Object* Memory::allocate(Object::ObjectType type) {
        Object *allocatedObject = nullptr;

        switch (type) {
            case Object::SYMBOL:
                allocatedObject = new Symbol();
                break;
            case Object::INT_NUMBER:
                allocatedObject = new IntNumber();
                break;
            case Object::FLOAT_NUMBER:
                allocatedObject = new FloatNumber();
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
            case Object::IF:
                allocatedObject = new IfExpr();
                break;
            case Object::SEQUENCE:
                allocatedObject = new Sequence();
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

    size_t Memory::getAllocatedObjects() const {
        return allocatedObjects;
    }

    size_t Memory::cleanup() {
        gc.collect();
        return releaseUnusedObjects();
    }

    // remove the unused objects and return the number of objects deleted
    size_t Memory::releaseUnusedObjects() {
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
}
