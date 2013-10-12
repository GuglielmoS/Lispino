#ifndef __LEXER__

#define __LEXER__

#include <vector>
#include <sstream>
#include <string>

#include "TokenizerException.h"
#include "MalformedStringException.h"

class Tokenizer {

public:
    
    static void tokenize(std::string& input, std::vector<std::string>& tokens)
        throw (TokenizerException);

};

#endif // __LEXER__
