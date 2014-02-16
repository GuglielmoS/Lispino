(define (accumulate combiner null-value term a next b)
  (if (> a b)
    null-value
    (combiner (term a) 
              (accumulate combiner null-value term (next a) next b))))

(define (sum term a next b)
  (accumulate + 0 term a next b))

(define (product term a next b)
  (accumulate * 1 term a next b))

(define (id x) x)
(define (inc n) (+ 1 n))

(define (factorial n)
  (product id 1 inc n))

(define (sum-integers-below n)
  (sum id 1 inc n))

(display "factorial of 5 = " (factorial 5))
(newline)
(display "sum integers below 10 = " (sum-integers-below 10))
(newline)
