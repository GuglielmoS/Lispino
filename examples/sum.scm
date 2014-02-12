(define (sum n)
  (if (= n 0)
    0
    (+ n (sum (- n 1)))))

(display "Sum from 0 to 5000 = " (sum 5000) (newline))
