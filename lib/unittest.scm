;; define some useful function to use for testing
(define (show-message status message)
  (if status
    (display "[OK]   " message)
    (display "[FAIL] " message))
  (newline))

(define (assert-equals expected actual message)
  (show-message (equal? expected actual) message))

(define (assert-true value message)
  (show-message (equal? value #t) message))

(define (assert-false value message)
  (show-message (equal? value #f) message))
