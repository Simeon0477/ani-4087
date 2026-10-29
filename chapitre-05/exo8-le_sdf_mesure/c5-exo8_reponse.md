# Exercice - Le SDF, mesuré

## Enoncé 
### Ce que vous allez faire
Refaire le panneau « Sortie » de deux façons, avec un atlas ordinaire et avec un atlas SDF, puis comparer de loin, de près, et en mémoire.

### Comment faire
1. Reprenez le code de votre panneau « Sortie » dans `sdf.cpp`. S'il n'existe pas encore, l'exercice « Un panneau au-dessus de la porte » donne les appels de l'atlas et de l'image.
2. Construisez deux atlas avec Inter à 32 pixels : un ordinaire, et un autre avec `atlas.sdfMode = true;` et `atlas.sdfSpread = 6;` avant `Build`.
3. Construisez aussi un troisième atlas, ordinaire, à 128 pixels. Relevez les trois tailles, `texWidth` et `texHeight`, dans `atlas.txt`.
4. Écrivez-les en trois lignes : `ordinaire 32 : L x H`, `sdf 32 : L x H`, puis `ordinaire 128 : L x H`.
5. Dans votre salle, une texture s'affiche telle quelle : rien n'y applique le nuanceur SDF du moteur. Vous allez donc faire sur le processeur, une fois, ce que ce nuanceur ferait.
6. Fabriquez l'image du panneau à huit fois la taille des lettres de l'atlas : sa hauteur vaut `8 * (ascent - descent)`. Faites-le pour les deux atlas de 32 pixels. Lisez l'atlas par interpolation bilinéaire, entre les quatre pixels voisins.
7. Pour l'atlas ordinaire, la valeur lue divisée par 255 est la couverture. Pour l'atlas SDF, appliquez la règle du nuanceur `kNkFontFragSDF` du moteur, recopiée ici avec la définition de `smoothstep` :
   ```glsl
   float dist  = valeur / 255.0;
   float alpha = smoothstep(0.5 - s, 0.5 + s, dist);
   
   float smoothstep(float a, float b, float x) {
       float t = clamp((x - a) / (b - a), 0.0, 1.0);
       return t * t * (3.0 - 2.0 * t);
   }
   ```
8. Écrivez cette règle en C++, dans une fonction nommée `smoothstep`. `s` règle la douceur du bord : essayez quelques valeurs, et gardez celle qui donne le bord le plus net sans escalier.
9. Posez les deux panneaux au-dessus de la porte, l'un après l'autre. Prenez quatre captures : `ordinaire-3m.png`, `ordinaire-50cm.png`, `sdf-3m.png` et `sdf-50cm.png`. Votre salle se capture seule : `MASALLE_SHOT=120` prend l'image 120, et `MASALLE_SHOT_PATH` lui donne son nom.
10. Pour trois mètres, la caméra est en (−0,70 ; 1,70 ; 1,00), et pour cinquante centimètres en (−0,70 ; 2,20 ; −1,50). Elle regarde le panneau.
11. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `A trois metres :`, `A cinquante centimetres :`, puis `Ma conclusion :`. La conclusion parle aussi de mémoire.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo8-le_sdf_mesure/` et mettez-y exactement ces fichiers, avec ces noms :

- `sdf.cpp`
- `atlas.txt`
- `ordinaire-3m.png`
- `ordinaire-50cm.png`
- `sdf-3m.png`
- `sdf-50cm.png`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
