#include <iostream>
#include <string>
#include <vector>

int main() {
    int nbImages = 0;
    std::cin >> nbImages;

    int justes = 0;
    int fautives = 0;

    for (int t = 1; t <= nbImages; ++t) {
        int n = 0;
        std::cin >> n;
        std::vector<std::string> appels(static_cast<std::size_t>(n));
        for (std::string &a : appels) {
            std::cin >> a;
        }

        // Chaque image repart de zero.
        bool attendu = false;           // WAIT fait
        bool commence = false;          // BEGIN fait
        bool fini = false;              // END accepte
        bool vues = false;              // VUES fait
        bool empruntee[2] = { false, false };   // 0 = gauche, 1 = droite

        int place = 0;
        std::string code;

        for (int i = 0; i < n && code.empty(); ++i) {
            const std::string &a = appels[static_cast<std::size_t>(i)];
            const int p = i + 1;
            int oeil = -1;
            if (!a.empty() && (a.back() == 'G' || a.back() == 'D')) {
                oeil = (a.back() == 'G') ? 0 : 1;
            }

            if (fini) {
                code = "APRES_END";
            } else if (a == "WAIT") {
                if (commence) {
                    code = "WAIT_APRES_BEGIN";
                } else {
                    attendu = true;
                }
            } else if (a == "BEGIN") {
                if (commence) {
                    code = "DOUBLE_BEGIN";
                } else if (!attendu) {
                    code = "BEGIN_SANS_WAIT";
                } else {
                    commence = true;
                }
            } else if (a == "VUES") {
                if (!attendu) {
                    code = "VUES_SANS_WAIT";
                } else {
                    vues = true;
                }
            } else if (a == "PREND_G" || a == "PREND_D") {
                if (!commence) {
                    code = "PREND_SANS_BEGIN";
                } else if (!vues) {
                    code = "PREND_SANS_VUES";
                } else if (empruntee[oeil]) {
                    code = "DOUBLE_PREND";
                } else {
                    empruntee[oeil] = true;
                }
            } else if (a == "LACHE_G" || a == "LACHE_D") {
                if (!empruntee[oeil]) {
                    code = "LACHE_SANS_PREND";
                } else {
                    empruntee[oeil] = false;
                }
            } else if (a == "END") {
                if (!commence) {
                    code = "END_SANS_BEGIN";
                } else if (empruntee[0] || empruntee[1]) {
                    code = "END_IMAGE_PRISE";
                } else {
                    fini = true;
                }
            }
            if (!code.empty()) {
                place = p;
            }
        }

        if (code.empty() && !fini) {
            code = "SANS_END";
            place = n + 1;
        }

        if (code.empty()) {
            std::cout << t << " OK\n";
            ++justes;
        } else {
            std::cout << t << " FAUTE " << place << " " << code << "\n";
            ++fautives;
        }
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUTIVES " << fautives << "\n";
    return 0;
}
