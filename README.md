Lispino
=======

A small LISP interpreter written in C++.  
At the moment it supports only a small subset of LISP.  

Thus the only instructions that you can try are:  
1. basic math operations  
> (+ x y)  
> (* x y)  
> (dec x)  

2. functions definition
> (def (square x) (* x x))  
> (square y)  

3. variables definition  
> (def x 3)  
> (def y 5)  
> (def z (+ x y))  
