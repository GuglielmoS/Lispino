#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

// c++
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

// execption
#include "TokenizerException.h"
#include "MalformedStringException.h"

using namespace std;

class Tokenizer {

public:
    
    static void tokenize(std::string& input, std::vector<std::string>& tokens) throw (TokenizerException);

};

#endif // __TOKENIZER_H__
