# Exercice - Mesurer en Debug et en Release

## Énoncé

Écrivez une boucle qui fait un calcul lourd et le chronomètre. Construisez en Debug puis en Release et mesurez.

Rendez le rapport. Puis dites, sachant qu'une image de casque dure onze millisecondes, laquelle des deux mesures vous aurait fait prendre une mauvaise décision.

## Solution

### *Code C++*

```c++
#include <iostream>
#include <chrono>
#include <cmath>

int main() {
    const int nbImages = 20;
    const int nbCalculs = 500000;
    double total = 0.0;
    double resultat = 0.0;

    for (int image = 0; image < nbImages; ++image) {
        auto debut = std::chrono::steady_clock::now();

        for (int i = 0; i < nbCalculs; ++i) {
            double x = i * 0.00001;
            resultat += std::sin(x) * std::cos(x);
        }

        auto fin = std::chrono::steady_clock::now();
        double temps = std::chrono::duration<double, std::milli>(fin - debut).count();
        total += temps;
    }

    std::cout << "Temps moyen : " << (total / nbImages) << " ms" << std::endl;
    std::cout << "Resultat de l'operation (sin(x) * cos(x)): " << resultat << std::endl;
    return 0;
}
```
### *Sortie de jenga run --config Debug*

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

Temps moyen : 14.4333 ms
Resultat de l'operation (sin(x) * cos(x)): 919538

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.36s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### *Sortie de jenga run --config Release*

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
     C:\Users\NNS\Documents\AIA_4\Semestre_01\ANI-IA_4087\ani-4087\MaSalle\Build\Bin\Release-Windows\MaSalle\MaSalle.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Temps moyen : 14.0172 ms
Resultat de l'operation (sin(x) * cos(x)): 919538

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.36s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Résultats

Après d'autres exécutions nous avons constaté que le temps d'exécution n'est pas constant, donc la donnée que nous décidons de noter sera la moyenne de 5 mesures.

| Configurations | Tailles | Temps de build | Temps d'exécution moyen |
|---|---|---|---:|
| Debug | **73,9 Ko (75 704 octets)** | **0.97s** | **14,5669 ms**  |
| Release | **73,9 Ko (75 704 octets)** | **0.96s** | **15,5949 ms** |


## Conclusion

En temps normal, Release qui est la configuration utilisée pour les applications à déployer et est doit donc être optimisé et avoir des performances supérieures à celle de Debug. Cependant, dans notre cas il y'a aucune optimisation pour Release, c'est pour cela que les deux présente des performances similaires.

Pour notre cas, notre programme avec nos deux configurations surpasse la limite des *11 ms* par image, donc il serait désagréable pour un utilisateur. Etant donné que les images en respecteront pas le quota des *11 ms* le joueur souffrira de la latence du programme et risquerait des nausées ou tout autre malaise.