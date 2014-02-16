(define (fibonacci n)
  (if (= n 0)
    1
    (if (= n 1)
      1
      (+ (fibonacci (- n 1)) (fibonacci (- n 2))))))

(display "FIBONACCI(25) = " (fibonacci 25))
(newline)
