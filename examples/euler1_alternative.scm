(define values (range 0 1000))

(define result
  (- (+ (sum (filter (div-by? 3) values))
        (sum (filter (div-by? 5) values)))
     (sum (filter (div-by? 3) (filter (div-by? 5) values)))))

(display "Euler 1 result: " result)
(newline)
