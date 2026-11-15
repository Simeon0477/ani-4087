#include <cmath>
#include <iostream>

namespace {

struct Pose {
    long long x = 0;
    long long y = 0;
    long long z = 0;
    int k = 0;
};

void Tourner(long long x, long long z, int k, long long &rx, long long &rz) {
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
}

Pose Composer(const Pose &a, const Pose &p) {
    long long dx = 0;
    long long dz = 0;
    Tourner(p.x, p.z, a.k, dx, dz);
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
    long long ex = 0;
    long long ey = 0;
    long long ez = 0;
    std::cin >> ex >> ey >> ez;

    int nbPanneaux = 0;
    std::cin >> nbPanneaux;

    for (int i = 1; i <= nbPanneaux; ++i) {
        char espace = '-';
        Pose p;
        long long w = 0;
        long long h = 0;
        std::cin >> espace >> p.x >> p.y >> p.z >> p.k >> w >> h;

        // Un panneau dont l'espace n'est pas precise est dans LOCAL.
        const bool stage = (espace == 'S');
        const Pose centre = stage ? p : Composer(ancre, p);

        std::cout << "PANNEAU " << i << " " << (stage ? "STAGE" : "LOCAL") << "\n";

        // Les quatre coins, dans le plan (x, y) du panneau, z = 0, dans cet ordre.
        const long long coins[4][2] = {
            { -w / 2, -h / 2 }, { w / 2, -h / 2 }, { w / 2, h / 2 }, { -w / 2, h / 2 }
        };
        for (const auto &c : coins) {
            long long rx = 0;
            long long rz = 0;
            Tourner(c[0], 0, centre.k, rx, rz);   // seul (x, z) tourne ; la hauteur ne tourne jamais
            std::cout << centre.x + rx << " " << centre.y + c[1] << " " << centre.z + rz << "\n";
        }

        const double dx = static_cast<double>(centre.x - ex);
        const double dy = static_cast<double>(centre.y - ey);
        const double dz = static_cast<double>(centre.z - ez);
        std::cout << "DISTANCE " << std::llround(std::sqrt(dx * dx + dy * dy + dz * dz)) << "\n";
    }

    std::cout << "PANNEAUX " << nbPanneaux << "\n";
    return 0;
}
