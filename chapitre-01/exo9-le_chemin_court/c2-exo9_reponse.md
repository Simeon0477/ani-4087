# Exercice - Le Chemin Court

## Énoncé
Écrivez la vitesse angulaire moyenne entre deux orientations séparées de dt, avec le forçage du chemin court.

Puis retirez le forçage et trouvez deux quaternions pour lesquels le résultat devient absurde. Rendez les deux valeurs, avec et sans.

## Résultats
Pour un quaternion q1 *(0, 0, 0, 1)*, 
et quaternion q2  *(0,0,-0.0049999,-0.9999875)*
et d'un *dt = 0.01 secondes* 
nous obtenons :

    Entrez q1 (x y z w)
    0
    0
    0
    1
    Entrez q2 (x y z w)
    0
    0
    -0.0049999
    -0.9999875
    Entrez dt, en secondes
    0.01
    Sans forcage : 0.0000  0.0000  -627.3079   (norme : 627.3079 rad/s)
    Avec forcage : 0.0000  -0.0000  1.0000   (norme : 1.0000 rad/s)

Sans forçage nous constatons donc une explosion de la norme, comme si la personne avait fait des tours complets en plus sur un petit mouvement, d'où l'importance de la recherche du chemin le plus court.

## Code
[chemin_court.cpp](./chemin_court.cpp)

