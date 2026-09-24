# Exercice - Les Vingt Deux Triées

## Énoncé

Prenez la liste des vingt-trois dépendances de la démonstration du moteur et classez-la en trois groupes : celles dont le nom suffit à deviner le rôle, celles dont vous avez une idée sans certitude, celles dont vous ne savez rien.

Pour ce troisième groupe, ouvrez l'en-tête principal de chaque module et rendez une phrase par module.

## Solution

Voici la liste des dépendances de **NKXRDemo** :
```python
    nkentseudependson(
        ["NKXR", "NKRenderer", "NKRHI", "NKSL", "NKGLSlang", "NKSPIRVCross",
         "NKSerialization", "NKReflection", "NKFileSystem", "NKFont", "NKImage", "NKGlad",
         "NKEvent", "NKWindow", "NKMath", "NKTime", "NKLogger", "NKStream",
         "NKContainers", "NKMemory", "NKCore", "NKPlatform", "NKThreading"],
        extra_includes=["src",
                        # NkVulkanDevice.h (liaison OpenXR) tire vulkan.h.
                        "%{wks.location}/Externals/Libs/Vulkan-Headers-1.4.350/include"],
    )
```

## Classification 

### *1 - Facile à deviner :*

 - **NKXR** : réalité virtuelle / XR
 - **NKRenderer** : Rendu graphique
 - **NKSerialization** : Sérialisation des données
 - **NKRéflexion** : Réflexion
 - **NKFileSystem** : système de fichiers
 - **NKFont** : Gestion des mises en forme du texte
 - **NKImage** : Gestion des images
 - **NKEvent** : Gestion des évènements
 - **NKWindows** : Gestion des fenêtres
 - **NKMaths** : Fonctions mathématiques
 - **NKTime** : Gestion du temps
 - **NKLogger** : Gestion des logs
 - **NKStream** : Gestion des flux
 - **NKContainers** : Conteneur de données
 - **NKMemory** : Gestion de la memoire
 - **NKCore** : Fonctions de bases
 - **NKPlatform** : Gestion de la plateforme
 - **NKThreading** : Gestion des threads

### *2 - Dont on a une idée mais sans certitude :*

 - **NKRHI** : Abstraction vas niveau graphique
 - **NKSL** : Compilateur de shaders maison

### *3 - Dont on n'en sait rien' :*

 - **NKGLSlang** : Repacking de Glslang (Khronos),GLSL -> SPIR-V
 - **NKGlad** : Repacking de glad, chargeur de fonctions OpenGL/GLES/EGL
 - **NKSPIRVCross** : Repacking de SPIRV-Cross (Khronos), SPIR-V -> GLSL/HLSL/MSL


