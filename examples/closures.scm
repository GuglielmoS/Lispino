;; create an adder generator
(define (make-adder n) 
  (lambda (x) (+ n x)))

;; create two adder
(define add-one (make-adder 1))
(define add-two (make-adder 2))

;; test the adder
(display (add-one 0))
(newline)
(display (add-two 0))
(newline)
(display (add-one (add-two 0)))
(newline)
