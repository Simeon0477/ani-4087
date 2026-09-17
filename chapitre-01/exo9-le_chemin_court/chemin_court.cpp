#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };

Vec3D operator*(const Vec3D &v, double s) { return {v.x*s, v.y*s, v.z*s}; }

Quat Conjugue(const Quat &q) { return {-q.x, -q.y, -q.z, q.w}; }

// Produit de Hamilton : QuatMul(a, b) tourne par b, puis par a.
Quat QuatMul(const Quat &a, const Quat &b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

double Dot(const Quat &a, const Quat &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

// Vitesse angulaire moyenne entre q1 et q2 sur une duree dt.
Vec3D VitesseAngulaireMoyenne(Quat q1, Quat q2, double dt, bool forcerCheminCourt) {
    if (forcerCheminCourt && Dot(q1, q2) < 0.0) {
        q2 = {-q2.x, -q2.y, -q2.z, -q2.w}; 
    }

    Quat delta = QuatMul(q2, Conjugue(q1)); 

    double w = max(-1.0, min(1.0, delta.w)); 
    double angle = 2.0 * acos(w);
    double sinDemiAngle = sqrt(1.0 - w*w); 

    Vec3D axe;
    if (sinDemiAngle < 1e-9) {
        axe = {0.0, 0.0, 0.0};
    } else {
        axe = {delta.x / sinDemiAngle, delta.y / sinDemiAngle, delta.z / sinDemiAngle};
    }

    return axe * (angle / dt);
}

void Afficher(const string &nom, const Vec3D &v) {
    cout << nom << " : " << v.x << "  " << v.y << "  " << v.z
         << "   (norme : " << sqrt(v.x*v.x + v.y*v.y + v.z*v.z) << " rad/s)\n";
}

int main() {
    Quat q1, q2;
    double dt;

    cout << "Entrez q1 (x y z w) " << endl;
    cin >> q1.x >> q1.y >> q1.z >> q1.w;
    cout << "Entrez q2 (x y z w) " << endl;
    cin >> q2.x >> q2.y >> q2.z >> q2.w;
    cout << "Entrez dt, en secondes " << endl;
    cin >> dt;

    Vec3D sansForcage = VitesseAngulaireMoyenne(q1, q2, dt, false);
    Vec3D avecForcage = VitesseAngulaireMoyenne(q1, q2, dt, true);

    cout << fixed << setprecision(4);
    Afficher("Sans forcage", sansForcage);
    Afficher("Avec forcage", avecForcage);

    return 0;
}