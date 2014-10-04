(define (collatz-next x)
  (if (even? x)
    (/ n 2)
    (+ (* 3 n) 1)))

(define (collatz-seq n)
  (if (= n 1)
    (lazy-cons 1 the-empty-stream)
    (lazy-cons n (collatz-seq (collatz-next n)))))

(define (collatz-length n)
  (define (iter s acc)
    (if (stream-null? s)
      acc
      (iter (stream-cdr s) (+ acc 1))))
  (iter (collatz-seq n) 0))

(display "collatz(13) has " (collatz-length 13) " elements")
(newline)
(display-stream (collatz-seq 13))
