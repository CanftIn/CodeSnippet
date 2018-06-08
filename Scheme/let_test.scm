(begin
    (display
        (let ((x 2) (y 3))
            (+ x y)))
    (newline))

(begin
    (display
        (let ((f +))
            (f 2 3)))
    (newline)
    (display
        (let ((f +) (x 2))
            (f x 3)))
    (newline)
    (display
        (let ((f +) (x 2) (y 3))
            (f x y)))
    (newline))
