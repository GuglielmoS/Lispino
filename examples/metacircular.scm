;; SICP Metacircular Evaluator

;; keep a copy of the evaluator's apply
(define apply-in-underlying-scheme apply)

;; redefine the apply function
(define (apply procedure arguments)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure 
           procedure 
           arguments))
        ((compound-procedure? procedure)
         (eval-sequence
           (procedure-body procedure)
           (extend-environment
             (procedure-parameters procedure)
             arguments
             (procedure-environment procedure))))
        (else
          (error "Unknown procedure type -- APPLY"))))

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp)
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp)))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
          (error "Unknown expression type -- EVAL"))))

(define (list-of-values exps env)
  (if (no-operands? exps)
    '()
    (cons (eval (first-operand exps) env)
          (list-of-values (rest-operands exps) env))))

(define (eval-if exp env)
  (if (true? (eval (if-predicate exp) env))
    (eval (if-consequent exp) env)
    (eval (if-alternative exp) env)))

(define (eval-sequence exps env)
  (cond ((last-exp? exps) (eval (first-exp exps) env))
        (else (begin (eval (first-expr exps) env)
                     (eval-sequence (rest-exps exps) env)))))

(define (eval-assignment exp env)
  (set-variable-value! (assignment-variable exp)
                       (eval (assignment-value exp) env)
                       env)
  'ok)

(define (eval-definition exp env)
  (define-variable! (definition-variable exp)
                    (eval (definition-value exp) env)
                    env)
  'ok)

(define (self-evaluating? exp)
  (cond ((null? exp)   #t)
        ((number? exp) #t)
        ((string? exp) #t)
        (else #f)))

(define (variable? exp) (symbol? exp))

(define (quoted? exp)
  (tagged-list? exp 'qt))

(define (text-of-quotation exp)
  (car (cdr exp)))

(define (tagged-list? exp tag)
  (if (pair? exp)
    (eq? (car exp) tag)
    #f))

(define (assignment? exp)
  (tagged-list? exp 'set!))

(define (assignment-variable exp) (car (cdr exp)))
(define (assignment-value exp) (car (cdr (cdr exp))))

(define (definition? exp)
  (tagged-list? exp 'def))
(define (definition-variable exp)
  (if (symbol? (car (cdr exp)))
    (car (cdr exp))
    (car (car (cdr exp)))))
(define (definition-value exp)
  (if (symbol? (car (cdr exp)))
    (car (cdr (cdr exp)))
    (make-lambda (cdr (car (cdr exp))) ; formal
                 (cdr (cdr exp)))))

(define (lambda? exp) (tagged-list? exp 'fun))
(define (lambda-parameters exp) (car (cdr exp)))
(define (lambda-body exp) (cdr (cdr exp)))

(define (make-lambda parameters body)
  (cons 'fun (cons parameters body)))

(define (if? exp) (tagged-list? exp 'when))
(define (if-predicate exp) (car (cdr exp)))
(define (if-consequent exp) (car (cdr (cdr exp))))
(define (if-alternative exp)
  (if (not (null? (cdr (cdr (cdr exp)))))
    (car (cdr (cdr (cdr exp))))
    'false))

(define (make-if predicate consequent alternative)
  (list 'if predicate consequent alternative))

(define (begin? exp) (tagged-list? exp 'progn))
(define (begin-actions exp) (cdr exp))
(define (last-exp? seq) (null? (cdr seq)))
(define (first-exp seq) (car seq))
(define (rest-exps seq) (cdr seq))

(define (sequence->exp seq)
  (cond ((null? seq) seq)
        ((last-exp? seq) (first-exp seq))
        (else (make-begin seq))))
(define (make-begin seq) (cons 'progn seq))

(define (application? exp) (pair? exp))
(define (operator exp) (car exp))
(define (operands exp) (cdr exp))
(define (no-operands? ops) (null? ops))
(define (first-operand ops) (car ops))
(define (rest-operands ops) (cdr ops))

(define (cond? exp) (tagged-list? exp 'case))
(define (cond-clauses exp) (cdr exp))
(define (cond-else-clause? clause)
  (eq? (cond-predicate clause) 'else))
(define (cond-predicate clause) (car clause))
(define (cond-actions clause) (cdr clause))
(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))
(define (expand-clauses clauses)
  (if (null? clauses)
    'false
    (let ((first (car clauses))
          (rest (cdr clauses)))
      (if (cond-else-clause? first)
        (if (null? rest)
          (sequence->exp (cond-actions first))
          (error "ELSE clause isn't last -- COND->IF"))
        (make-if (cond-predicate first)
                 (sequence->exp (cond-actions first))
                 (expand-clauses rest))))))

(define (true? x)
  (not (eq? x #f)))

(define (false? x)
  (eq? x #f))

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))
(define (compound-procedure? p)
  (tagged-list? p 'procedure))
(define (procedure-parameters p) (car (cdr p)))
(define (procedure-body p) (car (cdr (cdr p))))
(define (procedure-environment p) (car (cdr (cdr (cdr p)))))

(define (enclosing-environment env) (cdr env))
(define (first-frame env) (car env))
(define the-empty-environment '())
(define (make-frame variables values)
  (cons variables values))
(define (frame-variables frame) (car frame))
(define (frame-values frame) (cdr frame))
(define (add-binding-to-frame! var val frame)
  (set-car! frame (cons var (car frame)))
  (set-cdr! frame (cons val (cdr frame))))

(define (extend-environment vars vals base-env)
  (if (= (length vars) (length vals))
    (cons (make-frame vars vals) base-env)
    (if (< (length vars) (length vals))
      (error "Too many arguments supplied")
      (error "Too few arguments supplied"))))

(define (lookup-variable-value var env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (car vals))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
      (error "Unbound variable")
      (let ((frame (first-frame env)))
        (scan (frame-variables frame)
              (frame-values frame)))))
  (env-loop env))

(define (set-variable-value! var val env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (set-car! vals val))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
      (error "Unbound variable -- SET!")
      (let ((frame (first-frame env)))
        (scan (frame-variables frame)
              (frame-values frame)))))
  (env-loop env))

(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (begin
      (define (scan vars vals)
        (cond ((null? vars)
               (add-binding-to-frame! var val frame))
              ((eq? var (car vars))
               (set-car! vals val))
              (else (scan (cdr vars) (cdr vals)))))
      (scan (frame-variables frame)
        (frame-values frame)))))

(define (setup-environment)
  (let ((initial-env
          (extend-environment (primitive-procedures-names)
                              (primitive-procedures-objects)
                              the-empty-environment)))
    (begin
      (define-variable! 'true #t initial-env)
      (define-variable! 'false #f initial-env)
      initial-env)))

(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))

(define (primitive-implementation proc) (car (cdr proc)))

(define primitive-procedures
  (list 
    ;; list
    (list 'list list)
    (list 'cons cons)
    (list 'car car)
    (list 'cdr cdr)
    ;; math
    (list '* *)
    (list '+ +)
    (list '- -)
    (list '/ /)
    (list 'remainder remainder)
    ;; equality
    (list '= =)
    (list 'eq? eq?)))

(define (primitive-procedures-names)
  (map car primitive-procedures))
(define (primitive-procedures-objects)
  (map (lambda (proc) (list 'primitive (car (cdr proc))))
       primitive-procedures))

(define (apply-primitive-procedure proc args)
  (apply-in-underlying-scheme
    (primitive-implementation proc) args))

(define the-global-environment (setup-environment))

(define (meta-repl)
  (display "[MetaEval]>>> ")
  (let ((input (read)))
    (if (not (equal? input 'quit))
      (begin
        (display (eval input the-global-environment))
        (newline)
        (meta-repl))
      'quit)))

(meta-repl)
