(define (recur-expt b n)
  (if (zero? n)
    1
    (* b (recur-expt b (- n 1)))))

(display "10^10 = " (recur-expt 10 5))
(newline)
