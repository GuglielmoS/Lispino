(define (factorial n)
  (if (zero? n)
    1
    (* n (factorial (- n 1)))))

(display "Factorial(20) = " (factorial 20))
(newline)
