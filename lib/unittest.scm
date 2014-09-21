;; define some useful function to use for testing
(define (show-message status message)
  (if status
    (display "[OK]   " message)
    (display "[FAIL] " message))
  (newline))

(define (assert-equals expected actual message)
  (show-message (= expected actual) message))

(define (assert-true value message)
  (show-message (= value true) message))

(define (assert-false value message)
  (show-message (= value false) message))
