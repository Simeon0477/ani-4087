#include <iostream>
#include <string>

int main() {
    int nbImages = 0;
    std::cin >> nbImages;

    std::string signes;
    if (nbImages > 0) {
        std::cin >> signes;
    }

    int courant = 0;            // current a l'image d'avant
    bool tenuAvec = false;      // version AVEC le test de active
    bool tenuSans = false;      // version SANS le test de active
    bool tombe = false;         // la version SANS a laisse tomber l'objet : plus de prise possible
    int prisesAvec = 0;
    int prisesSans = 0;
    int chutesSans = 0;
    int coinces = 0;
    int differences = 0;

    for (int t = 1; t <= nbImages; ++t) {
        const char signe = (static_cast<std::size_t>(t - 1) < signes.size()) ? signes[static_cast<std::size_t>(t - 1)] : '0';
        const bool active = (signe != 'x');
        const int current = (signe == '1') ? 1 : 0;
        const int changed = (current != courant) ? 1 : 0;   // calcule meme pendant la coupure
        courant = current;

        // Version AVEC : on ne fait rien quand l'action est inactive.
        if (active) {
            if (current == 1 && changed == 1) {
                tenuAvec = true;
                ++prisesAvec;
            } else if (current == 0 && changed == 1) {
                tenuAvec = false;
            }
        }

        // Version SANS : meme logique, sans le test de active.
        if (!tombe) {
            if (current == 1 && changed == 1) {
                tenuSans = true;
                ++prisesSans;
            } else if (current == 0 && changed == 1) {
                if (!active && tenuSans) {
                    ++chutesSans;          // lacher sur une image inactive : l'objet tombe
                    tombe = true;
                }
                tenuSans = false;
            }
        }

        if (signe == '0' && tenuAvec) {
            ++coinces;
        }
        if (tenuAvec != tenuSans) {
            ++differences;
        }
        std::cout << t << " " << (tenuAvec ? "TENU" : "LIBRE") << " "
                  << (tenuSans ? "TENU" : "LIBRE") << "\n";
    }

    std::cout << "PRISES AVEC " << prisesAvec << "\n";
    std::cout << "PRISES SANS " << prisesSans << "\n";
    std::cout << "CHUTES SANS " << chutesSans << "\n";
    std::cout << "COINCES AVEC " << coinces << "\n";
    std::cout << "DIFFERENCES " << differences << "\n";
    return 0;
}
