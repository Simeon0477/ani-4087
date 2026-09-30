# Exercice - État contre événement

## Enoncé 
Écrivez deux compteurs. Le premier s'incrémente à chaque image où la touche Espace est tenue, lu par `NkInput.IsKeyDown`. Le second s'incrémente à chaque `NkKeyPressEvent` sur Espace.

Appuyez une seconde, relâchez. Rendez les deux nombres et expliquez l'écart.

## Résultats

### Code 

```c++
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

    int count_1 = 0;
    int count_2 = 0;
    while(running) {
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr) {
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }

            if(nkentseu::NkInput.IsKeyDown(nkentseu::NkKey::NK_SPACE)){
                count_1++;
            }

            if(event->Is<nkentseu::NkKeyPressEvent>()){
                count_2++;
            }

        }
    }

    std::cout<< "\n\nCompteur 1 : " << count_1 <<std::endl;
    std::cout<< "\nCompteur 2 : " << count_2 <<std::endl;

    return 0;
}
```

### Sortie de l'exécution 

 - **En maintenant la touche appuyée une fois**

```cmd
Compteur 1 : 34

Compteur 2 : 1
```

 - **En maintenant la touche appuyée deux fois**

```cmd
Compteur 1 : 88

Compteur 2 : 2
```

 - **En maintenant la touche appuyée trois fois**

```cmd
Compteur 1 : 108

Compteur 2 : 4
```

### Explication

L'écart entre les deux compteurs est énorme, en maintenant la touche plusieurs fois nous constatons que `NkKeyPressEvent` n'est valide qu'a l'appui de la touche tandis que `NkInput.IsKeyDown` est valide  tant que la touche est appuyée, tant que les touche est maintenue, un signal est émis et `NkInput.IsKeyDown` le lit constamment. En conclusion, en nous réferant au titre de l'exercice nous comprenons que `NkKeyPressEvent` se concentre sur l'évènement tandis que `NkInput.IsKeyDown` traite de l'état d'une touche du clavier.

Nous noous sommes décalé de la consigne en appuyant plus d'une fois la touche car nous avions besoin de plus d'information pour nos explications.
