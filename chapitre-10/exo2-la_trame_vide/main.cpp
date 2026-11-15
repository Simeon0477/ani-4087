#include <iostream>
#include <string>

int main() {
    int tailleChaine = 0;
    int nbImages = 0;
    std::cin >> tailleChaine >> nbImages;

    // La chaine accepte de 1 a 4 images : sinon, on n'affiche rien d'autre.
    if (tailleChaine < 1 || tailleChaine > 4) {
        std::cout << "CHAINE REFUSEE\n";
        return 0;
    }

    std::string signes;
    if (nbImages > 0) {
        std::cin >> signes;
    }

    int prochaine = 0;      // l'image a emprunter : l'anneau n'avance que sur une image rendue
    int fins = 0;
    int rendues = 0;
    int sautees = 0;

    for (int t = 1; t <= nbImages; ++t) {
        const char signe = (static_cast<std::size_t>(t - 1) < signes.size()) ? signes[static_cast<std::size_t>(t - 1)] : '0';
        if (signe == '1') {
            const int i = prochaine;
            const int lacet = t - 1;                     // un degre par image : suit le numero de l'image
            prochaine = (i + 1) % tailleChaine;
            ++rendues;
            std::cout << t << " OUI 1 " << lacet << " " << i << "\n";
        } else {
            ++sautees;                                   // rien d'emprunte, l'anneau ne bouge pas
            std::cout << t << " NON 0\n";
        }
        ++fins;                                          // la fin de trame part a chaque image
    }

    std::cout << "FINS " << fins << "\n";
    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "SAUTEES " << sautees << "\n";
    std::cout << "PROCHAINE " << prochaine << "\n";
    return 0;
}
