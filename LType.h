#ifndef __LTYPES_H__
#define __LTYPES_H__

/**
 * This enumeration contains all the existent types provided by the language.
 * Thus every parsed expression will have one of them.
 */
enum LType { // LIST
             CONS, NIL,

             // ATOMIC VALUES
             ATOM_STRING, ATOM_SYMBOL, ATOM_DOUBLE, ATOM_INTEGER,
            
             // SPECIAL EXPRESSION
             IF_EXPRESSION, QUOTE_EXPRESSION, LAMBDA_EXPRESSION, DEFINE_EXPRESSION,
             
             // OTHER 
             CLOSURE, BUILTIN_FUNCTION
           };

#endif // __LTYPES_H__
