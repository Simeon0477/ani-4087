#include <iostream>
#include <string>
#include <vector>

int main() {
    int nbImages = 1;
    int nbTrames = 0;
    long long x0 = 0;
    long long pas = 0;
    std::cin >> nbImages >> nbTrames >> x0 >> pas;

    std::string modes;
    std::cin >> modes;

    std::vector<long long> emplacement(static_cast<std::size_t>(nbImages), 0);  
    int prochaine = 0;

    bool precedentMontre = false;  
    long long positionPrecedente = 0;
    bool auMoinsUnSaut = false;
    long long sautMin = 0;
    long long sautMax = 0;

    for (int t = 1; t <= nbTrames; ++t) {
        const char mode = modes[static_cast<std::size_t>(t - 1)];

        // On emprunte la prochaine image et on y peint la trame t.
        const int emprunte = prochaine;
        emplacement[static_cast<std::size_t>(emprunte)] = t;

        int indexSoumis = emprunte;                                  // mode A : l'index emprunte
        if (mode == 'P') {
            indexSoumis = (prochaine + nbImages - 1) % nbImages;     // lu AVANT la liberation
        }

        // On rend l'image.
        prochaine = (prochaine + 1) % nbImages;

        if (mode == 'D') {
            indexSoumis = (prochaine + nbImages - 1) % nbImages;     // lu APRES la liberation
        }

        const long long f = emplacement[static_cast<std::size_t>(indexSoumis)];
        if (f == 0) {
            std::cout << t << " NOIR -\n";
            precedentMontre = false;
        } else {
            const long long position = x0 + pas * f;
            if (t == 1 || !precedentMontre) {
                std::cout << t << " " << position << " -\n";
            } else {
                const long long saut = position - positionPrecedente;
                std::cout << t << " " << position << " " << saut << "\n";
                if (!auMoinsUnSaut) {
                    sautMin = saut;
                    sautMax = saut;
                    auMoinsUnSaut = true;
                } else {
                    if (saut < sautMin) {
                        sautMin = saut;
                    }
                    if (saut > sautMax) {
                        sautMax = saut;
                    }
                }
            }
            positionPrecedente = position;
            precedentMontre = true;
        }
    }

    if (!auMoinsUnSaut) {
        std::cout << "SAUTS AUCUN\n";
    } else {
        std::cout << "SAUT MIN " << sautMin << "\n";
        std::cout << "SAUT MAX " << sautMax << "\n";
        std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << "\n";
    }
    return 0;
}