(define (make-counter n)
  (lambda (x)
    (set! n (+ n x))))

(define count (make-counter 0))

(display (count 1))
(newline)
(display (count 2))
(newline)
(display (count 3))
(newline)

