(define (integers-starting-from n)
  (lazy-cons n (integers-starting-from (+ n 1))))

(define (sieve stream)
  (lazy-cons
    (stream-car stream)
    (sieve (stream-filter
             (lambda (x)
               (not ((div-by? (stream-car stream)) x)))
             (stream-cdr stream)))))

;; infinite stream of prime numbers
(define primes (sieve (integers-starting-from 2)))

(define (euler7 nth)
  (stream-ref primes (- nth 1)))

(display "The 10001st prime number is: " (euler7 10001))
(newline)
