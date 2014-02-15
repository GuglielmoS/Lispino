(define (range start end)
  (if (= start end)
    nil
    (cons start (range (+ start 1) end))))

(define (euler1 values acc)
  (if (= values nil)
    acc
    (if (= (remainder (car values) 3) 0)
      (euler1 (cdr values) (+ (car values) acc))
      (if (= (remainder (car values) 5) 0)
        (euler1 (cdr values) (+ (car values) acc))
        (euler1 (cdr values) acc)))))

(display "Euler 1 result: " (euler1 (range 0 1000) 0) (newline))
