#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Meuble {
    string nom;
    double largeur, profondeur, hauteur;
};

struct Salle {
    double largeur, profondeur, hauteurPlafond;
    vector<Meuble> mobilier;
};

Meuble MettreAEchelle(const Meuble &m, double facteur) {
    return { m.nom, m.largeur * facteur, m.profondeur * facteur, m.hauteur * facteur };
}

Salle MettreAEchelle(const Salle &s, double facteur) {
    Salle resultat;
    resultat.largeur = s.largeur * facteur;
    resultat.profondeur = s.profondeur * facteur;
    resultat.hauteurPlafond = s.hauteurPlafond * facteur;
    for (const Meuble &m : s.mobilier)
        resultat.mobilier.push_back(MettreAEchelle(m, facteur));
    return resultat;
}

void AfficherSalle(const Salle &s) {
    cout << fixed << setprecision(2);
    cout << "Salle : " << s.largeur << " x " << s.profondeur
         << " m, plafond a " << s.hauteurPlafond << " m\n";
    for (const Meuble &m : s.mobilier) {
        cout << "  - " << m.nom << " : " << m.largeur << " x "
             << m.profondeur << " x " << m.hauteur << " m\n";
    }
}

int main() {
    Salle salleReference;
    salleReference.largeur = 4.00;
    salleReference.profondeur = 5.00;
    salleReference.hauteurPlafond = 2.50;
    salleReference.mobilier = {
        { "Table",  1.20, 0.75, 0.75 },
        { "Chaise", 0.45, 0.45, 0.90 },
        { "Porte",  0.90, 0.05, 2.00 }
    };

    double facteur;
    cout << "Entrez le facteur d'echelle " << endl;
    cin >> facteur;

    Salle salleEchelle = MettreAEchelle(salleReference, facteur);

    cout << "\nSalle a l'echelle " << facteur << " :\n";
    AfficherSalle(salleEchelle);

    return 0;
}