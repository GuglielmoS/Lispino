(define (fibonacci n)
  (if (< n 2)
    1
    (+ (fibonacci (- n 1)) (fibonacci (- n 2)))))

(display "The first ten fibonacci numbers: ")
(newline)
(display (map fibonacci (range 0 10)))
(newline)
