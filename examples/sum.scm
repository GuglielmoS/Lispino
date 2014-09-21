(define (sum n)
  (define (iter n acc)
    (if (zero? n)
      acc
      (+ n (iter (- n 1) acc))))
  (iter n 0))

(display "Sum from 0 to 5000 = " (sum 5000))
(newline)
