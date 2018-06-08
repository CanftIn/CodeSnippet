(define a 1)
(begin 
    (display a)
    (newline))

(set! a 2)
(begin 
    (display a)
    (newline))

(let ((a 3))
    (display a)
    (newline))


(let ((a 3)) (set! a 4)
    (display a)
    (newline))


(let ((a 3)) (define a 5) 
    (display a)
    (newline))
