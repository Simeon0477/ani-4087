#include <iostream>
#include <string>

int main() {
    int nbImages = 1;
    unsigned long long depart = 0;
    int nbOrdres = 0;
    std::cin >> nbImages >> depart >> nbOrdres;

    unsigned long long variables[26];
    for (int i = 0; i < 26; ++i) {
        variables[i] = depart;
    }

    int prochaine = 0;
    bool emprunte = false;

    for (int i = 0; i < nbOrdres; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire") {
            std::string nom;
            std::cin >> nom;
            const int indice = nom[0] - 'a';
            if (emprunte) {
                std::cout << "ACQUIRE FAUX " << nom << " " << variables[indice] << "\n";
            } else {
                variables[indice] = static_cast<unsigned long long>(prochaine);
                emprunte = true;
                std::cout << "ACQUIRE VRAI " << nom << " " << variables[indice] << "\n";
            }
        } else if (ordre == "release") {
            if (!emprunte) {
                std::cout << "RELEASE FAUX\n";
            } else {
                prochaine = (prochaine + 1) % nbImages;
                emprunte = false;
                std::cout << "RELEASE VRAI\n";
            }
        } else if (ordre == "last") {
            std::cout << "LAST " << (prochaine + nbImages - 1) % nbImages << "\n";
        }
    }

    std::cout << "EMPRUNTEE " << (emprunte ? "OUI" : "NON") << "\n";
    std::cout << "PROCHAINE " << prochaine << "\n";
    return 0;
}