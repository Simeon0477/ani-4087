#include <iostream>
#include <string>
#include <vector>

int main() {
    int nbApplications = 0;
    std::cin >> nbApplications;

    int muettes = 0;

    for (int i = 1; i <= nbApplications; ++i) {
        std::string fin;          // TOUJOURS, SI_RENDU ou JAMAIS : quand la boucle appelle EndFrame
        int g = 1;                // la chaine de l'oeil gauche est-elle dans la projection ?
        int d = 1;                // la chaine de l'oeil droit est-elle dans la projection ?
        char instant = 'P';       // P : instant predit, N : instant courant
        char pose = 'R';          // R : pose du rendu, F : pose relue
        char espace = 'S';        // S : le bon espace, L : le mauvais
        std::cin >> fin >> g >> d >> instant >> pose >> espace;

        // Les symptomes sur un casque, dans cet ordre.
        std::vector<std::string> symptomes;
        if (fin == "JAMAIS") {
            symptomes.push_back("FIGE");
        } else if (fin == "SI_RENDU") {
            symptomes.push_back("NE_REPART_PAS");
        }
        if (g == 0) {
            symptomes.push_back("OEIL_NOIR_G");
        }
        if (d == 0) {
            symptomes.push_back("OEIL_NOIR_D");
        }
        if (instant == 'N') {
            symptomes.push_back("TREMBLE");
        }
        if (pose == 'F') {
            symptomes.push_back("DE_TRAVERS");
        }
        if (espace == 'L') {
            symptomes.push_back("DECALE");
        }

        std::cout << i << " CASQUE";
        if (symptomes.empty()) {
            std::cout << " AUCUN";
        } else {
            for (const std::string &s : symptomes) {
                std::cout << " " << s;
            }
        }
        std::cout << "\n";

        // Le simulateur n'ecrit que pour une fin de trame manquante ou une chaine absente.
        const bool dit = (fin != "TOUJOURS") || g == 0 || d == 0;
        std::cout << i << " SIMULATEUR " << (dit ? "DIT" : "MUET") << "\n";

        if (!symptomes.empty() && !dit) {
            ++muettes;
        }
    }

    std::cout << "MUETTES " << muettes << "\n";
    return 0;
}
