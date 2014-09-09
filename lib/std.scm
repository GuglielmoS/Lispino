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
  (if (or (null? lst) (false? (f (car lst))))
    nil
    (cons (car lst) (takeWhile f (cdr lst)))))

(define (dropWhile f lst)
  (if (or (null? lst) (false? (f (car lst))))
    lst
    (dropWhile f (cdr lst))))

(define (fold f init lst)
  (if (null? lst)
    init
    (f (car lst) (fold f init (cdr lst)))))

(define (zipWith f lst1 lst2)
  (if (or (null? lst1) (null? lst2))
    nil
    (cons (f (car lst1) (car lst2))
          (zipWith f (cdr lst1) (cdr lst2)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; List                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (any lst)
  (fold or false lst))

(define (all lst)
  (fold and true lst))

(define (take n lst)
  (if (or (zero? n) (null? lst))
    nil
    (cons (car lst) (take (- n 1) (cdr lst)))))

(define (drop n lst)
  (if (or (zero? n) (null? lst))
    lst
    (drop (- n 1) (cdr lst))))

(define (zip lst1 lst2)
  (zipWith cons lst1 lst2))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Math                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (range start end)
  (if (= start end)
    nil
    (cons start (range (+ start 1) end))))

(define (sum lst)
  (fold + 0 lst))

(define (product lst)
  (fold * 1 lst))

(define (zero? n)
  (= n 0))

(define (positive? n)
  (> n 0))

(define (factorial n)
  (product (range 1 (+ n 1))))

(define (even n)
  (if (zero? n)
    true
    (odd (- n 1))))

(define (odd n)
  (if (zero? n)
    false
    (even (- n 1))))

(define (fibonacci n)
  (if (< n 2)
    1
    (+ (fibonacci (- n 1)) (fibonacci (- n 2)))))

