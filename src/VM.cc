#include "VM.h"

namespace Lispino {

    // singleton instance
    VM VM::instance;

    VM::VM() : memory(gc), allocator(memory), gc(globalEnv) {
        /* DO NOTHING */
    }

    Environment& VM::getGlobalEnv() {
        return instance.globalEnv;
    }

    Allocator& VM::getAllocator() {
        return instance.allocator;
    }

    Memory& VM::getMemory() {
        return instance.memory;
    }
}
