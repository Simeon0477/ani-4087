#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    unsigned long long nbImages = 1;
    int nbOrdres = 0;
    std::cin >> nbImages >> nbOrdres;

    std::vector<unsigned long long> emplacements(static_cast<std::size_t>(nbImages), 0ULL);
    std::set<unsigned long long> textures;
    int mortes = 0;
    int larges = 0;

    for (int k = 0; k < nbOrdres; ++k) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cree") {
            unsigned long long h = 0;
            std::cin >> h;
            textures.insert(h);
        } else if (ordre == "detruit") {
            unsigned long long h = 0;
            std::cin >> h;
            textures.erase(h);
        } else if (ordre == "set") {
            unsigned long long i = 0;
            unsigned long long h = 0;
            std::cin >> i >> h;
            if (i >= nbImages) {
                std::cout << "SET IGNORE " << i << "\n";
            } else {
                emplacements[static_cast<std::size_t>(i)] = h;
                if (h > 4294967295ULL) {
                    ++larges;
                }
            }
        } else if (ordre == "get") {
            unsigned long long i = 0;
            std::cin >> i;
            const unsigned long long h = (i >= nbImages) ? 0ULL : emplacements[static_cast<std::size_t>(i)];
            if (h == 0) {
                std::cout << "GET " << i << " 0 VIDE\n";
            } else if (textures.count(h) > 0) {
                std::cout << "GET " << i << " " << h << " VIVANTE\n";
            } else {
                std::cout << "GET " << i << " " << h << " MORTE\n";
                ++mortes;
            }
        }
    }

    std::cout << "MORTES " << mortes << "\n";
    std::cout << "LARGES " << larges << "\n";
    return 0;
}