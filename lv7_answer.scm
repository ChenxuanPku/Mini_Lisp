(define src (list 12 71 2 15 29 82 87 8 18 66 81 25 63 97 40 3 93 58 53 31 47))

(define (qsort lst)
  (
    if (null? lst) '()
    (
        let(
           (smaller ( filter (lambda (x) (< x (car lst))) lst ))
           (bigger (filter (lambda (x) (>= x (car lst))) lst ))
        )
        (append (qsort smaller) (qsort bigger))
    )
  )
)

(displayln (qsort src))