# Exercice - La Matrice de vue

## Énoncé
Écrivez les deux versions : celle qui inverse la matrice de la pose par une inversion générale, et celle qui construit directement le conjugué et la translation opposée.

Comparez les seize coefficients. Puis passez une pose dégénérée à la première et regardez ce qu'elle rend.

## Résultats
Pour une longueur de bras de *0.3 m*, 
et d'un avant-bras de  *0.25 m*
et du quaternion de l'épaule *(0.1221, 0.4517, -0.4945, -0.7325)* 
nous obtenons :

    --- Bras au repos ---
    Coude : 0.3000  0.0000  0.0000
    Main  : 0.5500  0.0000  0.0000

    Entrez le quaternion de rotation de l'epaule (qx qy qz qw)
    0.1221
    0.4517
    -0.4945
    -0.7325

    --- Apres rotation de l'epaule ---
    Coude : 0.0309  0.2504  0.1623
    Main  : 0.0566  0.4591  0.2975

    --- Verification (longueurs conservees) ---
    Epaule-Coude  avant : 0.3000   apres : 0.3000
    Coude-Main    avant : 0.2500   apres : 0.2500

Les orientations du coude et la main suivent effectivement le mouvement de l'épaule tout en conservant leurs longueurs respecitves.

## Code
[bras.cpp](./bras.cpp)

