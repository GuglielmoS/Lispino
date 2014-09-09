(define (euler1 values acc)
  (if (null? values)
    acc
    (if ((div-by? 3) (car values))
      (euler1 (cdr values) (+ (car values) acc))
      (if ((div-by? 5) (car values))
        (euler1 (cdr values) (+ (car values) acc))
        (euler1 (cdr values) acc)))))

(display "Euler 1 result: " (euler1 (range 0 1000) 0))
(newline)
