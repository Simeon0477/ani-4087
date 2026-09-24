# Exercice - Deux Systèmes un Fichier

## Énoncé

Écrivez les filtres pour Windows et pour Linux dans votre projet, chacun avec ses bibliothèques. Faites vérifier par un camarade sur l'autre système que le projet se construit chez lui sans modification. Si vous n'avez accès qu'à un système, écrivez quand même les deux et dites ce que vous n'avez pas pu vérifier.

## Solution

### *fichier .jenga*

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
    
    with filter("system:Windows"):
        links(["user32", "gdi32", "opengl32"])

    with filter("system:Linux"):
        links(["pthread", "X11", "GL"])
```

### *main.cpp*

```c++
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif

int main() {
#ifdef _WIN32
    std::cout << "Compile sur Windows" << std::endl;
#elif defined(__linux__)
    std::cout << "Compile sur Linux" << std::endl;
#endif
    return 0;
}
```

### *Sortie de jenga run sous windows*

```cmd
PS C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle> jenga run

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  MaSalle.exe
     C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\Build\Bin\Debug-Windows\MaSalle\MaSalle.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Compile sur Windows

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.05s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### *Sortie de jenga run sous Linux (Testé sur la machine de Dimitry)*

```cmd
sonwa@SONWA:/mnt/f/MaSalle$ jenga build

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.6.3             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Linux x86_64
Toolchain:     host-gcc

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle                                                         Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build/Bin/Debug-Linux/MaSalle/MaSalle

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.04s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.04s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

sonwa@SONWA:/mnt/f/MaSalle$ jenga run

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.6.3             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Cannot create builder: No suitable toolchain found for Windows x86_64
```

## Conclusion

Nous avons pu tester notre  programme sous Windows et constaté qu'il fonctionne sans encombre, cependant, lors du test sous Linux, le build a été un succès mais l'exécution a échoué a cause d'une absence de Toolchain pour Windows.
La question à se poser est donc pourquoi malgré le filtre notre programme demande toujours une chaine d'outils Windows?
 
