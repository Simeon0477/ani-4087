# Exercice - La Composition

## Énoncé
Écrivez la composition de deux poses, puis vérifiez sur un cas que composer puis appliquer donne le même résultat qu'appliquer l'une après l'autre.

Affichez les deux points obtenus et leur écart.

## Résultats
Pour le vecteur *(0.4, 0.6, 1)*, 
avec la pose parent constituée de la position *(-1, 0, 2)*
et du quaternion *(0.1221, 0.4517, -0.4945, -0.7325)* et la pose enfant de la position *(0, 2, -3)* et de son quaternion 
*(0.1221, 0.4517, -0.4945, -0.7325)*, 
nous obtenons :

    Entrez les coordonnees de la pose parent
    -1
    0
    2
    Entrez les coordonnees du quaternion parent
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees de la pose enfant
    0
    2
    -3
    Entrez les coordonnees du quaternion enfant
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees du point
    0.4
    0.6
    1
    PAR COMPOSITION :
    X : -0.5283
    Y : 0.9020
    Z : -1.5333

    PAR ETAPES :
    X : -0.5283
    Y : 0.9021
    Z : -1.5333

    Ecart : 0.0001

Au vu de l'écart quasi nul, nous pouvons donc conclure que la composition est équivalente à l'application successive des deux poses.

## Code
[composition.cpp](./composition.cpp)

