# Exercice - Treize formats, une image

## Enoncé 
### Ce que vous allez faire
Faire écrire une même photo dans cinq formats par le moteur, la relire dans chacun, et choisir le format d'une texture de mur.

### Comment faire
1. Prenez une photographie avec votre téléphone : un mur, un sol, du béton. Copiez-la dans le dossier de votre projet.
2. Dans `formats.cpp`, chargez-la dans une variable : `NkImage photo;` puis `photo.Load("photo.jpg")`, avec votre nom de fichier. `NkImage` est dans `NKImage/Core/NkImage.h`. Testez le retour de `Load` avant d'aller plus loin.
3. Faites écrire la photo par le moteur dans cinq formats de votre choix. `NkImage` porte `SavePNG`, `SaveJPEG`, `SaveBMP`, `SaveTGA`, `SaveQOI`, `SavePPM`, `SaveGIF`, `SaveHDR` et `SaveEXR`.
4. Rechargez chacun des cinq fichiers dans un nouveau `NkImage`. Pour chacun, affichez sa taille sur le disque en octets, puis `Width()` et `Height()`.
5. Écrivez les cinq résultats dans `formats.txt`, un par ligne, sous la forme `format : N octets, L x H`. N, L et H sont des nombres. Un fichier qui ne se relit pas s'écrit `format : N octets, illisible`.
6. Dans `choix.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Mon format pour un mur :`, `Pourquoi :`, puis `Ce qui m'a surpris :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo1-treize_formats_une_image/` et mettez-y exactement ces fichiers, avec ces noms :

- `formats.cpp`
- `formats.txt`
- `choix.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
