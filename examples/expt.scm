(define (recur-expt b n)
  (if (= n 0)
    1
    (* b (recur-expt b (- n 1)))))

(display "10^10 = " (recur-expt 10 10))
(newline)
