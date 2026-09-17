# Exercice - Le Coût du Doublement

## Énoncé
Reprenez le même programme et mesurez le temps que prend son rendu seul, sans la logique. Puis estimez ce que coûterait ce rendu fait deux fois, et ce qu'il resterait pour le reste.

Rendez la mesure, l'estimation, et votre conclusion sur ce qu'il faudrait réduire.

## Résultats
| Mesure | Valeur |
|---|---|
| Rendu le plus long | 4.616 ms |
| Estimation pour 2 rendus | 8.632 ms |
| Temps restant pour 11 ms | 2.368 ms |

## Conclusion
En supposant que deux rendus aient un coût approximativement deux fois supérieur, leur coût estimé serait de :

    2 × 4.616 = 8.632 ms

Avec un budget de 11 ms par image, le temps disponible pour le reste du programme serait donc :

    11 − 8.632 = 2.368 ms

Cette mesure montre que le principal point à réduire est le coût du rendu, particulièrement si deux rendus sont nécessaires