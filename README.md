Lispino
=======

This is a toy project that I started to improve my knowledge about Lisp and the world of compilers and interpreters.  
I decided to not concentrate on the use of tricks for improving perfomances,
mainly because the goal is to achieve a better understanding of the
processes involved in the design of such a program.  
The syntax that I chose is the same of the Scheme examples present in 
the SICP book (Structure and Interpretation of Computer Programs), thus
you can test the interpreter by simply copy&pasting some basic code and 
get an idea of what is possible to do.  
In the 'examples/' folder there are some programs to try, while in the 'test/' folder you can find 
the unit tests that I wrote for the whole project.

Main Features
-------------

+ Values: Integer, Float, Character, String, Symbol, Boolean 
+ Basic Scheme forms: define, if, cond, let, begin, quote, lambda
+ Identity predicates: list?, symbol?, char?, string?, pair?, number?, boolean?, procedure?, null?, promise?
+ Equality operators: eq?, eqv?, equal?
+ Lazy evaluation with promises: delay, force, lazy-cons
+ A little standard library that contains basic stuff (see lib/std.scm)
+ REPL to interact with the interpreter (nice with rlwrap)
+ It successfully executes the SICP metacircular evaluator (with some minor changes)
+ Simple Recursive Descent Parser
+ Tail Call Reduction
+ Stop-The-World, Mark & Sweep Garbage Collection  
+ Takes advantage of C++11 features (smart pointers, auto, lambda, ...)
+ Unit tests covered
+ Checked with Valgrind Memcheck

Requirements
------------

+ C++ compiler which supports the C++11 standard
+ Googletest, Google C++ Testing Framework
+ Make

Build
-----

Just execute 'make' for getting the executable, 'make test' for running the unit
tests and 'make clean' for removing temporary object and executable files.

MetaEvaluator Session
---------------------

I think that the most interesting piece of code that Lispino can evaluate
is the Metacircular evaluator proposed in SICP.
Below you can find an example of a REPL session with that program. If you
want to try it you have just to execute 'bin/lispino examples/metacircular.scm'.

```
[MEval]>>> (def (append x y) (when (eq? x nil) y (cons (car x) (append (cdr x)y))))
ok
[MEval]>>> (append (list 1 2 3) (list 4 5 6))
(1 2 3 4 5 6)
[MEval]>>> (def (range s e) (when (= s e) nil (cons s (range (+ s 1) e))))
ok
[MEval]>>> (def (map f lst) (when (eq? lst nil) nil (cons (f (car lst)) (map f (cdr lst)))))
ok
[MEval]>>> (def (square x) (* x x))
ok
[MEval]>>> (range 0 10)
(0 1 2 3 4 5 6 7 8 9)
[MEval]>>> (map square (range 0 10))
(0 1 4 9 16 25 36 49 64 81)
```

TODO
----

+ Implement a better errors handling mechanism
+ Macros

