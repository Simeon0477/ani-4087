# Exercice - Quatre filtres, une mesure

## Enoncé 
### Ce que vous allez faire
Réduire la même image de 2048 à 256 pixels de côté avec les quatre filtres du moteur, chronométrer chacun, et comparer les quatre résultats pixel par pixel.

### Comment faire
1. Partez d'une photo à vous. Réduisez-la d'abord en 2048 × 2048 avec `Resize`, et gardez ce résultat : c'est votre source.
2. Dans `filtres.cpp`, réduisez cette source en 256 × 256 avec chacun des quatre filtres : `NkResizeFilter::NK_NEAREST`, `NK_BILINEAR`, `NK_BICUBIC` et `NK_LANCZOS3`. L'appel est `source.Resize(256, 256, filtre)`.
3. Chronométrez chaque filtre avec `NkChrono`, de `NKTime/NkChrono.h` : `Elapsed().ToMicroseconds()`. Répétez chaque réduction vingt fois et gardez la moyenne.
4. Enregistrez les quatre résultats avec `SavePNG` : `nearest.png`, `bilinear.png`, `bicubic.png` et `lanczos3.png`.
5. Comparez chaque résultat à celui du bilinéaire, pixel par pixel, avec `GetPixel`. Comptez les pixels qui diffèrent sur au moins un canal.
6. Écrivez les quatre lignes dans `mesures.txt`, sous la forme `NK_BICUBIC : T us, differences : D`. T est la moyenne en microsecondes, D le nombre de pixels qui diffèrent.
7. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Ce que la comparaison montre :`, `L'ecart de temps que j'accepte :`, puis `Dans quel contexte :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo5-quatre_filtres_une_mesure/` et mettez-y exactement ces fichiers, avec ces noms :

- `filtres.cpp`
- `mesures.txt`
- `nearest.png`
- `bilinear.png`
- `bicubic.png`
- `lanczos3.png`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
