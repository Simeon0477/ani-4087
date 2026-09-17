# Exercice - L'extrapolation

## Énoncé
Écrivez la fonction qui avance une pose de dt secondes à vitesses constantes, linéaire et angulaire.

Votre programme lit une pose, ses deux vitesses et une durée, et affiche la pose extrapolée. Traitez le cas d'une vitesse angulaire nulle sans diviser par zéro.

## Résultats
Pour la pose constituée de la position *(-1, 0, 2)*
et du quaternion *(0.1221, 0.4517, -0.4945, -0.7325)*, 
une vitesse linéaire *(1, 1, 2)*, une vitesse angulaire *(0, 0.2, 0.56)* et un *dt = 2 secondes*
nous obtenons :

    Entrez la position de la pose
    -1
    0
    2
    Entrez le quaternion unitaire de la pose
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez la vitesse lineaire, m/s (x y z)
    1
    1
    2
    Entrez la vitesse angulaire, rad/s (x y z)
    0
    0.2
    0.56
    Entrez dt, en secondes
    2

    Pose extrapolee :
    Position   : 1.0000  2.0000  6.0000
    Quaternion : -0.2303  0.3006  -0.8191  -0.4310

Avec une vitesse angulaire nulle :

    Entrez la position de la pose
    -1
    0
    2
    Entrez le quaternion unitaire de la pose
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez la vitesse lineaire, m/s (x y z)
    1
    1
    2
    Entrez la vitesse angulaire, rad/s (x y z)
    0
    0
    0
    Entrez dt, en secondes
    2

    Pose extrapolee :
    Position   : 1.0000  2.0000  6.0000
    Quaternion : 0.1221  0.4517  -0.4945  -0.7325

Il y'a conservation des orientations en cas de vitesse angulaire nulle.

Avec un *dt = 20 s* :

    Entrez la position de la pose
    -1
    0
    2
    Entrez le quaternion unitaire de la pose
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez la vitesse lineaire, m/s (x y z)
    1
    1
    2
    Entrez la vitesse angulaire, rad/s (x y z)
    0
    0.2
    0.56
    Entrez dt, en secondes
    20

    Pose extrapolee :
    Position   : 19.0000  20.0000  42.0000
    Quaternion : 0.3108  0.4697  -0.2252  -0.7950

La question à se poser maintenant est de savoir si le corps conservera le même mouvement sur plus de 20 secondes, ce qui est fort improbable, c'est pour cela qu'il est dit que le modèle à vitesse constante ment plus qu'il n'aide.

## Code
[extrapolation](./extrapolation.cpp)

