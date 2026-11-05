#include <iostream>

int main() {
    int nbScenarios = 0;
    std::cin >> nbScenarios;

    for (int s = 0; s < nbScenarios; ++s) {
        long long n = 1;
        long long gardee = 0;     
        long long nbTrames = 0;   
        std::cin >> n >> gardee >> nbTrames;

        std::cout << "CIBLES " << n << " " << gardee;
        for (long long u = 1; u <= nbTrames; ++u) {
            std::cout << " " << (u - 1) % n;
        }
        std::cout << "\n";

        long long conflits = 0;
        for (long long u = 1; u <= nbTrames; ++u) {
            const long long image = (u - 1) % n;
            const long long premiere = (u - gardee > 1) ? (u - gardee) : 1;
            bool enConflit = false;
            for (long long w = premiere; w <= u - 1; ++w) {
                if ((w - 1) % n == image) {
                    enConflit = true;       
                    break;
                }
            }
            if (enConflit) {
                ++conflits;
            }
        }
        std::cout << "CONFLITS " << n << " " << gardee << " " << conflits << "\n";
    }
    return 0;
}