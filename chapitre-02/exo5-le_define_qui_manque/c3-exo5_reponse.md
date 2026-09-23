# Exercice — Lae Define qui manque

## Énoncé
Écrivez un petit en-tête à vous qui déclare une classe complète si un define est posé, et une coquille vide sinon. Compilez un programme qui l'emploie, avec puis sans le define.

Rendez les deux messages et dites lequel des deux vous auriez su diagnostiquer sans cet exercice.

## Résultats

### Message d'erreur

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
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (3 projects):
  1. Livre [CONSOLE_APP] → 
  2. Biblio [CONSOLE_APP] (depends: Livre) → 
  3. MaSalle [CONSOLE_APP] (depends: Biblio)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Livre                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Livre\Livre.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.72s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Biblio                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Biblio\Biblio.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.84s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle                                                         Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from                                                                        ║
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\Chapitre_2\MaSalle\src\main.cp ║
║ p:2:0:                                                                                       ║
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\Chapitre_2\MaSalle\Biblio\incl ║
║ ude/biblio.hpp:4:21: fatal error: Livre.hpp: No such file or directory                       ║
║  #include "Livre.hpp"                                                                        ║
║                      ^                                                                       ║
║ compilation terminated.                                                                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\Chapitre_2\MaSalle\src\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.22s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  2/3
Failed:         1
Errors:         1
Time:           1.78s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MaSalle
```

### MaSalle.jenga

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
    includedirs(["Biblio/include", "Biblio/src"])
    dependson(["Biblio"])
```

Le module *Livre* et *Biblio* se build sans soucis mais lors du build de *MaSalle* qui dépend de *Biblio* mais pas de *Livre* nous avons une erreur de compilation.
