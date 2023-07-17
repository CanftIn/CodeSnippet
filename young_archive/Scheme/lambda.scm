(display
    ((lambda (x) (+ x x)) (* 3 4)))
(newline)

(display
    (let ((f +))
        ((lambda (x) (f x x)) (* 3 4)))
        )
(newline)

(display
    (let ((double (lambda (x) (+ x x))))
        (list   (double (* 3 4))
                (double (/ 99 11))
                (double (- 2 7)))))
(newline)