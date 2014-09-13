(define (factorial-alternative n)
  (if (zero? n)
    1
    (* n (factorial (- n 1)))))

(display "Factorial(20) = " (factorial-alternative 20))
(newline)
