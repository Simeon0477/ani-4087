#include <iostream>
#include <string>

int main() {
    int nbImages = 1;
    int nbTrames = 0;
    std::cin >> nbImages >> nbTrames;

    bool emprunte = false;      
    int reussies = 0;
    int refusees = 0;
    int liberations = 0;
    int premiereFuite = 0;      

    for (int t = 1; t <= nbTrames; ++t) {
        std::string chemin;
        std::cin >> chemin;

        // Chaque trame commence par un emprunt.
        if (emprunte) {
            ++refusees;
            std::cout << t << " BLOQUEE\n";
            continue;
        }
        emprunte = true;
        ++reussies;

        if (chemin == "sortie") {
            // On sort sans rendre l'image : c'est la fuite.
            std::cout << t << " FUITE\n";
            if (premiereFuite == 0) {
                premiereFuite = t;
            }
        } else if (chemin == "double") {
            // Un second emprunt est tente : il est refuse, puis on rend l'image.
            ++refusees;
            emprunte = false;
            ++liberations;
            std::cout << t << " DOUBLE\n";
        } else {
            // normal : on dessine puis on rend l'image.
            emprunte = false;
            ++liberations;
            std::cout << t << " OK\n";
        }
    }

    std::cout << "REUSSIES " << reussies << "\n";
    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "LIBERATIONS " << liberations << "\n";
    std::cout << "ECART " << reussies - liberations << "\n";
    if (premiereFuite == 0) {
        std::cout << "PREMIERE FUITE AUCUNE\n";
    } else {
        std::cout << "PREMIERE FUITE " << premiereFuite << "\n";
    }
    (void)nbImages;
    return 0;
}