#ifndef __LEXER__

#define __LEXER__

#include <vector>
#include <sstream>
#include <string>

class Lexer {

public:
    
    static void tokenize(std::string& input, std::vector<std::string>& tokens);

};

#endif // __LEXER__
