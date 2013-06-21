#include <iostream>
#include <string>

#include "LObject.h"
#include "LNilObject.h"
#include "LInteger.h"
#include "LCons.h"
#include "LSymbol.h"
#include "LString.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int test_integer_atom() {
    LObject* obj = new LInteger(5);

    if (obj->getType() != "Atom") {
        cout << "[FAILED] Integer Atom :: getType failed!" << endl;
        return 1;
    }

    if (obj->prettyString() != "5") {
        cout << "[FAILED] Integer Atom :: prettyString failed!" << endl;
        return 2;
    }

    if (dynamic_cast<LInteger*>(obj)->getValue() != 5) {
        cout << "[FAILED] Integer Atom :: getValue failed!" << endl;
        return 3;
    }

    delete obj;

    return 0;
}

int test_nil_object() {
    LObject* obj = new LNilObject();

    if (obj->getType() != "NilObject") {
        cout << "[FAILED] Nil Object :: getType failed!" << endl;
        return 1;
    }

    if (obj->prettyString() != "NIL") {
        cout << "[FAILED] Nil Object :: prettyString failed!" << endl;
        return 2;
    }

    delete obj;

    return 0;
}

int test_symbol_atom() {
    LObject* obj = new LSymbol("fibonacci");
    
    if (obj->getType() != "AtomSymbol") {
        cout << "[FAILED] Symbol Atom :: getType failed!" << endl;
        return 1;
    }

    if (obj->prettyString() != "fibonacci") {
        cout << "[FAILED] Symbol Atom :: prettyPrint failed!" << endl;
        return 2;
    }

    if (dynamic_cast<LSymbol*>(obj)->getValue() != "fibonacci") {
        cout << "[FAILED] Symbol Atom :: getValue failed!" << endl;
        return 3;
    }

    delete obj;

    return 0;
}

int test_string_atom() {
    LObject* obj = new LString("lisp");
    
    if (obj->getType() != "AtomString") {
        cout << "[FAILED] String Atom :: getType failed!" << endl;
        return 1;
    }

    if (obj->prettyString() != "lisp") {
        cout << "[FAILED] String Atom :: prettyPrint failed!" << endl;
        return 2;
    }
    
    if (dynamic_cast<LString*>(obj)->getValue() != "lisp") {
        cout << "[FAILED] String Atom :: getValue failed!" << endl;
        return 3;
    }

    delete obj;

    return 0;
}

int test_atom() {

    if (test_nil_object() == 0)
        cout << "[OK] Nil Object tests passed successfully!" << endl;
    else
        return 1;

    if (test_integer_atom() == 0)
        cout << "[OK] Integer Atom tests passed successfully!" << endl;
    else
        return 2;

    if (test_symbol_atom() == 0)
        cout << "[OK] Symbol Atom tests passed successfully!" << endl;
    else
        return 3;

    if (test_string_atom() == 0)
        cout << "[OK] String Atom tests passed successfully!" << endl;
    else
        return 4;

    return 0;
}

int test_cons() {
    LObject* obj1 = new LCons(new LInteger(1));
    LObject* obj2 = new LCons(new LInteger(1), new LInteger(2));
    LObject* obj3 = new LCons(new LInteger(1), new LCons(new LInteger(2)));
    
    // type test
    
    if (obj1->getType() != "Cons") {
        cout << "[FAILED] Cons Object :: getType failed!" << endl;
        return 1;
    }

    // pretty print test

    if (obj1->prettyString() != "(1)") {
        cout << "[FAILED] Cons Object :: prettyString failed!" << endl;
        return 2;
    }

    if (obj2->prettyString() != "(1 . 2)") {
        cout << "[FAILED] Cons Object :: prettyString failed!" << endl;
        return 3;
    }


    if (obj3->prettyString() != "(1 2)") {
        cout << "[FAILED] Cons Object :: prettyString failed!" << endl;
        return 4;
    }

    // accessors methods test

    if (car(dynamic_cast<LCons*>(obj1))->prettyString() != "1") {
        cout << "[FAILED] Cons Object :: car failed!" << endl;
        return 5;
    }


    if (car(dynamic_cast<LCons*>(obj2))->prettyString() != "1") {
        cout << "[FAILED] Cons Object :: car failed!" << endl;
        return 6;
    }


    if (car(dynamic_cast<LCons*>(obj3))->prettyString() != "1") {
        cout << "[FAILED] Cons Object :: car failed!" << endl;
        return 7;
    }

    if (cdr(dynamic_cast<LCons*>(obj1))->prettyString() != "NIL") {
        cout << "[FAILED] Cons Object :: cdr failed!" << endl;
        return 8;
    }

    if (cdr(dynamic_cast<LCons*>(obj2))->prettyString() != "2") {
        cout << "[FAILED] Cons Object :: cdr failed!" << endl;
        return 9;
    }

    if (cdr(dynamic_cast<LCons*>(obj3))->prettyString() != "(2)") {
        cout << "[FAILED] Cons Object :: cdr failed!" << endl;
        return 10;
    }

    delete obj1;
    delete obj2;
    delete obj3;

    cout << "[OK] Cons Object tests passed successfully!" << endl;

    return 0;
}

int test_lexer() {
    string expr = "(foo bar \"old fox\")";
    vector<string> realTokens;

    realTokens.push_back("(");
    realTokens.push_back("foo");
    realTokens.push_back("bar");
    realTokens.push_back("\"old fox\"");
    realTokens.push_back(")");

    vector<string> lexerTokens;    
    Lexer::tokenize(expr, lexerTokens);

    if (lexerTokens.size() != realTokens.size()) {
        cout << "[FAILED] Lexer :: tokenize failed!" << endl;
        return 1;
    }

    bool equal = true;
    for (unsigned int i = 0; i < realTokens.size() && equal; i++)
        if (realTokens[i] != lexerTokens[i])
            equal = false;

    if (!equal) {
        cout << "[FAILED] Lexer :: tokenize failed!" << endl;
        return 2;
    }
    
    cout << "[OK] Lexer tests passed successfully!" << endl;

    return 0;
}

int test_parser() {
    vector<string> inputs;

    inputs.push_back("123456789");
    inputs.push_back("\"lisp is the best language of the world\"");
    inputs.push_back("abbababac");
    inputs.push_back("(define (square x) (* x x))");

    vector<LObject*> exprs;
    for (unsigned int i = 0; i < inputs.size(); i++) {
        exprs.push_back(Parser::parse(inputs[i]));

        /*cout << "Type:  " << exprs[i]->getType() << endl
             << "Value: " << exprs[i] << endl << endl;*/
    }

    if (exprs[0]->getType() != "AtomInteger") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 1;
    }

    if (dynamic_cast<LInteger*>(exprs[0])->getValue() != 123456789) {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 2;
    }

    if (exprs[1]->getType() != "AtomString") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 3;
    }

    if (dynamic_cast<LString*>(exprs[1])->getValue() != "lisp is the best language of the world") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 4;
    }

    if (exprs[2]->getType() != "AtomSymbol") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 5;
    }

    if (dynamic_cast<LSymbol*>(exprs[2])->getValue() != "abbababac") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 6;
    }

    if (exprs[3]->getType() != "Cons") {
        cout << "[FAILED] Parser :: parse failed!" << endl;
        return 7;
    }

    while (exprs.size() > 0)
        exprs.pop_back();

    cout << "[OK] Parser tests passed successfully!" << endl;

    return 0;
}

int test_all() {
    if (test_atom() != 0) {
        cout << "[FAILED] ATOM TEST FAILED!" << endl;
        return 1;
    }

    if (test_cons() != 0) {
        cout << "[FAILED] ATOM TEST FAILED!" << endl;        
        return 2;
    }

    if (test_lexer() != 0) {
        cout << "[FAILED] LEXER TEST FAILED!" << endl;
        return 3;
    }

    if (test_parser() != 0) {
        cout << "[FAILED] PARSER TEST FAILED!" << endl;
        return 4;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    return test_all();
}
