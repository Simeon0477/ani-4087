# Exercice - Le chemin qui marche partout

## Enoncé 
### Ce que vous allez faire
Lancer votre salle texturée depuis deux dossiers différents, constater la panne, puis la corriger en passant par le système de fichiers du moteur.

### Comment faire
1. Reprenez votre salle avec un mur texturé, chargé par un chemin relatif comme `murs/beton.png`. Mettez votre nom de fichier.
2. Lancez le programme depuis le dossier du projet. Puis allez dans `Build/Bin/Debug-Windows/MaSalle/`, où se trouve l'exécutable, et lancez-le de là.
3. Notez ce que vous voyez dans les deux cas. Le journal du second lancement est dans `logs/app.log`, sous le dossier d'où vous l'avez lancé.
4. Corrigez : passez le chemin par `NkPath::LocateResource("murs/beton.png")`, de `NKFileSystem/NkPath.h`, et donnez son résultat à `Load`. Mettez ce code dans `chemin.cpp`.
5. Lisez dans `NkPath.h` le commentaire de `LocateResource` : il dit dans quel ordre la fonction cherche. Relancez depuis les deux dossiers.
6. Écrivez les quatre essais dans `essais.txt`, un par ligne, commençant par `avant, projet :`, `avant, Build :`, `apres, projet :`, puis `apres, Build :`. Après chacun, ce que vous avez vu. Pour un lancement qui échoue, recopiez aussi la ligne du journal qui nomme votre fichier.
7. Dans `reponse.txt`, écrivez trois paragraphes étiquetés, dans cet ordre : `Ce qui a change :`, `Ce que LocateResource essaie :`, puis `Deja vu avec fopen :`. Le premier dit ce qui change d'un dossier à l'autre. Dans le dernier, dites honnêtement si vous avez reconnu le piège tout seul.

### Ce que vous rendez
Dans votre dépôt GitHub, créez le dossier `chapitre-05/exo6-le_chemin_qui_marche_partout/` et mettez-y exactement ces fichiers, avec ces noms :

- `chemin.cpp`
- `essais.txt`
- `reponse.txt`

N'écrivez ni votre nom ni votre matricule dans ces fichiers.

## Résultats


## Conclusion
