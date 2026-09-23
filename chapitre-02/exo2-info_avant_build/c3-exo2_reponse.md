# Exercice — Info avant Build

## Énoncé
Lancez jenga info sur votre projet et lisez sa sortie en entier. Rendez-la, et dites ce qu'elle vous apprend que le fichier de projet ne disait pas explicitement.

## Résultats

### *Sortie de jenga info*

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

========================= Jenga Workspace: Chapitre_2 ==========================

Location: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\Chapitre_2
Entry file: C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\Chapitre_2\Chapitre_2.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Android
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name      Kind         Language   Test   External
=================================================
MaSalle   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
mingw      gcc      Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running
```

### *Comparaison avec jenga build*

Le fichier projet nous renseigne sur :
 - Le type d'application (Consoleapp()) 
 - Le langage utilisé (C++)
 - Le dialecte de C++ employé (C++17)
 - La location par rapport au *Workspace*
 - Les fichiers à build

Tandis que *jenga info* nous donne : 
 - La configuration (Debug, Release)
 - La plate-forme de développement (windows)
 - Les SE cibles (Windows, Android)
 - L'architecture cible (x86_64, arm64 doit être ajouté pour Android)
 - L'environnement (mingw)
 - Les toolchains
 - Et l'état du projet (Exécuté ou non)

Il est donc indispensable de passer par un *jenga info* avant un *jenga build* car il renseigne sur les nécessités du projets.