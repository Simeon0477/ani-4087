# Exercice - Le son qui a une place

## Enoncé 
### Ce que vous allez faire
Placer un son de pluie en boucle à la fenêtre de votre salle, l'écouter de trois endroits, puis mesurer ce que le moteur envoie à chaque oreille.

### Comment faire
1. Votre projet doit lier `NKAudio`, que le kit Renderer de la salle ne contient pas. Le kit `R3D` le contient, avec tout le reste. Dans votre `.jenga`, remplacez `Kits/Renderer/Renderer.jenga` par `Kits/R3D/R3D.jenga`, `userenderer()` par `user3d()`, et `Kits/Renderer/Resources` par `Kits/R3D/Resources`.
2. Dans `son-place.cpp`, fabriquez la pluie : `AudioGenerator::GenerateNoise(4.f, WaveformType::NOISE_PINK)`. Jouez-la en boucle : `VoiceParams p; p.looping = true;`, puis `Play(pluie, p)`.
3. Placez-la à la première fenêtre, en (−1,98 ; 1,40 ; −0,90), dans `p.source3d.position`, avec `p.source3d.positional = true`. Choisissez `minDistance` et `maxDistance`, et notez-les.
4. Mettez l'auditeur à la place de la caméra, une fois au démarrage : `SetListenerPosition`, puis `SetListenerOrientation` avec la direction du regard et le haut.
5. Lancez la salle trois fois, la caméra placée près de la fenêtre, puis au centre, puis dans le coin opposé. Écoutez au casque, et notez ce que vous entendez, avec la position de la caméra.
6. Recommencez une de ces positions sans `positional`, et notez ce qui change.
7. Écrivez ensuite `mesure.cpp`. Ce programme n'a ni fenêtre ni sortie sonore : `cfg.backend = AudioBackendType::NULL_OUTPUT`. L'auditeur est à l'origine et regarde vers −Z : avant (0, 0, −1), haut (0, 1, 0).
8. Placez la pluie à deux mètres : à gauche en (−2, 0, 0), devant en (0, 0, −2), puis à droite en (2, 0, 0). Faites chaque mesure avec `positional` vrai, puis faux.
9. Pour chaque mesure, rendez 48 000 trames par blocs de 256 avec `RenderToBuffer`. Les échantillons y sont rangés gauche, droite, gauche, droite. Calculez la racine de la moyenne des carrés, pour l'oreille gauche puis pour la droite.
10. Écrivez les six lignes dans `mesures.txt`, sous la forme `devant 1 : G x D y`. Le chiffre après la position vaut 1 avec `positional`, 0 sans. x et y sont vos deux mesures.
11. Dans `ecoute.txt`, écrivez cinq paragraphes étiquetés, dans cet ordre : `Position 1 :`, `Position 2 :`, `Position 3 :`, `Sans positional :`, puis `Ce que les mesures montrent :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo11-le_son_qui_a_une_place/` et mettez-y exactement ces fichiers, avec ces noms :

- `son-place.cpp`
- `mesure.cpp`
- `mesures.txt`
- `ecoute.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
