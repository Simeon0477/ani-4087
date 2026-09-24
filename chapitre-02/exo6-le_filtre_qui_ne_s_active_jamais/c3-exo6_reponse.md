# Exercice — Le Filtre qui ne s'Active Jamais

## Énoncé
Écrivez un filtre dont la condition est fausse sur votre machine, avec une définition à l'intérieur, et prouvez qu'elle n'est pas appliquée. Puis rendez la condition vraie et prouvez qu'elle l'est.

Ne comptez pas sur jenga info, et c'est le premier enseignement de l'exercice. Sa sortie est rigoureusement identique, au caractère près, que la condition soit vraie ou fausse : il n'affiche aucune définition. Vérifié dans l'image de correction, Jenga 2.8.0. jenga build --verbose n'en montre pas davantage.

Quand l'outil refuse de répondre, on fait répondre le programme. Arrangez-vous pour que votre main.cpp affiche lui-même s'il a reçu la définition ou non, puis lancez-le dans les deux cas.

Rendez : votre fichier de projet, votre main.cpp, et les deux sorties du programme.

## Résultats

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
    
    with filter("system:Linux"):
        defines(["MODE_SPECIAL"])

    #with filter("system:Windows"):
    #    defines(["MODE_SPECIAL"])
```

### *main.cpp*

```c++
#include <iostream>

int main() {
#ifdef MODE_SPECIAL
    std::cout << "MODE_SPECIAL actif" << std::endl;
#else
    std::cout << "MODE_SPECIAL absent" << std::endl;
#endif
    return 0;
}
```

### *Sortie de jenga run avec filtre Linux*

```cmd
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

MODE_SPECIAL absent

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.06s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### *Sortie de jenga run avec filtre Windows*

```cmd
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

MODE_SPECIAL actif

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.05s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Conclusion

Au vu des tests, nous pouvons donc conclure que les filtres donnent des directives pour des systèmes précis. Dans notre cas, une défintion faite sous un filtre Linux n'affecte jamais un programme exécuté sous Windows. 

Nous pensons que c'est l'une des bases fondamentales du build multi-plateformes de Jenga, permettre qu'un programme s'exécute différement selon la plateforme.

