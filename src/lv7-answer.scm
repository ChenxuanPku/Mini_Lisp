(define src (12 71 2 15 29 82 87 8 18 66 81 25 63 97 40 3 93 58 53 31 47))

(define (qsort lst)
  (
    if (null? lst) '()
    (
        let(
           (pivot (car lst))
           (smaller ( filter (lambda (x) (< x pivot)) lst ))
           (bigger (filter (lambda (x) (>= x pivot)) lst ))
        )
        (append (qsort smaller) (qsort bigger))
    )
  )
)

(displayln (qsort src))