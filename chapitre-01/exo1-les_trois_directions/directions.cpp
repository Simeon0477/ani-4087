#include <iostream>
#include <iomanip>

using namespace std;
 
struct Vec3D {
    double x, y, z;
};
 
double dot(const Vec3D &a, const Vec3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
 
Vec3D Droite() { return {1.0, 0.0, 0.0}; }
Vec3D Haut()   { return {0.0, 1.0, 0.0}; }
Vec3D Avant()  { return {0.0, 0.0, -1.0}; }
 
double x, y, z;

int main() {
    cout << "Entre les coordonnees du vecteur \n";
    cin >> x >> y >> z;
    Vec3D point{x, y, z};
 
    cout << fixed << setprecision(4);
    cout << "Avant : " << dot(point, Avant()) << "\n";
    cout << "Haut : " << dot(point, Haut())  << "\n";
    cout << "Droite : " << dot(point, Droite()) << "\n";
 
    return 0;
}