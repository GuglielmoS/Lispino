Lispino
=======

This is a toy project that I started to improve my knowledge about Lisp and the world of compilers and interpreters.  
There are not particular tricks thought for improving perfomances,
mainly because the goal is to achieve a better understanding of the
processes involved in the design of such a program.  
The syntax that I chose is the same of the Scheme examples present in 
the SICP book (Structure and Interpretation of Computer Programs), thus
you can test the interpreter by simply copy&paste some basic code and 
get an idea of what is possible to do.  
In the examples/ folder there are some programs to try, while in the test/ folder you can find the unit tests that I wrote for the whole project.

Main Features
--------

+ Simple Recursive Descent Parser
+ Tail Call Reduction
+ Stop-The-World, Mark & Sweep Garbage Collection  
+ Unit tests covered
+ Checked with Valgrind Memcheck
+ REPL to interact with the interpreter (nice with rlwrap)
+ Easy way to add builtin functions
+ Basic Scheme constructs available (see the examples)
+ Integer, Float, String, Symbol, Boolean as possible atoms values
+ A little standard library that contains basic stuff (see lib/std.scm)

TODO
----

+ Implement a better errors handling mechanism

Requirements
------------

+ C++ compiler which supports the C++11 standard
+ Googletest, Google C++ Testing Framework
+ Make
