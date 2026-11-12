#include <iostream>

int main() {
    int nbAppels = 0;
    std::cin >> nbAppels;

    int bonnes = 0;
    int longues = 0;
    int muettes = 0;
    long long temps = 0;      // la somme peut depasser ce que tient un int

    for (int i = 1; i <= nbAppels; ++i) {
        long long a = 0;      // amplitude, en pour cent
        long long d = 0;      // duree, en millisecondes
        long long f = 0;      // frequence, en hertz
        std::cin >> a >> d >> f;

        const long long amplitude = (a < 0) ? 0 : (a > 100 ? 100 : a);

        std::cout << i << " " << amplitude << " ";
        if (d > 0) {
            std::cout << d;
            temps += d;
        } else {
            std::cout << "MIN";
        }
        std::cout << " ";
        if (f > 0) {
            std::cout << f;
        } else {
            std::cout << "DEFAUT";
        }
        std::cout << " ";

        if (amplitude == 0) {
            std::cout << "MUETTE\n";
            ++muettes;
        } else if (d < 50) {
            std::cout << "BREVE\n";
        } else if (d <= 200) {
            std::cout << "BONNE\n";
            ++bonnes;
        } else {
            std::cout << "LONGUE\n";
            ++longues;
        }
    }

    std::cout << "BONNES " << bonnes << "\n";
    std::cout << "LONGUES " << longues << "\n";
    std::cout << "MUETTES " << muettes << "\n";
    std::cout << "TEMPS " << temps << "\n";
    return 0;
}
