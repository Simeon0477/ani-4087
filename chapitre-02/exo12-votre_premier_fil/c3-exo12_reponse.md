# Exercice - Le Premier Fil

## Énoncé

Préparez votre fichier de projet pour tout le livre : ajoutez, en commentaire, une ligne par chapitre à venir disant ce qu'il faudra y ajouter.

Vous décocherez ces lignes une à une. Rendez le fichier commenté.

## Solution

### *fichier projet*

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# MaSalle - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("MaSalle"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])

    # Sprint 3  : NKWindow et NKEvent
    #             gestion de la fenêtre et des événements.

    # Sprint 4  : NKRHI et NKRenderer
    #             backend de rendu et abstraction graphique.

    # Sprint 5  : Images, modèles, textes, sons
    #             chargement des assets (textures, meshes, fonts, audio).

    # Sprint 6  : La tête, l'orientation et les deux yeux
    #             gestion de la caméra/tête et du rendu stéréo.

    # Sprint 7  : La cadence et la prédiction
    #             boucle de frame, timing et prédiction de pose.

    # Sprint 8  : Les chaînes d'échange
    #             synchronisation / échange de données entre systèmes.

    # Sprint 9  : Les actions
    #             système d'input/actions (mapping des commandes).

    # Sprint 10 : La composition et les couches
    #             compositing des passes de rendu en couches.

    # Sprint 11 : Lire le vrai backend, et la même application sur deux backends
    #             abstraction multi-backend, portabilité du rendu.

    # Sprint 12 : Rendre deux fois
    #             rendu dupliqué par œil (stéréo réel).

    # Sprint 13 : La porte s'ouvre
    #             intégration / ouverture vers un nouveau module ou flux.

    # Sprint 14 : Des panneaux qu'on lit, et le son qui place les choses
    #             UI in-world lisible + spatialisation audio.

    # Sprint 15 : Quelqu'un d'autre entre
    #             gestion multi-utilisateur / networking basique.

    # Sprint 16 : Bâtir et livrer
    #             packaging et livraison du build final.

    # Sprint 17 : Approfondissement
    #             optimisation et consolidation générale.
```

## Conclusion

