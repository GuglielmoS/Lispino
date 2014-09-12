#include "VM.h"

namespace Lispino {
    // singleton instance
    VM VM::instance;

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
