;; test the id function
(define (test-id message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-equals nil (id nil) "the id of nil is nil")
  (assert-equals '() (id '()) "the id of '() is '()")
  (assert-equals 1 (id 1) "the id of 1 is 1")
  (assert-false (= '(1 2) (id '(1 2))) "the id of '(1 2) is not the same '(1 2)")
  (assert-equals "str" (id "str") "the id of \"str\" is \"str\""))

;; test the null function
(define (test-null message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-true (null? nil) "null? nil is true")
  (assert-true (null? '()) "null? '() is true")
  (assert-false (null? '(1)) "null? '(1) is false")
  (assert-false (null? 0) "null? 0 is false")
  (assert-false (null? "str") "null? \"str\" is false"))

;; test the null function
(define (test-not message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-false (not #t) "not true is false")
  (assert-true (not #f) "not false is true"))

;; test the and function
(define (test-and message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-false (and #f #f) "false && false is false")
  (assert-false (and #f #t) "false && true is false")
  (assert-false (and #t #f) "true && false is false")
  (assert-true (and #t #t) "true && true is true"))

;; test the and function
(define (test-or message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-false (or #f #f) "false || false is false")
  (assert-true (or #f #t) "false || true is true")
  (assert-true (or #t #f) "true || false is true")
  (assert-true (or #t #t) "true || true is true"))

;; test the length function
(define (test-length message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-equals 0 (length nil) "the length of nil is 0")
  (assert-equals 0 (length '()) "the length of '() is 0")
  (assert-equals 1 (length '(1)) "the length of '(1) is 1")
  (assert-equals 2 (length '(1 2)) "the length of '(1 2) is 2")
  (assert-equals 5 (length '(1 2 3 4 5)) "the length of '(1 2 3 4 5) is 5"))

;; test the sum function
(define (test-sum message)
  (display "TESTS FOR: " message)
  (newline)
  (assert-equals 0 (sum nil) "the sum of nil is 0")
  (assert-equals 0 (sum '()) "the sum of '() is 0")
  (assert-equals 1 (sum '(1)) "the sum of '(1) is 1")
  (assert-equals 3 (sum '(1 2)) "the sum of '(1 2) is 3")
  (assert-equals 55 (sum '(1 2 3 4 5 6 7 8 9 10)) "the length of '(1 2 3 4 5 6 7 8 9 10) is 55"))

;; run the tests
(test-id "id")
(test-null "null?")
(test-not "not")
(test-and "and")
(test-or "or")
(test-length "length")
(test-sum "sum")
