#include <iostream>
#include <string>

int main() {
    std::string facon;       // TOUJOURS ou SAUTE : comment la boucle soumet la fin de trame
    int nbImages = 0;
    std::cin >> facon >> nbImages;

    std::string signes;
    if (nbImages > 0) {
        std::cin >> signes;
    }

    bool ouverte = false;    // le drapeau « trame ouverte » de la session
    int rendues = 0;
    int perdues = 0;
    int erreurs = 0;
    int premierRefus = 0;    // 0 = aucun

    for (int t = 1; t <= nbImages; ++t) {
        const char signe = (static_cast<std::size_t>(t - 1) < signes.size()) ? signes[static_cast<std::size_t>(t - 1)] : '0';

        bool rendre = false;                 // l'etat neuf : on ne rend pas
        const char *w = "OK";
        if (ouverte) {
            w = "REFUSE";                    // WaitFrame refuse, l'etat reste neuf
            ++erreurs;
            if (premierRefus == 0) {
                premierRefus = t;
            }
        } else {
            rendre = (signe == '1');
        }

        const char *b = "OK";
        if (ouverte) {
            b = "REFUSE";
            ++erreurs;
        } else {
            ouverte = true;                  // BeginFrame accepte : la trame s'ouvre
        }

        std::string e = "-";
        if (facon == "TOUJOURS" || rendre) {
            if (ouverte) {
                e = "OK";                    // EndFrame accepte : la trame se ferme
                ouverte = false;
            } else {
                e = "REFUSE";
                ++erreurs;
            }
        }

        if (rendre) {
            ++rendues;
        } else if (signe == '1') {
            ++perdues;                       // le runtime voulait un rendu, la boucle n'a pas pu
        }

        std::cout << t << " " << w << " " << b << " " << (rendre ? "OUI" : "NON") << " " << e << "\n";
    }

    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "PERDUES " << perdues << "\n";
    std::cout << "ERREURS " << erreurs << "\n";
    if (premierRefus == 0) {
        std::cout << "PREMIER REFUS AUCUN\n";
    } else {
        std::cout << "PREMIER REFUS " << premierRefus << "\n";
    }
    return 0;
}
