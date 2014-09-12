#ifndef LISPINO_MEMORY_H_
#define LISPINO_MEMORY_H_

#include <iostream>
#include <memory>

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
#include "IfExpr.h"
#include "Sequence.h"

namespace Lispino {

    class Memory {

        // This struct contains a pointer to an allocated object and the pointer
        // to the next element in memory
        struct MemoryNode {
            std::unique_ptr<Object> object;
            MemoryNode *next;

            MemoryNode(Object* obj, MemoryNode* next) : object(obj), next(next) {}
        };

        public:

            Memory(GarbageCollector& gc);
            ~Memory();

            Nil* getNilInstance();
            Boolean* getTrueInstance();
            Boolean* getFalseInstance();

            Object* allocate(Object::ObjectType type);

            size_t getAllocatedObjects() const;

            size_t cleanup();

        private:

            // reference to the garbage collector
            GarbageCollector &gc;

            // pointer to the first object in memory
            MemoryNode *first;

            // instance of frequently used objects that don't change their value
            Nil *nilInstance;
            Boolean *trueInstance;
            Boolean *falseInstance;

            // number of objects stored
            size_t allocatedObjects;

            // remove the unused objects and return the number of objects deleted
            size_t releaseUnusedObjects();
    };
};

#endif // LISPINO_MEMORY_H_
