# Exercice - Les quatre atténuations

## Enoncé 
### Ce que vous allez faire
Mesurer, avec le moteur lui-même, le gain des quatre modèles d'atténuation à cinq distances, et choisir celui d'une porte qui grince dans un couloir.

### Comment faire
1. Votre projet doit lier `NKAudio`, que le kit Renderer de la salle ne contient pas. Le kit `R3D` le contient, avec tout le reste. Dans votre `.jenga`, remplacez `Kits/Renderer/Renderer.jenga` par `Kits/R3D/R3D.jenga`, `userenderer()` par `user3d()`, et `Kits/Renderer/Resources` par `Kits/R3D/Resources`.
2. Écrivez `attenuations.cpp`. Ce programme n'a ni fenêtre ni sortie sonore : `cfg.backend = AudioBackendType::NULL_OUTPUT`. L'auditeur est à l'origine et regarde vers −Z : avant (0, 0, −1), haut (0, 1, 0).
3. Le son est un sinus doux : `AudioGenerator::GenerateTone(440.f, 2.f, WaveformType::SINE, 48000, 0.1f)`, joué en boucle avec `VoiceParams p; p.looping = true;`. Gardez cette amplitude faible : le moteur adoucit les fortes valeurs à la sortie.
4. Réglez `p.source3d` ainsi : `positional = true`, `minDistance = 1`, `maxDistance = 100`, `rolloffFactor = 1`. Placez la source devant l'auditeur, en (0, 0, −d), dans `p.source3d.position`.
5. Mesurez les quatre valeurs de `p.source3d.attenuationModel`, `AttenuationModel::NONE`, `INVERSE`, `LINEAR` et `EXPONENTIAL`, aux cinq distances 0,5, 1, 2, 4 et 8 mètres.
6. Pour chaque mesure, rendez 48 000 trames par blocs de 256 avec `RenderToBuffer`. Les échantillons y sont rangés gauche, droite, gauche, droite. Calculez la racine de la moyenne des carrés sur les deux oreilles ensemble.
7. Divisez chaque mesure par celle du modèle `NONE` à la même distance : c'est le gain. Gardez trois décimales.
8. Refaites les vingt mesures avec `rolloffFactor = 2`.
9. Écrivez les quarante lignes dans `mesures.txt`, sous la forme `INVERSE, rolloff 1, 2 m : g`, où g est le gain.
10. Tracez les quatre courbes du réglage `rolloff 1`, le gain en fonction de la distance, avec l'outil de votre choix. Enregistrez-les dans `courbe.png`.
11. Écoutez enfin `INVERSE` et `LINEAR` à 1 puis à 8 mètres, au casque, avec la sortie sonore normale.
12. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `La loi physique :`, `Ce que change rolloff :`, puis `Pour la porte du couloir :`.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo12-les_quatre_attenuations/` et mettez-y exactement ces fichiers, avec ces noms :

- `attenuations.cpp`
- `mesures.txt`
- `courbe.png`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
