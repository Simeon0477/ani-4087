#ifndef BIBLIOTHEQUE_HPP
#define BIBLIOTHEQUE_HPP

#include "livre.hpp"
#include <vector>
#include <string>

struct Bibliotheque {
    std::string nom;
    std::vector<Livre> livres;
    int capaciteMax;

    void showBiblio(const Bibliotheque& biblio){
        if (livres.empty()) {
            std::cout << "La bibliotheque '" << nom << "' est vide." << std::endl;
            return;
        }
        std::cout << "=== Bibliotheque: " << nom << " (" << livres.size() << " livres) ===" << std::endl;
        for (const auto& livre : livres) {
            livre.afficher();
        }
    }
};

#endif