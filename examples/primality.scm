(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
  (eq? (remainder b a) 0))

(define (prime? n)
  (eq? n (smallest-divisor n)))

(display "The prime numbers below 50: ")
(display (filter prime? (range 1 51)))
(newline)
