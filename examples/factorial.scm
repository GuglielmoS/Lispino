(define (factorial n)
  (if (= n 0)
    1
    (* n (factorial (- n 1)))))

(display "Factorial(20) = " (factorial 20) (newline))
