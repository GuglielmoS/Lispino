(define ones (lazy-cons 1 ones))

(define integers (lazy-cons 1 (stream-zipWith + ones integers)))

(define fibs (lazy-cons 0 (lazy-cons 1 (stream-zipWith + (stream-cdr fibs) fibs))))

(display "First 20 fibonacci numbers: ")
(newline)
(display (stream-take fibs 20))
(newline)
