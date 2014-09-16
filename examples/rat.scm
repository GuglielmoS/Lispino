(define (make-rat n d)
  (let ((g (gcd n d)))
    (cons (/ n g) (/ d g))))

(define (numer x) (car x))
(define (denom x) (cdr x))

(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))

(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))

(define (mul-rat x y)
  (make-rat (* (numer x) (numer y))
            (* (denom x) (numer y))))

(define (equal-rat? x y)
  (eq? (* (numer x) (denom y))
       (* (numer y) (denom x))))

(define (print-rat x)
  (display (numer x))
  (display "/")
  (display (denom x)))

(define one-half (make-rat 1 2))
(define one-third (make-rat 1 3))

(print-rat one-half)
(display " + ")
(print-rat one-third)
(display " = ")
(print-rat (add-rat one-half one-third))
(newline)

(print-rat one-half)
(display " * ")
(print-rat one-third)
(display " = ")
(print-rat (mul-rat one-half one-third))
(newline)

(print-rat one-third)
(display " + ")
(print-rat one-third)
(display " = ")
(print-rat (add-rat one-third one-third))
(newline)
