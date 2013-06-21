#ifndef __LEXER__

#define __LEXER__

#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Lexer {

public:
    
    static void tokenize(string& input, vector<string>& tokens);

};

#endif // __LEXER__
