; 1.
(defun binomial (n k) ; slower than the second version
    (if (or (= k 0) (= n k))
        1
        (+ (binomial (- n 1) k) (binomial (- n 1) (- k 1)))))

; 2.
(defun pascals-triangle-row (n)
    (if (= n 0)
        '(1)
        (let ((previous-row (pascals-triangle-row (- n 1))))
        (cons 1 (append (mapcar #'+ previous-row (cdr previous-row)) '(1))))))

(defun binomial2 (n k)
    (nth k (pascals-triangle-row n)))

; 3.
(defun merge-lists (left right)
    (cond ((null left) right)
          ((null right) left)
          ((<= (car left) (car right)) (cons (car left) (merge-lists (cdr left) right)))
          (t (cons (car right) (merge-lists left (cdr right))))))

(defun merge-sort (list)
    (let ((len (list-length list)))
    (cond ((null list) list)
          ((= len 1) list)
          (t (merge-lists (merge-sort (subseq list 0 (ceiling len 2))) (merge-sort (subseq list (ceiling len 2))))))))

; 4.
(defun gcd-extended (a b)
    (if (= a 0)
        (values b 0 1)
        (multiple-value-bind (g x1 y1) (gcd-extended (mod b a) a)
        (values g (- y1 (* (floor (/ b a)) x1) ) x1))))

(defun diophantine (a b)
    (multiple-value-bind (g x y) (gcd-extended (abs a) (abs b))
        (let ((x0 (if (>= a 0) x (- x)))
              (y0 (if (>= b 0) y (- y))))
    (list x0 y0 g))))

; 5.
(defun divisor (n d)
    (and (> n 1) (> d 1)
    (if (= (mod n d) 0)
        d
        (divisor n (- d 1)))))

(defun prime-factors (n)
    (if (= n 1)
        ()
        (let ((d (divisor n (isqrt n))))
            (if d
                (nconc (prime-factors (/ n d)) (prime-factors d))
                (list n)))))

; 6.
(defun is-co-prime (a b)
    (= (gcd a b) 1))

(defun totient(n &optional (i 2) (counter 1)) ; slower than the second version
    (cond ((> i n) counter)
          ((is-co-prime n i) (totient n (+ i 1) (+ counter 1)))
          (t (totient n (+ i 1) counter))))

; 7.
(defun totient2 (n)
    (nth-value 0 (floor (* n (reduce #'* (mapcar #'(lambda (p) (- 1 (/ 1 p))) (remove-duplicates (prime-factors n))))))))

; 8.
(defun is-prime (n &optional (d (isqrt n)))
    (and (>= n 2)
        (or (= d 1)
            (and (/= (mod n d) 0)
                (is-prime n (- d 1))))))

(defun primes (n &optional (i 2))
    (cond ((<= n 1) nil)
          ((is-prime i) (cons i (primes (- n 1) (+ i 1))))
          (t (primes (- n 1) (+ i 1)))))
