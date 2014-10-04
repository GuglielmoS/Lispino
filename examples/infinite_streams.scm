(define (fibgen a b)
  (lazy-cons a (fibgen b (+ a b))))

(define fibs (fibgen 0 1))

(define ones (lazy-cons 1 ones))

