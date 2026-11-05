#include <iostream>
#include <string>
#include <vector>

int main() {
    long long largeurFenetre = 0;
    long long hauteurFenetre = 0;
    int nbTampons = 0;
    int nbOrdres = 0;
    std::cin >> largeurFenetre >> hauteurFenetre >> nbTampons >> nbOrdres;

    bool offscreenAllume = false;
    std::vector<long long> largeurCible;   
    std::vector<long long> hauteurCible;
    long long cibleActive = 0;             
    long long zoneLargeur = largeurFenetre;
    long long zoneHauteur = hauteurFenetre;
    std::vector<bool> tamponPris(nbTampons > 0 ? nbTampons : 1, false);
    int numeroImage = 0;
    int imagesDessinees = 0;
    bool fige = false;

    for (int i = 0; i < nbOrdres && !fige; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "allume") {
            std::string nom;
            std::cin >> nom;
            if (nom == "OFFSCREEN") {
                offscreenAllume = true;
            }
        } else if (ordre == "cible") {
            long long w = 0;
            long long h = 0;
            std::cin >> w >> h;
            if (!offscreenAllume) {
                std::cout << "CIBLE NULLE\n";
            } else {
                largeurCible.push_back(w);
                hauteurCible.push_back(h);
                std::cout << "CIBLE " << largeurCible.size() << " " << w << " " << h << "\n";
            }
        } else if (ordre == "vers") {
            long long k = 0;
            std::cin >> k;
            if (k == 0 || (k >= 1 && k <= static_cast<long long>(largeurCible.size()))) {
                cibleActive = k;
            } else {
                std::cout << "VERS REFUSE\n";
            }
        } else if (ordre == "taille") {
            std::cin >> zoneLargeur >> zoneHauteur;
        } else if (ordre == "image") {
            ++numeroImage;
            const int tampon = (numeroImage - 1) % nbTampons;
            if (tamponPris[tampon]) {
                std::cout << "BLOQUE " << numeroImage << "\n";
                fige = true;
            } else {
                ++imagesDessinees;
                if (cibleActive == 0) {
                    std::cout << "IMAGE " << numeroImage << " FENETRE\n";
                } else {
                    std::cout << "IMAGE " << numeroImage << " CIBLE " << cibleActive << "\n";
                    const long long cw = largeurCible[cibleActive - 1];
                    const long long ch = hauteurCible[cibleActive - 1];
                    if (zoneLargeur > cw || zoneHauteur > ch) {
                        tamponPris[tampon] = true;
                    }
                }
            }
        }
    }

    std::cout << "IMAGES " << imagesDessinees << "\n";
    std::cout << "ETAT " << (fige ? "BLOQUE" : "LIBRE") << "\n";
    return 0;
}