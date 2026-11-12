#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace {

struct Liaison {
    const char *usage;
    const char *main;
    const char *commande;
};

// La table du simulateur : usage, main, commande du bureau.
const Liaison kTable[] = {
    { "SELECT",         "DROITE", "SOURIS_G" },
    { "GRAB",           "DROITE", "SOURIS_D" },
    { "MENU",           "GAUCHE", "TAB" },
    { "MOVE",           "GAUCHE", "FLECHES" },
    { "AIM_POSE",       "DROITE", "AUCUNE" },
    { "GRIP_POSE",      "DROITE", "AUCUNE" },
    { "HAPTIC",         "DROITE", "AUCUNE" },
    { "SELECT_LEFT",    "GAUCHE", "SOURIS_M" },
    { "GRAB_LEFT",      "GAUCHE", "MAJ_G" },
    { "AIM_POSE_LEFT",  "GAUCHE", "AUCUNE" },
    { "GRIP_POSE_LEFT", "GAUCHE", "AUCUNE" },
    { "HAPTIC_LEFT",    "GAUCHE", "AUCUNE" },
    { "MOVE_RIGHT",     "DROITE", "IJKL" }
};

const Liaison *Chercher(const std::string &usage) {
    for (const Liaison &l : kTable) {
        if (usage == l.usage) {
            return &l;
        }
    }
    return nullptr;
}

} // namespace

int main() {
    int nbActions = 0;
    int nbImages = 0;
    std::cin >> nbActions >> nbImages;

    std::vector<std::string> commandes;   // la commande de chaque action, dans l'ordre
    int droite = 0;
    int gauche = 0;

    for (int i = 0; i < nbActions; ++i) {
        std::string nom;
        std::string usage;
        std::cin >> nom >> usage;
        const Liaison *l = Chercher(usage);
        const std::string main = l ? l->main : "DROITE";
        const std::string commande = l ? l->commande : "AUCUNE";
        commandes.push_back(commande);
        if (main == "GAUCHE") {
            ++gauche;
        } else {
            ++droite;
        }
        std::cout << nom << " " << main << " " << commande << "\n";
    }

    int imagesTete = 0;
    for (int t = 1; t <= nbImages; ++t) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        std::cout << t;
        for (const std::string &commande : commandes) {
            std::cout << " ";
            if (commande == "AUCUNE") {
                std::cout << "-";
            } else if (commande == "FLECHES") {
                const int x = (tenues.count("F_DROITE") ? 1 : 0) - (tenues.count("F_GAUCHE") ? 1 : 0);
                const int y = (tenues.count("F_HAUT") ? 1 : 0) - (tenues.count("F_BAS") ? 1 : 0);
                std::cout << x << "," << y;
            } else if (commande == "IJKL") {
                const int x = (tenues.count("L") ? 1 : 0) - (tenues.count("J") ? 1 : 0);
                const int y = (tenues.count("I") ? 1 : 0) - (tenues.count("K") ? 1 : 0);
                std::cout << x << "," << y;
            } else {
                std::cout << (tenues.count(commande) ? 1 : 0);
            }
        }
        std::cout << "\n";

        const char *tete[] = { "Z", "Q", "S", "D", "W", "A" };
        bool bouge = false;
        for (const char *lettre : tete) {
            if (tenues.count(lettre)) {
                bouge = true;
            }
        }
        if (bouge) {
            ++imagesTete;
        }
    }

    std::cout << "DROITE " << droite << "\n";
    std::cout << "GAUCHE " << gauche << "\n";
    std::cout << "TETE " << imagesTete << "\n";
    return 0;
}