# Exercice - L'Inventaire de la Chaine

## Énoncé

Lancez `jenga info -v` et rendez le tableau `Available Toolchains` en entier.

Dites ce qui est présent sur votre machine et ce qui manque.

## Solution

### *Sortie de jenga info -v*

```cmd
PS C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle> jenga info -v

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

[Loader] Loading workspace from C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle.jenga
[Loader] Workspace 'MaSalle' post-processed.
=========================== Jenga Workspace: MaSalle ===========================

Location: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle
Entry file: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\MaSalle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Android, Linux
Target Architectures: x86_64, arm64


Projects
------------------------------------------------------------
Name      Kind         Language   Test   External
=================================================
MaSalle   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running


System
------------------------------------------------------------
Host OS: Windows
Host Architecture: x86_64
Host Environment: msvc
Host Triple: x86_64-pc-windows-msvc
Python: 3.12.2 (tags/v3.12.2:6abddd9, Feb  6 2024, 21:26:36) [MSC v.1937 64 bit (AMD64)]
Jenga version: 2.8.2
```

### *Récapitulatif*

**Toolchains présentes :**
 - host-clang
 - host-g++
 - clang-mingw
 - mingw
 - clang-cross-linux

**Toolchains absentes :**
 - msvc
 - emsdk
 - zig (all)


