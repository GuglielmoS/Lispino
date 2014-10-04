;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Utils                                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (id x)
  x)

(define (null? val)
  (eq? val nil))

(define (newline)
  (display "\n"))

(define (display-line x)
  (display x)
  (newline))

;; useful when used with cond
(define else #t)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Boolean                                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (not p)
  (if p #f #t))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Functional                                                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (flip f)
  (lambda (x y)
    (f y x)))

(define (curry f x)
  (lambda (y)
    (f x y)))

(define (compose f g)
  (lambda (x)
    (f (g x))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Higher Order Functions                                                    ;;
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
    (fold f (f acc (car lst)) (cdr lst))))

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; List                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (list . values)
  values)

(define (list-ref lst n)
  (if (= n 0)
    (car lst)
    (list-ref (cdr lst) (- n 1))))

(define (length lst)
  (fold (lambda (acc x) (inc acc)) 0 lst))

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
  (fold or #f lst))

(define (all lst)
  (fold and #t lst))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Lazy evaluation                                                           ;; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define the-empty-stream nil)

(define (stream-null? s)
  (eq? s the-empty-stream))

(define stream-car car)

(define (stream-cdr s)
  (force (cdr s)))

(define (stream-ref s n)
  (if (= n 0)
    (stream-car s)
    (stream-ref (stream-cdr s) (- n 1))))

(define (stream-map proc s)
  (if (stream-null? s)
    the-empty-stream
    (lazy-cons (proc (stream-car s))
               (stream-map proc (stream-cdr s)))))

(define (stream-filter pred s)
  (cond ((stream-null? s) the-empty-stream)
        ((pred (stream-car s))
         (lazy-cons (stream-car s)
                    (stream-filter pred (stream-cdr s))))
        (else (stream-filter pred (stream-cdr s)))))

(define (stream-for-each proc s)
  (if (stream-null? s)
    'done
    (begin (proc (stream-car s))
           (stream-for-each proc (stream-cdr s)))))

(define (stream-zipWith proc s1 s2)
  (if (or (stream-null? s1) (stream-null? s2))
    the-empty-stream
    (lazy-cons (proc (stream-car s1) (stream-car s2))
               (stream-zipWith proc (stream-cdr s1) (stream-cdr s2)))))

(define (stream-take s n)
  (if (= n 0)
    the-empty-stream
    (cons (stream-car s)
          (stream-take (stream-cdr s) (- n 1)))))

(define (display-stream s)
  (stream-for-each display-line s))

(define (stream-enumerate-interval low hig)
  (if (> low high)
    the-empty-stream
    (lazy-cons
      low
      (stream-enumerate-interval (+ low 1) high))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Math                                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (inc x)
  (+ x 1))

(define (dec x)
  (- x 1))

(define (min first . rest)
  (fold (lambda (old new) (if (< new old) new old)) first rest))

(define (max first . rest)
  (fold (lambda (old new) (if (> new old) new old)) first rest))

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

(define (expt base n)
  (cond ((= n 1)   base)
        ((= n 0)   1)
        ((even? n) (square (expt base (/ n 2))))
        (else      (* base (expt base (dec n))))))

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

