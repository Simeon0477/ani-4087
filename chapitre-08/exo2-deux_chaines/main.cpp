#include <iostream>
#include <string>

int main() {
    int nbChaines = 0;
    std::cin >> nbChaines;

    long long acceptees = 0;
    long long occupes = 0;
    long long gauche = 0;
    long long droit = 0;
    long long sansNom = 0;

    for (int i = 0; i < nbChaines; ++i) {
        long long largeur = 0;
        long long hauteur = 0;
        long long images = 0;
        int oeil = 0;
        std::string nom;
        std::cin >> largeur >> hauteur >> images >> oeil >> nom;

        const bool anonyme = (nom == "-");
        const std::string affiche = anonyme ? "SANS-NOM" : nom;

        if (largeur == 0 || hauteur == 0) {
            std::cout << "REFUSEE " << affiche << " TAILLE\n";
        } else if (images == 0 || images > 4) {
            std::cout << "REFUSEE " << affiche << " IMAGES\n";
        } else {
            std::cout << "CHAINE " << affiche << " " << largeur << " " << hauteur << " "
                      << images << " " << (oeil == 0 ? "GAUCHE" : "DROIT") << "\n";
            ++acceptees;
            occupes += images;
            if (oeil == 0) {
                ++gauche;
            } else {
                ++droit;
            }
            if (anonyme) {
                ++sansNom;
            }
        }
    }

    std::cout << "ACCEPTEES " << acceptees << "\n";
    std::cout << "EMPLACEMENTS " << 4 * acceptees << "\n";
    std::cout << "OCCUPES " << occupes << "\n";
    std::cout << "GAUCHE " << gauche << "\n";
    std::cout << "DROIT " << droit << "\n";
    std::cout << "SANS NOM " << sansNom << "\n";
    return 0;
}