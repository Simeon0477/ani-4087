# Exercice - Le Fichier de Porjet Lu en Entier
## Énoncé
 
Ouvrez le fichier de projet de la démonstration XR du moteur et lisez-le en entier, y compris les commentaires.
 
Rendez une page : ce qu'il construit, ce dont il dépend, ce qui change d'un système à l'autre, et les trois pièges qu'il documente. Pour chacun des trois, dites ce qui se passerait sans la ligne concernée.
 
## Solution
 
### 1 - Ce qu'il construit
 
Le projet s'appelle **NKXRDemo**, déclaré en *windowedapp()* (application graphique avec fenêtre, pas une console). C'est l'« Étage 0 » d'une mission XR plus large : une démo qui rend une scène NKRenderer en **stéréo simulée** (souris = mouvement de tête, ZQSD/WASD pour se déplacer, rendu côte à côte simulant les deux yeux) — sans casque réel, via un backend simulateur desktop. L'architecture décrite en commentaire d'en-tête : un renderer 2D qui compose la frame finale à partir de deux renderers 3D offscreen, un par œil.
 
### 2 - Ce dont il dépend
 
Le projet ne dépend pas de un ou deux modules mais de **23 modules internes** via *nkentseudependson*, en chaîne complète depuis le bas niveau (*NKCore*, *NKMemory*, *NKPlatform*) jusqu'au rendu (*NKRenderer*, *NKRHI*, *NKSL*) en passant par le shader-compiling (*NKGLSlang*, *NKSPIRVCross*), la sérialisation, le système de fichiers, les fonts, etc. Il tire en plus un chemin d'include externe vers les headers Vulkan (*Vulkan-Headers-1.4.350*), nécessaire car *NkVulkanDevice.h* sert de couche de liaison avec OpenXR.
 
### 3 - Ce qui change d'un système à l'autre
 
Trois blocs *with filter("system:...")*, chacun avec des choix distincts :
 
| Système | Toolchain | Defines spécifiques | Links/Frameworks |
|---|---|---|---|
| Windows (hors UWP/Xbox) | *TC_WINDOWS* | *WIN32_LEAN_AND_MEAN*, *_UNICODE*, *UNICODE* | *user32*, *gdi32*, *opengl32*, *d3d11/d3d12/dxgi*, *advapi32*, etc. |
| Linux (XLib par défaut) | *clang-native* | *NKENTSEU_FORCE_WINDOWING_XLIB_ONLY* | *pthread*, *X11*, *Xext*, *GL* |
| macOS | *clang-native* | *(aucun define spécifique)* | Frameworks Cocoa, QuartzCore, OpenGL |
 
Il y a aussi une distinction orthogonale par configuration (*config:Debug* vs *config:Release*) : symboles de debug activés/désactivés et niveau d'optimisation, classique et indépendante du système d'exploitation.
 
### 4 - Les trois pièges documentés
 
**Piège 1 — *NKGLSlang*/*NKSPIRVCross* explicites dans *nkentseudependson***
 
« le linker d'un exécutable qui tire NKSL/NKRHI ne les récupère pas transitivement (piège documenté dans NkLocomotionDemo.jenga, 2026-07-23) »
 
Normalement, si *NKRHI* dépend déjà de *NKGLSlang*/*NKSPIRVCross*, on s'attendrait à ce que l'exécutable final les récupère automatiquement par transitivité. Ce n'est pas le cas ici — c'est une limite connue de leur système de build. Si on supprime ces deux entrées de la liste, le projet continue de compiler normalement (aucune erreur de syntaxe ou de type), mais **l'édition de liens échoue** avec des symboles indéfinis (*undefined reference*) venant du code de *NKSL*/*NKRHI* qui appelle des fonctions de ces deux libs jamais liées à l'exécutable final. C'est donc un piège qui se manifeste tardivement, à la toute dernière étape de la chaîne.
 
**Piège 2 — *defines(["NK_RHI_VK_ENABLED"])***
 
    « NK_RHI_VK_ENABLED est un define LOCAL de NKRHI (non propagé) : sans lui, NkVulkanDevice.h montre sa classe STUB et la liaison OpenXR ne compile pas. »
 
Ce define contrôle si *NkVulkanDevice.h* expose la vraie implémentation Vulkan ou une classe stub (coquille vide, sans les membres réels). Si on supprime cette ligne, le header bascule silencieusement sur la version STUB — aucun message d'erreur au moment de l'include lui-même. L'échec apparaît seulement plus loin, quand le code de liaison OpenXR essaie d'appeler des méthodes qui n'existent que sur la vraie classe : c'est donc une **erreur de compilation**, mais retardée et dont la cause racine (un define manquant, pas un bug dans le code appelant) n'est pas évidente à première lecture du message.
 
**Piège 3 — *advapi32* dans les *links* Windows**
 
    « advapi32 : RegGetValueA de la decouverte du runtime OpenXR actif (NkXrOpenXRBackend, etape 2a) »
 
Cette bibliothèque système Windows n'a rien d'évident à voir avec du rendu graphique — elle sert uniquement à appeler *RegGetValueA*, utilisée pour lire le registre Windows et détecter quel runtime OpenXR est actuellement actif sur la machine. Si on la retire, la compilation du *.cpp* correspondant passe sans problème (c'est juste un appel de fonction déclarée dans *<winreg.h>*), mais l'**édition de liens échoue** spécifiquement sous Windows avec un symbole *RegGetValueA* introuvable — un piège d'autant plus insidieux qu'il ne se manifesterait jamais sur Linux/macOS, donnant l'illusion trompeuse que le projet est correctement configuré.
 
### Résumé des trois pièges par étape de la chaîne
 
| Piège | Étape où ça casse |
|---|---|
| Dépendances shader non propagées | Édition de liens |
| *NK_RHI_VK_ENABLED* absent | Compilation (retardée, sur du code utilisant le stub) |
| *advapi32* absent | Édition de liens (Windows uniquement) |
