# Exercice - La Pose Appliquée

## Énoncé
Écrivez la structure Pose, avec une position et un quaternion, et la fonction qui applique une pose à un point : rotation puis translation.

Le quaternion est donné par ses quatre composantes, déjà normalisé. Votre programme lit une pose et un point, et affiche le point transformé.

## Résultats
Pour le vecteur *(0.4, 0.6, 1)*, 
avec la pose constitué de la position *(-1, 0, 2)*
et du quaternion *(0.1221, 0.4517, -0.4945, -0.7325)* (Quarternion unitaire),
nous obtenons :

    X : -2.1098
    Y : 0.3547
    Z :  2.4031

## Code
[la_pose.cpp](./la_pose.cpp)


