#include <iostream>
#include <string>

int main() {
    int nbOrdres = 0;
    std::cin >> nbOrdres;

    unsigned long long courante = 0;           // poignee de la cible courante
    unsigned long long prochainePoignee = 101; // la premiere cible recoit 101
    unsigned long long index0 = 0;             // ce que la chaine a range a l'index 0
    int numeroImage = 0;
    int affichees = 0;
    int noires = 0;
    int perimees = 0;

    for (int i = 0; i < nbOrdres; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cible") {
            unsigned long long w = 0;
            unsigned long long h = 0;
            std::cin >> w >> h;
            courante = prochainePoignee;
            ++prochainePoignee;
            std::cout << "CIBLE " << courante << " " << w << " " << h << "\n";
        } else if (ordre == "chaine") {
            index0 = 0;
        } else if (ordre == "enregistre") {
            index0 = courante;
        } else if (ordre == "image") {
            ++numeroImage;
            if (index0 == 0) {
                std::cout << "IMAGE " << numeroImage << " NOIR\n";
                ++noires;
            } else if (index0 == courante) {
                std::cout << "IMAGE " << numeroImage << " AFFICHE " << index0 << "\n";
                ++affichees;
            } else {
                std::cout << "IMAGE " << numeroImage << " PERIMEE " << index0 << "\n";
                ++perimees;
            }
        }
    }

    std::cout << "AFFICHEES " << affichees << "\n";
    std::cout << "NOIRES " << noires << "\n";
    std::cout << "PERIMEES " << perimees << "\n";
    return 0;
}