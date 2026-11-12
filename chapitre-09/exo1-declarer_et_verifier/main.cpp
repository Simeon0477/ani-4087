#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace {

int NumeroUsage(const std::string &usage) {
    static const char *noms[] = {
        "SELECT", "GRAB", "MENU", "MOVE", "AIM_POSE", "GRIP_POSE", "HAPTIC",
        "SELECT_LEFT", "GRAB_LEFT", "AIM_POSE_LEFT", "GRIP_POSE_LEFT",
        "HAPTIC_LEFT", "MOVE_RIGHT"
    };
    for (int i = 0; i < 13; ++i) {
        if (usage == noms[i]) {
            return i;
        }
    }
    return -1;
}

} // namespace

int main() {
    int nbOrdres = 0;
    std::cin >> nbOrdres;

    std::vector<std::string> noms;       // le nom de l'action de handle h est noms[h - 1]
    std::set<std::string> nomsVus;
    bool attache = false;
    unsigned long long attachees = 0;    // k : actions connues de la session
    int nomsEnDouble = 0;

    for (int i = 0; i < nbOrdres; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cree") {
            std::string nom;
            std::string type;
            std::string usage;
            std::cin >> nom >> type >> usage;

            noms.push_back(nom);
            if (!nomsVus.insert(nom).second) {
                ++nomsEnDouble;
            }
            std::cout << "ACTION " << noms.size() << " " << nom << " " << type << " "
                      << NumeroUsage(usage) << "\n";
        } else if (ordre == "attache") {
            if (attache) {
                std::cout << "ATTACHE REFUSE\n";
            } else {
                attache = true;
                attachees = noms.size();
                std::cout << "ATTACHE " << attachees << "\n";
            }
        } else if (ordre == "lit") {
            unsigned long long h = 0;
            std::cin >> h;
            if (h == 0 || h > noms.size()) {
                std::cout << "LIT " << h << " INVALIDE\n";
            } else if (!attache || h > attachees) {
                std::cout << "LIT " << h << " INCONNUE\n";
            } else {
                std::cout << "LIT " << h << " " << noms[static_cast<std::size_t>(h - 1)] << "\n";
            }
        }
    }

    std::cout << "ACTIONS " << noms.size() << "\n";
    std::cout << "ATTACHEES " << attachees << "\n";
    std::cout << "NOMS EN DOUBLE " << nomsEnDouble << "\n";
    return 0;
}