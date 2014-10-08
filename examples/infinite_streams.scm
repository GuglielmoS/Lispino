(define ones (lazy-cons 1 ones))

(define integers (lazy-cons 1 (stream-zipWith + ones integers)))

(define (integers-starting-from n)
  (lazy-cons n (integers-starting-from (+ n 1))))

(define fibs (lazy-cons 0 (lazy-cons 1 (stream-zipWith + (stream-cdr fibs) fibs))))

(define (sieve stream)
  (lazy-cons
    (stream-car stream)
    (sieve (stream-filter
             (lambda (x)
               (not ((div-by? (stream-car stream)) x)))
             (stream-cdr stream)))))

(define primes (sieve (integers-starting-from 2)))

(display "First 20 fibonacci numbers: ")
(newline)
(display (stream-take fibs 20))
(newline)

(display "First 20 prime numbers: ")
(newline)
(display (stream-take primes 20))
(newline)
