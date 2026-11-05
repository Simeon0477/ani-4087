#include <cstdint>
#include <iostream>

int main() {
    int nbEtats = 0;
    std::cin >> nbEtats;

    int refusees = 0;
    int fauxSigne = 0;
    int fauxNonSigne = 0;

    for (int i = 0; i < nbEtats; ++i) {
        unsigned long long n = 0;
        unsigned long long r = 0;
        std::cin >> n >> r;

        if (n == 0 || n > 4) {
            std::cout << n << " " << r << " REFUSEE\n";
            ++refusees;
            continue;
        }

        const unsigned long long prochaine = r % n;            
        const int nbImages = static_cast<int>(n);
        const int p = static_cast<int>(prochaine);

        const int juste = (p + nbImages - 1) % nbImages;       
        const int signe = (p - 1) % nbImages;                  
        const std::uint32_t nonsigne =
            (static_cast<std::uint32_t>(p) - 1u) % static_cast<std::uint32_t>(nbImages);

        if (signe != juste) {
            ++fauxSigne;
        }
        if (static_cast<int>(nonsigne) != juste) {
            ++fauxNonSigne;
        }

        std::cout << n << " " << r << " " << prochaine << " " << juste << " "
                  << signe << " " << nonsigne << "\n";
    }

    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "FAUX SIGNE " << fauxSigne << "\n";
    std::cout << "FAUX NON SIGNE " << fauxNonSigne << "\n";
    return 0;
}