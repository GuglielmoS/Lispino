Lispino
=======

A small LISP interpreter written in C++.  
Currently it supports only a small subset of LISP.  

REPL commands
-------------
```
> quit  
Exits from the REPL  
> time-it <code>  
Shows the execution time of the provided code  
```

Examples
--------
Factorial
```
> (def (fact n) (if (= n 0) 1 (* n (fact (- n 1)))))
#<LAMBDA>  
> (fact 5)  
120  
> (fact 20)  
2432902008176640000  
```

Arithmetic expressions
----------------------
```
> (+ 1 2)
3  
> (* 2 3)
6  
> (* 1 2 3 4)
24  
> (/ 1 2)
0  
> (/ 1.0 2)
0.5  
```

Variables
---------
```
> (def x 1)
    x
> (def y 5)
    y
> (def z (+ x y))
    z
> z
    6
> (+ x y z)
    12
```

Closures
-------
```
> (def make-adder (lambda (x) (lambda (y) (+ x y)))))
    make-adder
> (def add-one (make-adder 1))
    add-one
> (def add-two (make-adder 2))
    add-two
> (add-one (add-two 0))
    3
```

Functions definition syntax
---------------------------
```
> (def (square x) (* x x))
    square
> (def (double x) (+ x x))
    double
> (square 5)
    25
> (double 5)
    10
```

Lists
-----
```
> '(A B C D)
    (A B C D)
> '(A . B)
    (A . B)
> '(A B C . D)
    (A B C . D)
> (car '(A B C D))
    A
> (cdr '(A B C D))
    (B C D)
> (car (cdr (cdr '(A B C D))))
    C
```
