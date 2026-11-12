#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace {

// Les actions sont declarees une seule fois : un nom et une intention (un usage).
// Aucun nom de bouton ou de touche n'apparait dans ce programme : les commandes ne viennent
// que de la table lue sur l'entree.
struct Action {
    std::string nom;
    std::string usage;
};

// Joue une table : affiche TABLE i, les actions inactives, puis une ligne par image.
std::vector<std::string> JouerUneTable(int numero, const std::vector<Action> &actions) {
    int nbLiaisons = 0;
    std::cin >> nbLiaisons;
    std::map<std::string, std::string> table;           // usage -> commande
    for (int i = 0; i < nbLiaisons; ++i) {
        std::string usage;
        std::string commande;
        std::cin >> usage >> commande;
        table[usage] = commande;
    }

    int nbImages = 0;
    std::cin >> nbImages;

    std::cout << "TABLE " << numero << "\n";
    for (const Action &a : actions) {
        if (table.find(a.usage) == table.end()) {
            std::cout << "INACTIVE " << a.nom << "\n";
        }
    }

    std::vector<bool> appuyeAvant(actions.size(), false);   // rien n'est appuye avant l'image 1
    std::vector<std::string> lignes;
    for (int t = 1; t <= nbImages; ++t) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string commande;
            std::cin >> commande;
            tenues.insert(commande);
        }

        std::string ligne = std::to_string(t);
        bool aucune = true;
        for (std::size_t i = 0; i < actions.size(); ++i) {
            const auto it = table.find(actions[i].usage);
            const bool appuyee = (it != table.end()) && (tenues.count(it->second) > 0);
            if (appuyee && !appuyeAvant[i]) {
                ligne += " " + actions[i].nom;
                aucune = false;
            }
            appuyeAvant[i] = appuyee;
        }
        if (aucune) {
            ligne += " -";
        }
        std::cout << ligne << "\n";
        lignes.push_back(ligne);
    }
    return lignes;
}

} // namespace

int main() {
    int nbActions = 0;
    std::cin >> nbActions;
    std::vector<Action> actions(static_cast<std::size_t>(nbActions));
    for (Action &a : actions) {
        std::cin >> a.nom >> a.usage;
    }

    const std::vector<std::string> premiere = JouerUneTable(1, actions);
    const std::vector<std::string> seconde = JouerUneTable(2, actions);

    std::cout << "IDENTIQUES " << (premiere == seconde ? "OUI" : "NON") << "\n";
    return 0;
}
