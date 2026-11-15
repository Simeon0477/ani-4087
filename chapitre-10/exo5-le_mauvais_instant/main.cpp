#include <iostream>

namespace {

long long Absolu(long long v) {
    return (v < 0) ? -v : v;
}

} // namespace

int main() {
    long long w = 0;          // vitesse de la tete : degres par seconde, donc millièmes de degre par milliseconde
    int nbImages = 0;
    std::cin >> w >> nbImages;

    int fausses = 0;
    long long pireCasque = 0;
    long long pireSimulateur = 0;

    for (int t = 1; t <= nbImages; ++t) {
        long long p = 0;      // instant d'affichage predit
        long long s = 0;      // instant de la soumission
        long long a = 0;      // instant d'affichage reel
        char m = 'R';
        std::cin >> p >> s >> a >> m;

        const long long lacetRendu = w * p;                     // on dessine toujours avec la pose predite
        const long long poseSoumise = (m == 'R') ? w * p : w * s;
        const long long casque = poseSoumise - lacetRendu;      // ce que le compositeur du casque laisse a l'ecran
        const long long simulateur = w * a - w * p;             // le simulateur ne tourne rien : ne depend pas de M

        if (casque != 0) {
            ++fausses;
        }
        if (Absolu(casque) > pireCasque) {
            pireCasque = Absolu(casque);
        }
        if (Absolu(simulateur) > pireSimulateur) {
            pireSimulateur = Absolu(simulateur);
        }
        std::cout << t << " CASQUE " << casque << " SIMULATEUR " << simulateur << "\n";
    }

    std::cout << "FAUSSES " << fausses << "\n";
    std::cout << "PIRE CASQUE " << pireCasque << "\n";
    std::cout << "PIRE SIMULATEUR " << pireSimulateur << "\n";
    return 0;
}
