#include <chrono>
#include <iostream>

#define NB_IMG 1000
#define TIME_LIMIT 11.0
#define SCREEN (1024 * 1024)

using namespace std;

int* pixels = new int[SCREEN];

int main() {

    double longestRender = 0.0;

    for (int img = 0; img < NB_IMG; img++) {

        const auto start = chrono::steady_clock::now();

        // RENDU SEUL
        for (int pixel = 0; pixel < SCREEN; pixel++) {
            pixels[pixel] = 0;
        }

        const auto end = chrono::steady_clock::now();

        const double renderTime =
            chrono::duration<double, milli>(end - start).count();

        if (renderTime > longestRender) {
            longestRender = renderTime;
        }
    }

    const double doubleRender = 2.0 * longestRender;
    const double remaining = TIME_LIMIT - doubleRender;

    cout << "Rendu le plus long : "
         << longestRender << " ms\n";

    cout << "Estimation pour deux rendus : "
         << doubleRender << " ms\n";

    cout << "Temps restant sur 11 ms : "
         << remaining << " ms\n";

    delete[] pixels;

    return 0;
}