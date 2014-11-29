#ifndef LISPINO_UTILS_LIST_H_
#define LISPINO_UTILS_LIST_H_

#include <cstdint>

#include <vector>

#include "../Object.h"
#include "../List.h"

namespace lispino {

namespace utils {

std::vector<Object*> list2vec(List* list);

List* vec2list(std::vector<Object*>& vec);
}
}

#endif  // LISPINO_UTILS_LIST_H_
