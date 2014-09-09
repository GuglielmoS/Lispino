(define (accumulate combiner null-value term a next b)
  (if (> a b)
    null-value
    (combiner (term a) 
              (accumulate combiner null-value term (next a) next b))))

(define (sum-alt term a next b)
  (accumulate + 0 term a next b))

(define (prod term a next b)
  (accumulate * 1 term a next b))

(define (fact n)
  (prod id 1 inc n))

(define (sum-integers-below n)
  (sum-alt id 1 inc n))

(display "factorial of 5 = " (fact 5))
(newline)
(display "sum integers below 10 = " (sum-integers-below 10))
(newline)
