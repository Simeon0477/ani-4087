#include <iostream>
#include <string>

namespace {

// Une fausse session, qui suit le drapeau « trame ouverte » du moteur.
class Session {
public:
    bool Wait() {
        if (ouverte_) {
            ++refus_;
            return false;
        }
        return true;
    }

    bool Begin() {
        if (ouverte_) {
            ++refus_;
            return false;
        }
        ouverte_ = true;
        ++debuts_;
        return true;
    }

    bool End() {
        if (!ouverte_) {
            ++refus_;
            return false;
        }
        ouverte_ = false;
        ++fins_;
        return true;
    }

    int Debuts() const { return debuts_; }
    int Fins() const { return fins_; }
    int Refus() const { return refus_; }
    bool Ouverte() const { return ouverte_; }

private:
    bool ouverte_ = false;
    int debuts_ = 0;
    int fins_ = 0;
    int refus_ = 0;
};

// Termine la trame toute seule, quel que soit le chemin de sortie.
// On ne peut pas la copier : une copie fermerait la trame deux fois.
class GardeTrame {
public:
    explicit GardeTrame(Session &session) : session_(session) {}
    ~GardeTrame() { session_.End(); }

    GardeTrame(const GardeTrame &) = delete;
    GardeTrame &operator=(const GardeTrame &) = delete;

private:
    Session &session_;
};

// Sans la garde : End est ecrit en bas du corps de boucle, C et R le sautent.
int BoucleSansGarde(Session &session, const std::string &signes) {
    int images = 0;
    for (char c : signes) {
        char signe = c;
        if (!session.Wait() && (signe == 'N' || signe == 'C')) {
            signe = 'V';                 // sans etat de Wait, la boucle ne rend pas
        }
        session.Begin();
        if (signe == 'C') {
            continue;                    // les vues echouent : on saute la fin
        }
        if (signe == 'R') {
            return images;               // return : on saute la fin et on s'arrete
        }
        if (signe == 'N') {
            ++images;
        }
        session.End();
    }
    return images;
}

// Avec la garde : le destructeur ferme la trame sur tous les chemins.
int BoucleAvecGarde(Session &session, const std::string &signes) {
    int images = 0;
    for (char c : signes) {
        char signe = c;
        if (!session.Wait() && (signe == 'N' || signe == 'C')) {
            signe = 'V';
        }
        session.Begin();
        GardeTrame garde(session);       // cree juste apres Begin
        if (signe == 'C') {
            continue;
        }
        if (signe == 'R') {
            return images;
        }
        if (signe == 'N') {
            ++images;
        }
    }
    return images;
}

void Afficher(const char *nom, const Session &session, int images) {
    std::cout << nom << " DEBUTS " << session.Debuts() << " FINS " << session.Fins()
              << " REFUS " << session.Refus() << " IMAGES " << images
              << " OUVERTE " << (session.Ouverte() ? "OUI" : "NON") << "\n";
}

} // namespace

int main() {
    int nbImages = 0;
    std::cin >> nbImages;
    std::string signes;
    if (nbImages > 0) {
        std::cin >> signes;
    }

    Session sans;
    const int imagesSans = BoucleSansGarde(sans, signes);
    Afficher("SANS", sans, imagesSans);

    Session avec;
    const int imagesAvec = BoucleAvecGarde(avec, signes);
    Afficher("AVEC", avec, imagesAvec);
    return 0;
}
