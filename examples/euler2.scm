; infinite stream of fibonacci numbers
(define fibs (lazy-cons 0 (lazy-cons 1 (stream-zipWith + (stream-cdr fibs) fibs))))

; sum of the even fibonacci numbers
(define (euler2 limit)
  (define (iter s acc)
    (if (> (stream-car s) limit)
      acc
      (iter (stream-cdr s) (+ acc (stream-car s)))))
  (iter (stream-filter even? fibs) 0))

(display "Euler 2: " (euler2 4000000))
(newline)
