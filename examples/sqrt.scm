(define (sqrt x)
  (define (sqrt-iter guess last-guess)
    (if (good-enough? guess last-guess)
        guess
        (sqrt-iter (improve guess x) guess)))
  (define (abs x) (if (< x 0) (- x) x))
  (define (square x) (* x x))
  (define (average x y) (/ (+ x y) 2))
  (define (improve guess x) (average guess (/ x guess)))
  (define (good-enough? guess last-guess)
    (< (abs (- guess last-guess)) 0.001))
  (sqrt-iter 1.0 0.0))

(display (sqrt 2))
(newline)
(display (sqrt 9))
(newline)
(display (sqrt (+ 100 37)))
(newline)
