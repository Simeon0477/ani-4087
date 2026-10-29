# Exercice - Un panneau au-dessus de la porte

## Enoncé 
### Ce que vous allez faire
Écrire le mot « Sortie » au-dessus de la porte de votre salle, avec une police embarquée dans le moteur, comme un objet de la salle.

### Comment faire
1. Dans `panneau.cpp`, construisez l'atlas : `NkFontAtlas atlas;`, puis `NkFontEmbedded::AddToAtlas(atlas, NkEmbeddedFontId::Inter, 32.f)`, puis `atlas.Build()`. Testez chaque retour.
2. Les en-têtes sont `NKFont/NkFont.h` et `NKFont/Embedded/NkFontEmbedded.h`. La police est dans le moteur : aucun fichier à fournir.
3. Lisez les pixels de l'atlas avec `GetTexDataAsAlpha8` : un octet par pixel, qui dit combien la lettre le couvre. `atlas.texWidth` et `atlas.texHeight` donnent sa taille.
4. Pour chaque lettre, `police->FindGlyph(c)` rend un `NkFontGlyph`. `x0`, `y0`, `x1` et `y1` placent la lettre en pixels, depuis le curseur posé sur la ligne de base.
5. `y0` est négatif pour ce qui monte au-dessus de la ligne. `u0`, `v0`, `u1` et `v1` disent où est la lettre dans l'atlas, entre 0 et 1. `advanceX` fait avancer le curseur.
6. Créez l'image avec `NkImage::Create(largeur, hauteur, 4, couleur)`, où `couleur` s'écrit `0xRRGGBBAA`. Sa largeur est la somme des `advanceX` des six lettres. Sa hauteur vaut `police->ascent - police->descent`, et la ligne de base est à `ascent` pixels du haut.
7. Dans l'image, une lettre occupe le rectangle qui va de `curseur + x0` à `curseur + x1` en largeur, et de `base + y0` à `base + y1` en hauteur.
8. Un pixel placé à la fraction `f` de la largeur de ce rectangle correspond à `u = u0 + f * (u1 - u0)` dans l'atlas, et de même en hauteur avec `v`. Le pixel de l'atlas est en `(u * texWidth, v * texHeight)`.
9. Lisez-y la couverture, divisez-la par 255, et mélangez dans cette proportion la couleur du texte à celle du fond.
10. Enregistrez l'image avec `SavePNG` dans `panneau.png`. Posez-la ensuite comme texture sur un pavé de 20 cm de haut, au-dessus de la porte. Une texture se pose en trois appels. `renderer->GetTextures()->Load(chemin)` la charge. `NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC)` crée un matériau, et `SetAlbedoMap` lui donne la texture. Le pavé la reçoit par `dc.material = mat->GetInstHandle()`. `NkMaterial` est dans `NKRenderer/Materials/NkMaterial.h`.
11. La porte est centrée en x = −0,70 m, haute de 2 m, contre le mur du fond en z = −2 m. Donnez au pavé la largeur qui garde les proportions de votre image.
12. Prenez une capture à trois mètres du panneau, nommée `trois-metres.png`, et une à cinquante centimètres, nommée `cinquante-cm.png`. Votre salle se capture seule : `MASALLE_SHOT=120` prend l'image 120, et `MASALLE_SHOT_PATH` lui donne son nom.
13. Pour trois mètres, placez la caméra en (−0,70 ; 1,70 ; 1,00), et pour cinquante centimètres en (−0,70 ; 2,20 ; −1,50). Dans les deux cas, elle regarde le panneau.
14. Dans `panneau.txt`, écrivez d'abord deux lignes, `atlas : L x H` et `image : L x H`, avec vos tailles en pixels. Puis écrivez trois paragraphes étiquetés, dans cet ordre : `Ma police et sa taille :`, `A trois metres :`, puis `A cinquante centimetres :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo7-un_panneau_au_dessus_de_la_porte/` et mettez-y exactement ces fichiers, avec ces noms :

- `panneau.cpp`
- `panneau.png`
- `trois-metres.png`
- `cinquante-cm.png`
- `panneau.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
