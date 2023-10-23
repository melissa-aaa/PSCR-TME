###TME 4

Question 2.
    Si Alice envoie 1000 euros à Bob qui a 0 euros sur son compte, et que Bob souhaite envoyer 500 euros à Carlos, mais qu'il n'a pas encore été crédité (étant donné que les opérations crédit et débit ne sont pas atomiques), il ne pourra pas avoir envoyer l'argent alors que c'est techniquement son argent.
    Cependant il n'y a pas de datarace.

Question 5.
    Le programme se bloque car le même thread essaie de lock plusieurs fois le même mutex qui est celui de la classe Compte.

Question 6.
    Chaque Compte a son mutex. L'opération de transfert du débiteur : si un compte est débiteur dans une thread et créditeur dans une autre thread, ça peut bloquer.
