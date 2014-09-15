;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Utils                                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (id x)
  x)

(define (null? val)
  (eq? val nil))

(define (newline)
  (display "\n"))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Boolean                                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (not p)
  (if p false true))

(define (and p1 p2)
  (if p1 p2 false))

(define (or p1 p2)
  (if p1 true p2))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Higher order functions                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

(define (takeWhile f lst)
  (if (or (null? lst) (not (f (car lst))))
    nil
    (cons (car lst) (takeWhile f (cdr lst)))))

(define (dropWhile f lst)
  (if (or (null? lst) (not (f (car lst))))
    lst
    (dropWhile f (cdr lst))))

(define (fold f acc lst)
  (if (null? lst)
    acc
    (fold f (f (car lst) acc) (cdr lst))))

(define (foldr f init lst)
  (if (null? lst)
    init
    (f (car lst) (foldr f init (cdr lst)))))

(define (zipWith f lst1 lst2)
  (if (or (null? lst1) (null? lst2))
    nil
    (cons (f (car lst1) (car lst2))
          (zipWith f (cdr lst1) (cdr lst2)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; List                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (length lst)
  (if (null? lst)
    0
    (+ 1 (length (cdr lst)))))

(define (any lst)
  (fold or false lst))

(define (all lst)
  (fold and true lst))

(define (take n lst)
  (if (or (zero? n) (null? lst))
    nil
    (cons (car lst) (take (dec n) (cdr lst)))))

(define (drop n lst)
  (if (or (zero? n) (null? lst))
    lst
    (drop (dec n) (cdr lst))))

(define (zip lst1 lst2)
  (zipWith cons lst1 lst2))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Math                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (inc x)
  (+ x 1))

(define (dec x)
  (- x 1))

(define (range start end)
  (if (eq? start end)
    nil
    (cons start (range (inc start) end))))

(define (sum lst)
  (fold + 0 lst))

(define (product lst)
  (fold * 1 lst))

(define (zero? n)
  (eq? n 0))

(define (positive? n)
  (> n 0))

(define (div-by? n)
  (lambda (x)
    (zero? (remainder x n))))

(define (factorial n)
  (product (range 1 (inc n))))

(define (exp base n)
  (if (eq? n 1)
    base
    (if (eq? n 0)
      1
      (if (even? n)
        (square (exp base (/ n 2)))
        (* base (exp base (dec n)))))))

(define (square n)
  (* n n))

(define (even? n)
  (if (zero? n)
    true
    (odd? (dec n))))

(define (odd? n)
  (if (zero? n)
    false
    (even? (dec n))))

(define (abs x)
  (if (< x 0)
    (- x)
    x))

