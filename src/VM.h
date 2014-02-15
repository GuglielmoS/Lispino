#ifndef __VM_H__
#define __VM_H__

#include "Memory.h"
#include "Allocator.h"
#include "GarbageCollector.h"
#include "Environment.h"

namespace Lispino {

    class VM {
        
        // memory used at runtime by the objects
        Memory memory;

        // used when at runtime when a new object is needed 
        Allocator allocator;

        // gc used by the memory when needed
        GarbageCollector gc;

        // environment that contains the global definitions 
        Environment globalEnv;
    
        // default private constructor
        VM() : memory(gc), allocator(memory), gc(globalEnv) {}

        // singleton instance
        static VM instance;

        public:

            static Environment& getGlobalEnv();
            static Allocator& getAllocator();
            static Memory& getMemory();
            
    };
};

#endif // __VM_H__
