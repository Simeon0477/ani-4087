#include <chrono>
#include <iostream>

#define NB_IMG 1000  // Nombres d'images (Nombres d'itérations)
#define TIME_LIMIT 11.0 // Seuil de temps (En millisecondes)
#define SCREEN 1024 * 1024 // Simulation d'un écran de définition 1024*1024 (Nombre total de pixels de l'écran)

using namespace std;

int* pixels = new int[SCREEN]; // Tableau représentant les pixels
double longestImg = 0.0; // Temps mis par l'image la plus longue
int badImgCount = 0; // Nombre de mauvaises images (Images ayant dépassé le seuil des 11 ms)

int main(){
    for (int img = 0; img < NB_IMG; img++) {
        // Initialisation du chronomètre
        const auto start = chrono::steady_clock::now();

        // On efface tous les pixels de l'écran.
        for (int pixel = 0; pixel < SCREEN; pixel++) {
            pixels[pixel] = 0;
        }

        // Arrêt du chronomètre
        const auto end = chrono::steady_clock::now();
        const double imgTime = chrono::duration<double, milli>(end - start).count();

        // Détermination de l'image la plus longue
        if (imgTime > longestImg) {
            longestImg = imgTime;
        }

        // On compte les images qui dépassent la limite de 11 ms.
        if (imgTime > TIME_LIMIT) {
            badImgCount++;
        }
    }

    cout << "Plus longue image : " << longestImg << " ms\n";
    cout << "Mauvaises images : " << badImgCount << " sur " << NB_IMG << "\n";

    // Libération de la mémoire
    delete[] pixels;
    return 0;
}



