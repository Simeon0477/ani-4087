# Exercice - L'Inventaire de la Chaine

## Énoncé

Lancez `jenga info -v` et rendez le tableau `Available Toolchains` en entier.

Dites ce qui est présent sur votre machine et ce qui manque.

## Solution

### *Sortie de jenga info -v*

```cmd
Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu
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


