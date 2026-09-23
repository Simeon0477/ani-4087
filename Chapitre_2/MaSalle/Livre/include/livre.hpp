#ifndef LIVRE_HPP
#define LIVRE_HPP

#include <string>

struct Livre {
    std::string titre;
    std::string auteur;
    int anneePublication;
    bool estDisponible;

    void afficher() const {
        std::cout << titre << " - " << auteur 
                  << " (" << anneePublication << ") "
                  << (estDisponible ? "Disponible" : "Emprunte") << std::endl;
    }
};

#endif