(define (div-by-3? x) (= (remainder x 3) 0))
(define (div-by-5? x) (= (remainder x 5) 0))
(define values (range 0 1000))

(define result
  (- (+ (sum (filter div-by-3? values))
        (sum (filter div-by-5? values)))
     (sum (filter div-by-3? (filter div-by-5? values)))))

(display "Euler 1 result: " result)
(newline)
