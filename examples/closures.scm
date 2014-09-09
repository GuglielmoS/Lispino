(define (make-adder n) 
  (lambda (x) (+ n x)))

(define add-one (make-adder 1))
(define add-two (make-adder 2))

(display (add-one 0))
(newline)
(display (add-two 0))
(newline)
(display (add-one (add-two 0)))
(newline)
