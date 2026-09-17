# Exercice - L'Inverse d'une Pose

## Énoncé
Écrivez Inverser(pose) à la main : conjugué du quaternion, et position opposée tournée par ce conjugué.

Vérifiez-la : appliquez la pose à un point, puis l'inverse au résultat, et affichez l'écart au point de départ. Il doit être nul aux arrondis près.

## Résultats
Pour le vecteur *(0.4, 0.6, 1)*, 
avec la pose constitué de la position *(-1, 0, 2)*
et du quaternion *(0.1221, 0.4517, -0.4945, -0.7325)*,
nous obtenons :

    Entrez les coordonnees de la pose
    -1
    0
    2
    Entrez les coordonnees du quaternion
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees de la position actuelle
    0.4
    0.6
    1
    POSE :
    X : -2.1098
    Y : 0.3547
    Z :  2.4031

    INVERSE DE LA POSE :
    X : 0.4000
    Y :  0.6000
    Z :   1.0000

    Ecart : 0.0001

L'écart entre les deux est extrement négligeable, on peut donc affirmer que notre fonction InversePose fonctionne.

[pose_inverse.cpp](./pose_inverse.cpp)

