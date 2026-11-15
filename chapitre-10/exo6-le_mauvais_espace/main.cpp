#include <iostream>

namespace {

struct Pose {
    long long x = 0;
    long long y = 0;
    long long z = 0;
    int k = 0;      // lacet, en quarts de tour
};

// Tourne (x, z) de k quarts de tour ; y ne tourne pas.
void Tourner(long long x, long long z, int k, long long &rx, long long &rz) {
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
}

// Compose l'ancre A avec une pose p : c'est le passage de LOCAL a STAGE.
Pose Composer(const Pose &a, const Pose &p) {
    long long dx = 0;
    long long dz = 0;
    Tourner(p.x, p.z, a.k, dx, dz);       // on tourne la position AVANT d'ajouter l'ancre
    Pose r;
    r.x = a.x + dx;
    r.y = a.y + p.y;
    r.z = a.z + dz;
    r.k = (a.k + p.k) % 4;
    return r;
}

} // namespace

int main() {
    Pose ancre;
    std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;

    int nbPoses = 0;
    std::cin >> nbPoses;

    int justes = 0;
    int fausses = 0;

    for (int i = 1; i <= nbPoses; ++i) {
        char demande = 'S';      // espace dans lequel la pose a ete demandee
        char declare = 'S';      // espace declare dans la couche
        Pose p;
        std::cin >> demande >> declare >> p.x >> p.y >> p.z >> p.k;

        const Pose vraie = (demande == 'S') ? p : Composer(ancre, p);
        const Pose crue = (declare == 'S') ? p : Composer(ancre, p);   // le compositeur lit p dans l'espace declare

        const long long dx = crue.x - vraie.x;
        const long long dy = crue.y - vraie.y;
        const long long dz = crue.z - vraie.z;
        const int dk = (crue.k - vraie.k + 4) % 4;

        std::cout << i << " CRU " << crue.x << " " << crue.y << " " << crue.z << " " << crue.k << "\n";
        std::cout << i << " ECART " << dx << " " << dy << " " << dz << " " << dk << "\n";
        if (dx == 0 && dy == 0 && dz == 0 && dk == 0) {
            ++justes;
        } else {
            ++fausses;
        }
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUSSES " << fausses << "\n";
    return 0;
}
