# Exercice — Les Trois Cadences

## Énoncé
Calculez la durée d'une image à 72, 90 et 120 hertz, au dixième de milliseconde. Pour chacune, soustrayez les huit millisecondes que prennent les capteurs, la transmission, la composition et l'affichage, et dites ce qu'il reste à votre code.

## Calculs
On sait que : 

  **Fréquence = 1 / Temps**

Ceci implique donc que : 

  **Temps = 1 / Fréquence**

Nous avons donc : 

 - **Pour 72 Hertz :**

        72 = 1 / T => T = 1 / 72

        T = 0,01388 secondes

        T = 13.8 millisecondes

    En soustraiyant les 8 millisecondes pour les autres opérations, on a:

        t = T - 8

        t = 5.8 millisecondes

    Nous obtenons donc comme temps final : *5.8 millisecondes*

 - **Pour 90 Hertz :**

        90 = 1 / T => T = 1 / 90

        T = 0,01111 secondes

        T = 11.1 millisecondes

    En soustraiyant les 8 millisecondes pour les autres opérations, on a:

        t = T - 8

        t = 3.1 millisecondes

    Nous obtenons donc comme temps final : *3.1 millisecondes*

 - **Pour 120 Hertz :**

        120 = 1 / T => T = 1 / 120

        T = 0,00833 secondes

        T = 8.3 millisecondes

    En soustraiyant les 8 millisecondes pour les autres opérations, on a:

        t = T - 8

        t = 0.3 millisecondes

    Nous obtenons donc comme temps final : *O.3 millisecondes*