#include "Lexer.h"

using namespace std;

void Lexer::tokenize(string& input, vector<string>& tokens) {
    string::iterator it = input.begin();
    
    while (it != input.end()) {
        if (*it == ' ' || *it == '\t' || *it == '\n') {
            ++it; 
            continue;
        } 
        else if (*it == '(') {
            tokens.push_back("(");
            ++it;
        }
        else if (*it == ')') {
            tokens.push_back(")");
            ++it;
        }
        else if (*it == '\'') {
            tokens.push_back("'");
            ++it;
        }
        else if (*it == '\"') {
            stringstream buf;
            
            buf << "\"";
            ++it;

            char last = *it;
            while (it != input.end()) {
                if (*it == '\"' && last != '\\')
                    break;
            
                buf << *it;
                last = *it;
                ++it;
            }
            
            buf << "\"";
            ++it;

            tokens.push_back(buf.str());
        }
        else {
            stringstream buf;

            while (it != input.end() &&
                    *it != ' ' && *it != '\t' && *it != '\n' && 
                    *it != '(' && *it != ')') {
                buf << *it;
                ++it;
            }

            tokens.push_back(buf.str());
        }
    }
}

