# Exercice - Le Define qui Manque

## Énoncé

Écrivez un petit en-tête à vous qui déclare une classe complète si un define est posé, et une coquille vide sinon. Compilez un programme qui l'emploie, avec puis sans le define. Rendez les deux messages et dites lequel des deux vous auriez su diagnostiquer sans cet exercice.

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
    defines(["VERSION_COMPLETE"])
```

### *build avec define*

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

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle                                                         Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MaSalle\MaSalle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.51s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1.51s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

### *build sans define*

```cmd
Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MaSalle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MaSalle                                                         Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle\src\main.cpp:4 ║
║ :16: error: no matching constructor for initialization of 'HelloWorld'                       ║
║     4 |     HelloWorld h("Hello, monde complet !");                                          ║
║       |                ^ ~~~~~~~~~~~~~~~~~~~~~~~~                                            ║
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle\src/../include ║
║ /Helloworld.hpp:7:7: note: candidate constructor (the implicit copy constructor) not viable: ║
║ no known conversion from 'const char[23]' to 'const HelloWorld' for 1st argument             ║
║     7 | class HelloWorld {                                                                   ║
║       |       ^~~~~~~~~~                                                                     ║
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle\src/../include ║
║ /Helloworld.hpp:7:7: note: candidate constructor (the implicit move constructor) not viable: ║
║ no known conversion from 'const char[23]' to 'HelloWorld' for 1st argument                   ║
║     7 | class HelloWorld {                                                                   ║
║       |       ^~~~~~~~~~                                                                     ║
║ C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle\src/../include ║
║ /Helloworld.hpp:12:5: note: candidate constructor not viable: requires 0 arguments, but 1    ║
║ was provided                                                                                 ║
║    12 |     HelloWorld() : m_message("Hello") {}                                             ║
║       |     ^                                                                                ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle\src\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.58s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.58s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MaSalle
```

## Conclusion
Lors du build avec define nous n'avons aucune erreur et le build se fait sans encombre.
Sans l'ajout du define au sein du fichier *.jenga*, nous obtenons une erreur de compilation lors du build.

