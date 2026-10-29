# Exercice - Le premier mur texturé

## Enoncé 
### Ce que vous allez faire
Mettre une texture sur un mur de votre salle, avec une photo à vous, et montrer ce mur avant et après.

### Comment faire
1. Prenez en photo un mur, de la brique ou du béton. Mettez le fichier dans un dossier `murs/` de votre projet.
2. Une texture se pose en trois appels. `renderer->GetTextures()->Load(chemin)` la charge. `NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC)` crée un matériau, et `SetAlbedoMap` lui donne la texture. Le pavé la reçoit par `dc.material = mat->GetInstHandle()`. `NkMaterial` est dans `NKRenderer/Materials/NkMaterial.h`.
3. Chargez la texture une seule fois, avant la boucle, avec le renderer de la salle. Créez le matériau au même endroit.
4. Écrivez une variante de `Pave` qui reçoit ce matériau, et employez-la pour un seul mur. Mettez ce code dans `mur.cpp`.
5. Pour que la texture se répète tous les mètres au lieu d'être étirée, `NkMaterial` porte `SetTriplanarTileSize(1.0f)`. C'est facultatif.
6. Prenez une capture avant le changement, nommée `avant.png`, et une après, nommée `apres.png`, du même point de vue. Votre salle se capture seule : `MASALLE_SHOT=120` prend l'image 120, et `MASALLE_SHOT_PATH` lui donne son nom.
7. Le moteur annonce chaque texture chargée dans son journal, `logs/app.log`, avec ses dimensions. Copiez cette ligne dans `journal.txt`.
8. Cette ligne n'apparaît qu'au premier chargement : le moteur garde ensuite une copie de la texture. Pour la revoir, lancez avec `NK_TEX_CACHE=0`.
9. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Ma texture :`, `Ce que le mur a gagne :`, puis `Ce qui m'a bloque :`. Si le mur n'a pas changé, dites quel chemin était en cause.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo4-le_premier_mur_texture/` et mettez-y exactement ces fichiers, avec ces noms :

- `mur.cpp`
- `avant.png`
- `apres.png`
- `journal.txt`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
