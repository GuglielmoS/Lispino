(define (map f lst)
  (if (= lst nil)
    nil
    (cons (f (car lst)) (map f (cdr lst)))))

(define (filter pred lst)
  (if (= lst nil)
    nil
    (if (pred (car lst))
      (cons (car lst) (filter pred (cdr lst)))
      (filter pred (cdr lst)))))

(define (range start end)
  (if (= start end)
    nil
    (cons start (range (+ start 1) end))))

(define (sum lst)
  (if (= lst nil)
    0
    (+ (car lst) (sum (cdr lst)))))

(define (div-by-3? x) (= (remainder x 3) 0))
(define (div-by-5? x) (= (remainder x 5) 0))
(define values (range 0 1000))

(define result
  (- (+ (sum (filter div-by-3? values))
        (sum (filter div-by-5? values)))
     (sum (filter div-by-3? (filter div-by-5? values)))))

(display "Euler 1 result: " result)
(newline)
