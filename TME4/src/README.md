###TME 4

Question 2.
    Si Alice envoie 1000 euros à Bob qui a 0 euros sur son compte, et que Bob souhaite envoyer 500 euros à Carlos, mais qu'il n'a pas encore été crédité (étant donné que les opérations crédit et débit ne sont pas atomiques), il ne pourra pas avoir envoyer l'argent alors que c'est techniquement son argent.
    Cependant il n'y a pas de datarace.

Question 5.
    Le programme se bloque car le même thread essaie de lock plusieurs fois le même mutex qui est celui de la classe Compte.

Question 6.
    Chaque Compte a son mutex. L'opération de transfert du débiteur : si un compte est débiteur dans une thread et créditeur dans une autre thread, ça peut bloquer.

Question 7&8. 
    Même si les opérations de transfert son protégée par un mutex,
    le thread comptable pourrait lire des informations incohérentes si une opération de transfert est en cours:
    Par exemple, le thread comptable lit le solde du compte A (1000), puis le thread transfert débite 100 de A et crédite 100 de B. Cependant, lorsque le thread comptable lit à nouveau le solde de A, il pourrait obtenir l'ancienne valeur (1000) au lieu de la nouvelle (900).
    Le comptable doit donc bloquer les modification (transferts) des comptes qu'il traite.

Question 10.
    On pourrait verrouiller tout les comptes comptabilisé et les dévérouiller à la fin de chaque comptabilisation OU l'inverse on verrouille tout et on déverouille ce qui est fait au fur et à mesure pour permettre les opérations sur les comptes comptabilisé 

