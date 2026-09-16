# Exercice - L'ordre Inversé

## Énoncé
Reprenez l'exercice précédent et écrivez une seconde fonction qui applique la translation d'abord et la rotation ensuite.

Affichez les deux résultats pour le même point. Puis trouvez une pose et un point pour lesquels les deux coïncident, et dites pourquoi.

## Résultats
Pour le vecteur *(0.4, 0.6, 1)*, 
avec la pose constitué de la position *(-1, 0, 2)*
et du quaternion *(0.2, 0.74, -0.81, -1.2)*,
nous obtenons :

**Rotation puis translation**

    X : -4.6518
    Y : -0.0581
    Z :  1.3983

**Translation puis rotation**

    X : -6.4444
    Y : -3.7357
    Z : -2.4041

Les deux ordres divergent ici, comme attendu : rotation-translation fait tourner l'objet sur lui-même, translation-rotation le fait orbiter autour de l'origine.

## Quand les deux coïncident

En notant *R* la rotation et *t* la translation :

- Rotation puis translation : `R(p) + t`
- Translation puis rotation : `R(p + t) = R(p) + R(t)`

Les deux expressions sont égales si et seulement si `R(t) = t` : la translation doit être invariante par la rotation. Cette condition ne dépend que de la pose, jamais du point.

Exemple : position *(0, 5, 0)* (translation le long de l'axe Y), quaternion *(0, 0.7071068, 0, 0.7071068)* (rotation de 90° autour de Y). Une rotation autour de Y laisse invariant tout vecteur porté par Y, donc `R(t) = t`. Pour n'importe quel point, par exemple *(2, 3, 4)*, les deux fonctions donnent le même résultat.

    Entrez les coordonnees de la pose
    0
    5
    0
    Entrez les coordonnees du quaternion
    0
    0.7071068
    0
    0.7071068
    Entrez les coordonnees de la position actuelle
    2
    3
    4
    Rotation puis Translation :
    X : 4.0000
    Y : 8.0000
    Z :  -2.0000

    Translation puis Rotation :
    X : 4.0000
    Y :  8.0000
    Z :   -2.0000

## Code
[l_inverse.cpp](./l_inverse.cpp)

