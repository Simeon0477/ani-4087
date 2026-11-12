#include <iostream>
#include <string>

int main() {
    int nbImages = 0;
    std::cin >> nbImages;

    std::string signes;
    if (nbImages > 0) {
        std::cin >> signes;
    }

    int courant = 0;          // current a l'image d'avant (0 avant l'image 1)
    int appuis = 0;
    int relaches = 0;
    int fauxRelaches = 0;
    int tenues = 0;

    for (int t = 1; t <= nbImages; ++t) {
        const char signe = (static_cast<std::size_t>(t - 1) < signes.size()) ? signes[static_cast<std::size_t>(t - 1)] : '0';
        const int active = (signe == 'x') ? 0 : 1;
        const int current = (signe == '1') ? 1 : 0;        // une action inactive vaut toujours 0
        const int changed = (current != courant) ? 1 : 0;  // par rapport a l'image d'avant
        courant = current;

        if (current == 1 && changed == 1) {
            ++appuis;
        }
        if (current == 0 && changed == 1) {
            ++relaches;
            if (active == 0) {
                ++fauxRelaches;
            }
        }
        if (current == 1) {
            ++tenues;
        }
        std::cout << t << " " << current << " " << changed << " " << active << "\n";
    }

    std::cout << "APPUIS " << appuis << "\n";
    std::cout << "RELACHES " << relaches << "\n";
    std::cout << "FAUX RELACHES " << fauxRelaches << "\n";
    std::cout << "TENUES " << tenues << "\n";
    return 0;
}
