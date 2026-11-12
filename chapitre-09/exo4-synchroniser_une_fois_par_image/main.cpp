#include <iostream>

int main() {
    int nbImages = 0;
    std::cin >> nbImages;

    int current = 0;
    int changed = 0;
    int active = 0;
    int pPrecedent = 0;       // p a l'image d'avant (0 avant l'image 1)
    int appuisReels = 0;
    int saisies = 0;
    int syncRefusees = 0;

    for (int t = 1; t <= nbImages; ++t) {
        int p = 0;
        int s = 0;
        int f = 0;
        std::cin >> p >> s >> f;

        if (p == 1 && pPrecedent == 0) {
            ++appuisReels;
        }
        pPrecedent = p;

        for (int i = 0; i < s; ++i) {
            if (f == 0) {
                ++syncRefusees;           // sans le focus : refuse, rien ne change
            } else {
                changed = (p != current) ? 1 : 0;
                current = p;
                active = 1;
            }
        }

        const bool saisit = (current == 1 && changed == 1);
        if (saisit) {
            ++saisies;
        }
        std::cout << t << " " << current << " " << changed << " " << active << " "
                  << (saisit ? "SAISIT" : "-") << "\n";
    }

    std::cout << "APPUIS REELS " << appuisReels << "\n";
    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "SYNC REFUSEES " << syncRefusees << "\n";
    return 0;
}
