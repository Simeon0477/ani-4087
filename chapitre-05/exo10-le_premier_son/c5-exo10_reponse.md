# Exercice - Le premier son

## Enoncé 
### Ce que vous allez faire
Faire jouer un son au démarrage de votre salle, sans le placer dans l'espace, et compter ce que cela coûte en lignes et en temps.

### Comment faire
1. Votre projet doit lier `NKAudio`, que le kit Renderer de la salle ne contient pas. Le kit `R3D` le contient, avec tout le reste. Dans votre `.jenga`, remplacez `Kits/Renderer/Renderer.jenga` par `Kits/R3D/R3D.jenga`, `userenderer()` par `user3d()`, et `Kits/Renderer/Resources` par `Kits/R3D/Resources`.
2. Dans `premier-son.cpp`, initialisez le moteur de son : `AudioEngineConfig cfg; cfg.sampleRate = 48000;`, puis `AudioEngine::Instance().Initialize(cfg)`. Tout est dans `NKAudio/NkAudio.h`, espace `nkentseu::audio`.
3. Prenez un son : un fichier `.wav` à vous, chargé par `AudioLoader::Load`, ou un son fabriqué par `AudioGenerator::GenerateTone(440.f, 1.f)`. Jouez-le une fois au démarrage avec `Play`.
4. Juste après l'initialisation, affichez quatre lignes : `dorsal : `, `frequence : `, `tampon : ` et `latence : `. Elles sont suivies, dans cet ordre, de ce que rendent `GetBackendName`, `GetSampleRate`, `GetBufferSize` et `GetLatencyMs`. La latence est en millisecondes.
5. Fermez le moteur à la fin du programme, après la boucle : `Shutdown`, puis `AudioLoader::Free` sur l'échantillon.
6. Copiez les quatre lignes affichées dans `demarrage.txt`. Calculez à la main la durée d'un tampon de 256 trames à 48 000 hertz.
7. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Lignes de mon premier son :`, `Latence calculee et annoncee :`, puis `Pourquoi pas dans la boucle de rendu :`. Comptez les lignes de l'initialisation à la fermeture comprises.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo10-le_premier_son/` et mettez-y exactement ces fichiers, avec ces noms :

- `premier-son.cpp`
- `demarrage.txt`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
