#include <iostream>
#include <string>

int main() {
    int nbImages = 1;
    int nbOrdres = 0;
    std::cin >> nbImages >> nbOrdres;

    int prochaine = 0;           
    bool emprunte = false;      
    bool dessinee = false;       
    bool renduNeuf = false;      
    bool dernierVide = false;    
    int soumises = 0;
    int refus = 0;
    int horsEmprunt = 0;

    for (int i = 0; i < nbOrdres; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire") {
            if (emprunte) {
                std::cout << "ACQUIRE REFUSE\n";
                ++refus;
            } else {
                emprunte = true;
                dessinee = false;
                std::cout << "ACQUIRE " << prochaine << "\n";
            }
        } else if (ordre == "draw") {
            if (emprunte) {
                dessinee = true;
                std::cout << "DRAW " << prochaine << "\n";
            } else {
                std::cout << "DRAW HORS EMPRUNT\n";
                ++horsEmprunt;
            }
        } else if (ordre == "release") {
            if (!emprunte) {
                std::cout << "RELEASE REFUSE\n";
                ++refus;
            } else {
                prochaine = (prochaine + 1) % nbImages;
                emprunte = false;
                renduNeuf = true;
                dernierVide = !dessinee;
                std::cout << "RELEASE OK\n";
            }
        } else if (ordre == "submit") {
            if (emprunte) {
                std::cout << "SUBMIT REFUSE EMPRUNTEE\n";
                ++refus;
            } else if (!renduNeuf) {
                std::cout << "SUBMIT REFUSE RIEN\n";
                ++refus;
            } else {
                const int j = (prochaine + nbImages - 1) % nbImages;
                std::cout << "SUBMIT " << j << (dernierVide ? " VIDE" : "") << "\n";
                ++soumises;
                renduNeuf = false;
            }
        }
    }

    std::cout << "SOUMISES " << soumises << "\n";
    std::cout << "REFUS " << refus << "\n";
    std::cout << "HORS EMPRUNT " << horsEmprunt << "\n";
    return 0;
}