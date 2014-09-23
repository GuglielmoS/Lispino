;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Utils                                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (id x)
  x)

(define (null? val)
  (= val nil))

(define (newline)
  (display "\n"))

;; useful when used with cond
(define else #t)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Boolean                                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (not p)
  (if p #f #t))

(define (&& x y)
  (if x y #f))

(define (|| x y)
  (if x #t y))

(define (and . values)
  (fold && #t values))

(define (or . values)
  (fold || #f values))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; functional                                                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (flip f)
  (lambda (x y)
    (f x y)))

(define (curry f x)
  (lambda (y)
    (f x y)))

(define (compose f g)
  (lambda (x)
    (f (g x))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; higher order functions                                                    ;;
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

(define (foldl f acc lst)
  (if (null? lst)
    acc
    (fold f (f (car lst) acc) (cdr lst))))

(define (foldr f init lst)
  (if (null? lst)
    init
    (f (car lst) (foldr f init (cdr lst)))))

(define fold foldl)

(define (zipWith f lst1 lst2)
  (if (or (null? lst1) (null? lst2))
    nil
    (cons (f (car lst1) (car lst2))
          (zipWith f (cdr lst1) (cdr lst2)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; List                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (list . values)
  values)

(define (length lst)
  (fold (lambda (x acc) (inc acc)) 0 lst))

(define (reverse lst)
  (fold (flip cons) nil lst))

(define (append lst1 lst2)
  (if (null? lst1)
    lst2
    (cons (car lst1) (append (cdr lst1) lst2))))

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

(define (any lst)
  (fold || #f lst))

(define (all lst)
  (fold && #t lst))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::::::::
;; Math                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (inc x)
  (+ x 1))

(define (dec x)
  (- x 1))

(define (min first . rest)
  (fold (lambda (new old) (if (< new old) new old)) first rest))

(define (max first . rest)
  (fold (lambda (new old) (if (> new old) new old)) first rest))

(define (range start end)
  (define (iter start end acc)
    (if (= start end)
      (cons start acc)
      (iter start (dec end) (cons end acc))))
  (iter start end nil))

(define (sum lst)
  (fold + 0 lst))

(define (product lst)
  (fold * 1 lst))

(define zero? (curry = 0))

(define positive? (curry < 0))

(define negative? (curry > 0))

(define (div-by? n)
  (lambda (x)
    (zero? (remainder x n))))

(define (factorial n)
  (product (range 1 n)))

(define (exp base n)
  (cond ((= n 1)   base)
        ((= n 0)   1)
        ((even? n) (square (exp base (/ n 2))))
        (else      (* base (exp base (dec n))))))

(define (square n)
  (* n n))

(define (even? n)
  (zero? (remainder n 2)))

(define (odd? n)
  (not (zero? (remainder n 2))))

(define (abs x)
  (if (negative? x) (- x) x))

(define (gcd a b)
  (if (zero? b)
    a
    (gcd b (remainder a b))))

