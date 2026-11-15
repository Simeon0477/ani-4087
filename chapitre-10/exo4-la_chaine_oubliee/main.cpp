#include <iostream>
#include <string>

int main() {
    int tailleChaine = 1;
    int nbAppels = 0;
    std::cin >> tailleChaine >> nbAppels;

    bool ouverte = false;                 // la trame est-elle ouverte ?
    int index[2] = { 0, 0 };              // l'index d'image de chaque chaine (0 = gauche, 1 = droite)
    bool empruntee[2] = { false, false };
    int journal = 0;                      // refus de wait, begin et end
    int avertissements = 0;               // un par oeil sans chaine
    int silencieux = 0;                   // refus de acquire et release : ils n'ecrivent rien

    for (int numero = 1; numero <= nbAppels; ++numero) {
        std::string appel;
        std::cin >> appel;
        std::cout << numero << " " << appel << " ";

        if (appel == "wait") {
            if (ouverte) {
                std::cout << "REFUSE\n";
                ++journal;
            } else {
                std::cout << "OK\n";
            }
        } else if (appel == "begin") {
            if (ouverte) {
                std::cout << "REFUSE\n";
                ++journal;
            } else {
                ouverte = true;
                std::cout << "OK\n";
            }
        } else if (appel == "acquire") {
            std::string oeil;
            std::cin >> oeil;
            const int c = (oeil == "G") ? 0 : 1;
            if (empruntee[c]) {
                std::cout << "REFUSE\n";
                ++silencieux;
            } else {
                empruntee[c] = true;
                std::cout << "OK " << index[c] << "\n";
            }
        } else if (appel == "release") {
            std::string oeil;
            std::cin >> oeil;
            const int c = (oeil == "G") ? 0 : 1;
            if (!empruntee[c]) {
                std::cout << "REFUSE\n";
                ++silencieux;
            } else {
                empruntee[c] = false;
                index[c] = (index[c] + 1) % tailleChaine;
                std::cout << "OK\n";
            }
        } else if (appel == "end") {
            std::string premier;
            std::cin >> premier;
            const bool projection = (premier != "-");
            int renseignee[2] = { 0, 0 };
            if (projection) {
                renseignee[0] = std::stoi(premier);
                std::cin >> renseignee[1];
            }

            if (!ouverte) {
                std::cout << "REFUSE AUCUNE\n";
                ++journal;
            } else {
                ouverte = false;          // la trame se ferme dans tous les cas
                int bloque = -1;
                if (projection) {
                    for (int c = 0; c < 2 && bloque < 0; ++c) {
                        if (renseignee[c] == 1 && empruntee[c]) {
                            bloque = c;
                        }
                    }
                }
                if (bloque >= 0) {
                    std::cout << "REFUSE ACQUISE " << (bloque == 0 ? "G" : "D") << "\n";
                    ++journal;
                } else {
                    std::cout << "OK";
                    if (projection) {
                        const bool manqueG = (renseignee[0] == 0);
                        const bool manqueD = (renseignee[1] == 0);
                        if (manqueG || manqueD) {
                            std::cout << " AVERT";
                            if (manqueG) {
                                std::cout << " G";
                                ++avertissements;
                            }
                            if (manqueD) {
                                std::cout << " D";
                                ++avertissements;
                            }
                        }
                    }
                    std::cout << "\n";
                }
            }
        }
    }

    std::cout << "JOURNAL " << journal << "\n";
    std::cout << "AVERTISSEMENTS " << avertissements << "\n";
    std::cout << "SILENCIEUX " << silencieux << "\n";
    return 0;
}
