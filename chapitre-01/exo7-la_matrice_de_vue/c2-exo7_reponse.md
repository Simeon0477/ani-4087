# Exercice - La Matrice de vue

## Énoncé
Écrivez les deux versions : celle qui inverse la matrice de la pose par une inversion générale, et celle qui construit directement le conjugué et la translation opposée.

Comparez les seize coefficients. Puis passez une pose dégénérée à la première et regardez ce qu'elle rend.

## Résultats
Pour la pose constituée de la position *(-1, 0, 2)*
et du quaternion *(0.1221, 0.4517, -0.4945, -0.7325)*
nous obtenons :

    Entrez la position de la pose
    -1
    0
    2
    Entrez le quaternion unitaire de la pose
    0.1221
    0.4517
    0.4945
    -O.7325

    === Comparaison sur une pose valide ===

    Inversion generale (Gauss-Jordan) :
    13.2798   -1.5099   -1.6529   16.5857
    -1.5099    8.1024   -6.1148   10.7198
    -1.6529   -6.1148    6.9937  -15.6404
        0.0000    0.0000    0.0000    1.0000

    Inversion analytique (conjugue + translation opposee) :
        0.1029    0.1103    0.1208   -0.1386
        0.1103    0.4811    0.4467   -0.7832
        0.1208    0.4467    0.5621   -1.0035
        0.0000    0.0000    0.0000    1.0000

    Ecart maximum sur les seize coefficients : 16.7243

    === Pose degeneree passee a l'inversion generale ===

    Matrice degeneree (rang deficient) :
        1.0000    0.0000    0.0000    5.0000
        0.0000    1.0000    0.0000    3.0000
        0.0000    1.0000    0.0000    3.0000
        0.0000    0.0000    0.0000    1.0000

    Ce que rend InverserGenerale :
        1.0000    0.0000    0.0000    0.0000
        0.0000    1.0000    0.0000    0.0000
        0.0000    0.0000    1.0000    0.0000
        0.0000    0.0000    0.0000    1.0000

Aucune erreur, aucun message : la fonction rend l'identite
comme si la pose etait neutre, alors que la matrice d'entree
ne represente aucune transformation valide.

## Code
[matrice_vue.cpp](./matrice_vue.cpp)

