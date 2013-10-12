#ifndef __LTYPES__

#define __LTYPES__

enum LType { CONS, NIL,
             ATOM_STRING, ATOM_SYMBOL, ATOM_DOUBLE, ATOM_INTEGER,
             IF_EXPRESSION, QUOTE_EXPRESSION, LAMBDA_EXPRESSION
           };

#endif // __LTYPES__
