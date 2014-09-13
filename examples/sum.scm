(define (sum n)
  (if (zero? n)
    0
    (+ n (sum (- n 1)))))

(display "Sum from 0 to 5000 = " (sum 5000))
(newline)
