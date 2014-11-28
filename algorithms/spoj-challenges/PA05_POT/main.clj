(defn exp [ base pow ]
  (reduce * (repeat (bigint pow) (bigint base))))

(defn mod-exp [ base pow ]
  (if (= pow 0) 1
    (let [z (mod-exp base (bigint (/ pow 2)))]
      (if (even? pow)
        (mod (exp z 2) 10)
        (mod (* (exp z 2) base) 10)))))

(defn run [ n ]
  (when (> n 0)
    (let [ input (read-line)
           [ base pow ] (.split input " ") ]
      (println (str (mod (mod-exp (read-string base) (read-string pow)) 10)))
      (run (dec n)))))

(run (read-string (read-line)))