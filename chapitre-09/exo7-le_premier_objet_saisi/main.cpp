#include <iostream>
#include <vector>

namespace {

struct Pose {
    long long x = 0;
    long long y = 0;
    int k = 0;      // quarts de tour, de 0 a 3, sens inverse des aiguilles d'une montre
};

// Tourne le vecteur (u, v) de k quarts de tour.
void Tourner(long long u, long long v, int k, long long &ru, long long &rv) {
    switch (k % 4) {
        case 0: ru = u;  rv = v;  break;
        case 1: ru = -v; rv = u;  break;
        case 2: ru = -u; rv = -v; break;
        default: ru = v; rv = -u; break;
    }
}

// A * B : position de A plus la position de B tournee de A.k ; angle (A.k + B.k) % 4.
Pose Composer(const Pose &a, const Pose &b) {
    long long dx = 0;
    long long dy = 0;
    Tourner(b.x, b.y, a.k, dx, dy);
    Pose r;
    r.x = a.x + dx;
    r.y = a.y + dy;
    r.k = (a.k + b.k) % 4;
    return r;
}

// Inverse de A : angle (4 - A.k) % 4, position (-A.x, -A.y) tournee de cet angle.
Pose Inverse(const Pose &a) {
    Pose r;
    r.k = (4 - a.k) % 4;
    Tourner(-a.x, -a.y, r.k, r.x, r.y);
    return r;
}

} // namespace

int main() {
    int nbObjets = 0;
    int nbImages = 0;
    std::cin >> nbObjets >> nbImages;

    std::vector<Pose> objets(static_cast<std::size_t>(nbObjets));
    for (int i = 0; i < nbObjets; ++i) {
        std::cin >> objets[static_cast<std::size_t>(i)].x >> objets[static_cast<std::size_t>(i)].y
                 >> objets[static_cast<std::size_t>(i)].k;
    }

    int tenu = 0;               // numero de l'objet tenu, 0 = aucun
    Pose attache;               // pose de l'objet dans le repere de la main, figee a la saisie
    int bPrecedent = 0;
    int saisies = 0;
    int ratees = 0;

    for (int t = 1; t <= nbImages; ++t) {
        Pose paume;
        int b = 0;
        std::cin >> paume.x >> paume.y >> paume.k >> b;

        bool rate = false;
        if (b == 1 && bPrecedent == 0) {
            // un appui : on cherche l'objet le plus proche, a 150 mm au plus
            int meilleur = 0;
            long long meilleureDistance = 0;
            for (int j = 1; j <= nbObjets; ++j) {
                const Pose &o = objets[static_cast<std::size_t>(j - 1)];
                const long long dx = o.x - paume.x;
                const long long dy = o.y - paume.y;
                const long long d2 = dx * dx + dy * dy;
                if (d2 <= 22500 && (meilleur == 0 || d2 < meilleureDistance)) {
                    meilleur = j;
                    meilleureDistance = d2;
                }
            }
            if (meilleur != 0) {
                tenu = meilleur;
                attache = Composer(Inverse(paume), objets[static_cast<std::size_t>(meilleur - 1)]);
                ++saisies;
            } else {
                rate = true;
                ++ratees;
            }
        } else if (b == 0 && bPrecedent == 1) {
            tenu = 0;           // un relachement : l'objet reste ou il est
        }
        bPrecedent = b;

        if (tenu != 0) {
            objets[static_cast<std::size_t>(tenu - 1)] = Composer(paume, attache);
            const Pose &o = objets[static_cast<std::size_t>(tenu - 1)];
            std::cout << t << " TIENT " << tenu << " " << o.x << " " << o.y << " " << o.k << "\n";
        } else if (rate) {
            std::cout << t << " RATE\n";
        } else {
            std::cout << t << " LIBRE\n";
        }
    }

    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "RATEES " << ratees << "\n";
    for (int j = 1; j <= nbObjets; ++j) {
        const Pose &o = objets[static_cast<std::size_t>(j - 1)];
        std::cout << "OBJET " << j << " " << o.x << " " << o.y << " " << o.k << "\n";
    }
    return 0;
}
