#include <iostream>
#include <set>
#include <string>

namespace {

// Avant et droite de la tete, au sol, selon son lacet k (en quarts de tour) : (x, z).
const int kAvant[4][2] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } };
const int kDroite[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } };

} // namespace

int main() {
    long long pas = 0;
    int nbImages = 0;
    std::cin >> pas >> nbImages;

    // Le decalage du JOUEUR : on deplace le monde par rapport a la tete.
    // La pose de la tete, qui vient du casque, n'est jamais ecrite ici.
    long long decalageX = 0;
    long long decalageZ = 0;
    int diagonales = 0;

    for (int t = 1; t <= nbImages; ++t) {
        int k = 0;
        int n = 0;
        std::cin >> k >> n;
        std::set<std::string> tenues;
        for (int i = 0; i < n; ++i) {
            std::string fleche;
            std::cin >> fleche;
            tenues.insert(fleche);
        }

        const int x = (tenues.count("F_DROITE") ? 1 : 0) - (tenues.count("F_GAUCHE") ? 1 : 0);
        const int y = (tenues.count("F_HAUT") ? 1 : 0) - (tenues.count("F_BAS") ? 1 : 0);
        const int q = k % 4;

        decalageX += pas * (y * kAvant[q][0] + x * kDroite[q][0]);
        decalageZ += pas * (y * kAvant[q][1] + x * kDroite[q][1]);
        if (x != 0 && y != 0) {
            ++diagonales;
        }
        std::cout << t << " " << x << "," << y << " " << decalageX << " " << decalageZ << "\n";
    }

    std::cout << "DECALAGE " << decalageX << " " << decalageZ << "\n";
    std::cout << "DIAGONALES " << diagonales << "\n";
    return 0;
}
