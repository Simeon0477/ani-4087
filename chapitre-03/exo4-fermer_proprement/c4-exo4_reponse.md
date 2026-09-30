# Exercice - Fermer proprement

## Enoncé 
Ajoutez un rappel sur `NkWindowCloseEvent` qui met un booléen à faux, et faites porter la boucle sur ce booléen plutôt que sur `IsOpen()`.

Ajoutez ensuite un rappel sur `NkKeyPressEvent` qui fait la même chose sur la touche Échap.

Rendez le code et expliquez pourquoi les deux chemins de sortie doivent aboutir au même endroit.

## Résultats

### Code

```c++
#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

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

    while(running) {
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr) {
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }

            if(event->Is<nkentseu::NkKeyPressEvent>()){
                running = false;
            }
        }
    }

    return 0;
}
```

### Explication

Pour cette exercice nous avons utilisé 2 évènements, `NkWindowCloseEvent` et `NkKeyPressEvent` qui correspondent respectivement à cliquer sur le bouton de fermeture de la fenêtre et à presser la touche échap. L'on pourrait penser qu'à son nom `NkWindowCloseEvent` permette de fermer une fenêtre pourtant, il est juste le lecteur du signal émis lorsqu'on appuie sur la bouton de fermeture, si à la place de `running = false;` je mets `true`, la fenêtre ne se ferme plus, et c'est pareil pour `NkKeyPressEvent`. Donc les deux chemins de sortie aboutissent au même endroit parce qu'on leur a attribué la même opération par rapport à leur évènement.

