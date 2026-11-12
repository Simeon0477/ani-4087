#include <cmath>
#include <iostream>
#include <vector>

namespace {

struct Vec3 {
    long long x = 0;
    long long y = 0;
    long long z = 0;
};

// Poses locales dans le repere de la tete, main droite : x vers la droite, y vers le haut,
// l'avant de la tete est vers les z negatifs.
const Vec3 kPaumeDroite = { 180, -300, -250 };
const Vec3 kViseeDroite = { 180, -250, -400 };

// Passe une pose locale dans la salle : main gauche (x change de signe AVANT la rotation),
// rotation de (x, z) de k quarts de tour, puis position de la tete.
Vec3 VersLaSalle(Vec3 local, bool gauche, int k, const Vec3 &tete) {
    if (gauche) {
        local.x = -local.x;
    }
    long long x = local.x;
    long long z = local.z;
    switch (k % 4) {
        case 0: break;
        case 1: x = local.z;  z = -local.x; break;
        case 2: x = -local.x; z = -local.z; break;
        default: x = -local.z; z = local.x; break;
    }
    Vec3 r;
    r.x = x + tete.x;
    r.y = local.y + tete.y;
    r.z = z + tete.z;
    return r;
}

long long Distance2(const Vec3 &a, const Vec3 &b) {
    const long long dx = a.x - b.x;
    const long long dy = a.y - b.y;
    const long long dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

void Afficher(const char *nom, const Vec3 &p) {
    std::cout << nom << " " << p.x << " " << p.y << " " << p.z << "\n";
}

// L'objet le plus proche de la pose, a 150 mm au plus (distance au carre : 22500 au plus).
// A egalite, le plus petit numero gagne. Retourne 0 s'il n'y en a aucun.
int Plusproche(const Vec3 &pose, const std::vector<Vec3> &objets) {
    int meilleur = 0;
    long long meilleureDistance = 0;
    for (std::size_t j = 0; j < objets.size(); ++j) {
        const long long d2 = Distance2(pose, objets[j]);
        if (d2 <= 22500 && (meilleur == 0 || d2 < meilleureDistance)) {
            meilleur = static_cast<int>(j) + 1;
            meilleureDistance = d2;
        }
    }
    return meilleur;
}

void AfficherSaisie(const char *nom, int j) {
    std::cout << "SAISIE " << nom << " ";
    if (j == 0) {
        std::cout << "AUCUNE\n";
    } else {
        std::cout << j << "\n";
    }
}

} // namespace

int main() {
    int nbTetes = 0;
    int nbObjets = 0;
    std::cin >> nbTetes >> nbObjets;

    struct Tete {
        Vec3 position;
        int lacet = 0;
    };
    std::vector<Tete> tetes(static_cast<std::size_t>(nbTetes));
    for (Tete &t : tetes) {
        std::cin >> t.position.x >> t.position.y >> t.position.z >> t.lacet;
    }
    std::vector<Vec3> objets(static_cast<std::size_t>(nbObjets));
    for (Vec3 &o : objets) {
        std::cin >> o.x >> o.y >> o.z;
    }

    for (int h = 1; h <= nbTetes; ++h) {
        const Tete &t = tetes[static_cast<std::size_t>(h - 1)];
        const Vec3 paumeD = VersLaSalle(kPaumeDroite, false, t.lacet, t.position);
        const Vec3 viseeD = VersLaSalle(kViseeDroite, false, t.lacet, t.position);
        const Vec3 paumeG = VersLaSalle(kPaumeDroite, true, t.lacet, t.position);
        const Vec3 viseeG = VersLaSalle(kViseeDroite, true, t.lacet, t.position);

        std::cout << "TETE " << h << "\n";
        Afficher("PAUME D", paumeD);
        Afficher("VISEE D", viseeD);
        Afficher("PAUME G", paumeG);
        Afficher("VISEE G", viseeG);
        AfficherSaisie("PAUME", Plusproche(paumeD, objets));
        AfficherSaisie("VISEE", Plusproche(viseeD, objets));
    }

    // L'ecart entre la paume droite et la visee droite ne depend pas de la tete :
    // les deux poses gardent son orientation. On le calcule dans le repere de la tete.
    const double ecart = std::sqrt(static_cast<double>(Distance2(kPaumeDroite, kViseeDroite)));
    std::cout << "ECART " << std::llround(ecart) << "\n";
    return 0;
}
