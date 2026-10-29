# Exercice - L'image qui n'existe pas

## Enoncé 
### Ce que vous allez faire
Charger une image qui n'existe pas, deux fois : avec `NkImage`, puis comme texture d'un mur de votre salle. Regarder ce que le programme fait ensuite.

### Comment faire
1. Dans `inexistant.cpp`, la partie `NkImage` tient en cinq lignes au plus : un `NkImage`, l'appel `Load("murs/nexistepas.png")`, puis un affichage. `NkImage` est dans `NKImage/Core/NkImage.h`.
2. L'affichage tient sur une ligne, sous la forme `charge : C, valide : V, largeur : L, hauteur : H`. C est le retour de `Load`, V celui de `IsValid()`, L et H ceux de `Width()` et `Height()`.
3. Chargez ensuite le même chemin comme texture, et posez-la sur un mur de votre salle. Une texture se pose en trois appels. `renderer->GetTextures()->Load(chemin)` la charge. `NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC)` crée un matériau, et `SetAlbedoMap` lui donne la texture. Le pavé la reçoit par `dc.material = mat->GetInstHandle()`. `NkMaterial` est dans `NKRenderer/Materials/NkMaterial.h`.
4. Lancez la salle depuis le dossier du projet. Prenez une capture du mur, nommée `mur-absent.png`. Votre salle se capture seule : `MASALLE_SHOT=120` prend l'image 120, et `MASALLE_SHOT_PATH` lui donne son nom.
5. Le moteur tient un journal dans `logs/app.log`, sous le dossier d'où vous lancez le programme. Copiez dans `journal.txt` la ligne de votre programme, puis la ligne du journal qui nomme votre fichier.
6. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Ce que rend Load :`, `Pourquoi rien ne plante :`, puis `Ce que montre le mur :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo2-l_image_qui_n_existe_pas/` et mettez-y exactement ces fichiers, avec ces noms :

- `inexistant.cpp`
- `journal.txt`
- `mur-absent.png`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
