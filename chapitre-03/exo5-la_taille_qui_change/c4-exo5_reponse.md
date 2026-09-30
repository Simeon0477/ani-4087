# Exercice - La taille qui change

## Enoncé 
Écoutez `NkWindowResizeEvent` et affichez la nouvelle taille dans la console à chaque changement.

Redimensionnez lentement, puis d'un coup. Rendez les deux séries de nombres, et dites ce que vous en concluez sur le nombre d'événements reçus.

## Résultats

### Code de main.cpp

```c++
#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include <iostream>

NKENTSEU_DEFINE_APP_DATA(([](){
    nkentseu::NkAppData d{};
    d.appName = "La Fenetre Nue";
    d.appVersion = "0.1.0";
    return d;
})())

int nkmain(const nkentseu::NkEntryState &state)
{
    nkentseu::NkWindowConfig config;
    config.title = "La Fenetre Nue";
    config.width = 1000;
    config.height = 720;

    nkentseu::NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    bool running = true;
    auto& stackEvent = nkentseu::NkEvents();

    int count = 0;
    while(running) {
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr) {
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }

            if(event->Is<nkentseu::NkKeyPressEvent>()){
                running = false;
            }

            if(event->Is<nkentseu::NkWindowResizeEvent>()){
                int width = fenetre.GetSize().width;
                int height = fenetre.GetSize().height;

                count++;
                std::cout<< " - Largeur de la fenetre : " << width << "\n - Hauteur de la fenetre : " << height <<std::endl;
            }
        }
    }

    std::cout<< "\n\nNombre d'evenements : " << count <<std::endl;

    return 0;
}
```

### Extrait de la sortie du redimensionnement lent : 

```cmd
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1024
 - Hauteur de la fenetre : 734
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747
 - Largeur de la fenetre : 1036
 - Hauteur de la fenetre : 747


Nombre d'evenements : 123
```

Lors d'un redimensionnement lent, pour 123 évènements recensés, nous constatons une très faible variation des dimensions de l'écran.

Comme le montre les dimensions affichées par le programme, il faut de nombreuses itération pour un changement d'un pixel.

### Extrait de la sortie du redimensionnement rapide

```cmd
 - Largeur de la fenetre : 998
 - Hauteur de la fenetre : 712
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981
 - Largeur de la fenetre : 1388
 - Hauteur de la fenetre : 981


Nombre d'evenements : 35
```

Cette fois ci l'on décompte beaucoup moins d'évènements lus, cependant, cette fois ci, le changement de dimensions s'est fait brutalement au premier évènement et pour toutes les autres fois ce sont les mêmes dimensions qui  ont été affichées.