(define (map f lst)
  (if (null? lst)
    nil
    (cons (f (car lst)) (map f (cdr lst)))))

(define (filter pred lst)
  (if (null? lst)
    nil
    (if (pred (car lst))
      (cons (car lst) (filter pred (cdr lst)))
      (filter pred (cdr lst)))))

(define (range start end)
  (if (= start end)
    nil
    (cons start (range (+ start 1) end))))

(define (sum lst)
  (if (null? lst)
    0
    (+ (car lst) (sum (cdr lst)))))


