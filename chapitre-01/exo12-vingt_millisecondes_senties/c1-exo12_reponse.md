# Exercice - Vingt millisecondes senties

## Énoncé

Écrivez un programme sur écran ordinaire qui suit la souris avec un retard réglable, de zéro à deux cents millisecondes. Faites-le essayer à cinq personnes et notez, pour chacune, le retard à partir duquel elle dit sentir quelque chose.

Rendez les cinq seuils. Comparez au budget de vingt millisecondes et dites pourquoi le seuil est bien plus bas dans un casque.

## Témoignages

### Personne 1 — seuil : 35 ms

> « À 0 ça va, je sens rien. Mais vers 35 ms là, je commence à voir que le rond il suit plus directement ma souris. Ça devient un peu bizarre, comme si ça répondait en retard. À partir de là ça me dérange. »

### Personne 2 — seuil : 50 ms

> « Moi j'ai commencé à sentir vers 50 ms. En dessous franchement ça va, je remarque même pas trop. Mais à 50 ms et plus, quand je bouge vite la souris, le rond reste derrière et ça devient agaçant. »

### Personne 3 — seuil : 25 ms

> « Moi j'ai senti assez vite hein. Vers 25 ms déjà ça me gênait un peu. Quand je déplace la souris, j'ai l'impression que le truc veut pas suivre normalement. Ça fatigue un peu les yeux aussi quand tu fais ça plusieurs fois. »

### Personne 4 — seuil : 40 ms

> « Jusqu'à 30 ms ça passe encore. Mais vers 40 ms là, je commence vraiment à remarquer le décalage. Surtout quand je bouge la souris rapidement, le rond donne l'impression de traîner derrière. C'est pas grave mais c'est désagréable. »

### Personne 5 — seuil : 60 ms

> « Moi il faut quand même un peu de retard avant que ça me dérange. À 40 ou 50 ms je remarque que c'est pas instantané, mais ça va encore. À partir de 60 ms là, ça commence à m'énerver parce que le rond ne suit clairement plus ma souris. »

## Les cinq seuils

| Personne | Seuil de gêne |
|---|---:|
| Personne 1 | 35 ms |
| Personne 2 | 50 ms |
| Personne 3 | 25 ms |
| Personne 4 | 40 ms |
| Personne 5 | 60 ms |

## Comparaison avec le budget de 20 ms
Les seuils observés sont tous supérieurs à **20 ms**. Sur un écran ordinaire, les personnes testées commencent donc à trouver le retard désagréable entre **25 et 60 ms**.

Dans un casque de réalité virtuelle, le seuil doit être beaucoup plus bas car le retard entre le mouvement de la tête et l'affichage de l'image crée une discordance entre ce que voient les yeux et ce que ressent le système vestibulaire. Cela peut provoquer de l'inconfort ou des sensations de malaise.

Le budget de **20 ms** permet donc de limiter cette discordance et de conserver une expérience de réalité virtuelle confortable.

## Code
[mouse.py](./mouse.py)