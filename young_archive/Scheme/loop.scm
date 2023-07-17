(define factorial
    (lambda (n) 
        (do ((i n (- i 1)) (a 1 (* a i)))
            ((zero? i) a))))

(display (factorial 10))
(newline)