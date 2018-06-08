(define (abs n)
    (if (< n 0)
        (- 0 n)
        n))

(define abs
    (lambda (n) 
        (cond 
            ((= n 0) 0)
            ((< n 0) (- 0 n))
            (else n))))

(let ((x 4) (y 5))
    (case (+ x y)
        ((1 3 5 7 9) 'odd)
        ((0 2 4 6 8) 'even)
        (else 'out-of-range)))
