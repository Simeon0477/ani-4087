#include <cmath>
#include <iostream>

int main() {
    int nbImages = 0;
    long long delai = 0;      // d : temps, en millisecondes, entre le rendu et la fin de trame
    std::cin >> nbImages >> delai;

    long long sommePosition = 0;
    long long sommeAngle = 0;

    for (int t = 1; t <= nbImages; ++t) {
        long long x1 = 0;
        long long z1 = 0;
        long long a1 = 0;     // pose du rendu : x, z en millimetres, lacet en milliemes de degre
        long long x2 = 0;
        long long z2 = 0;
        long long a2 = 0;     // pose relue a la fin de trame
        std::cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;

        const double dx = static_cast<double>(x2 - x1);
        const double dz = static_cast<double>(z2 - z1);
        const long long position = std::llround(std::sqrt(dx * dx + dz * dz));   // arrondie au plus proche
        long long angle = a2 - a1;
        if (angle < 0) {
            angle = -angle;                       // sans son signe
        }

        sommePosition += position;
        sommeAngle += angle;
        std::cout << t << " POSITION " << position << " ANGLE " << angle << "\n";
    }

    if (nbImages == 0 || delai == 0) {
        std::cout << "AUCUNE\n";
        return 0;
    }

    // Moyennes arrondies a l'entier inferieur (les sommes sont positives ou nulles).
    std::cout << "MOYENNE POSITION " << sommePosition / nbImages << "\n";
    std::cout << "MOYENNE ANGLE " << sommeAngle / nbImages << "\n";
    // Des milliemes de degre par milliseconde sont des degres par seconde.
    std::cout << "VITESSE " << sommeAngle / (static_cast<long long>(nbImages) * delai) << "\n";
    return 0;
}
