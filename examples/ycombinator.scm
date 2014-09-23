;; Taken from http://rosettacode.org/wiki/Y_combinator#Scheme

(define (Y f)
  ((lambda (x)
     (x x))
   (lambda (g)
     (f (lambda args
          (apply (g g) args))))))

(define fac
  (Y
    (lambda (f)
      (lambda (x)
        (if (< x 2)
          1
          (* x (f (- x 1))))))))

(define fib
  (Y
    (lambda (f)
      (lambda (x)
        (if (< x 2)
          x
          (+ (f (- x 1)) (f (- x 2))))))))

(display "Factorial(6) = " (fac 6))
(newline)

(display "Fibonacci(6) = " (fib 6))
(newline)
