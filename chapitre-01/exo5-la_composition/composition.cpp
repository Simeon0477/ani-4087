#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };
struct Pose  { Vec3D position; Quat orientation; };

Pose parent, enfant;
Vec3D point;

Vec3D operator+(const Vec3D &a, const Vec3D &b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3D operator-(const Vec3D &a, const Vec3D &b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }

double Norme(const Vec3D &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

Vec3D Tourner(const Quat &q, const Vec3D &v) {
    Vec3D qv{q.x, q.y, q.z};
    Vec3D t{
        2.0 * (qv.y*v.z - qv.z*v.y),
        2.0 * (qv.z*v.x - qv.x*v.z),
        2.0 * (qv.x*v.y - qv.y*v.x)
    };
    Vec3D qCrossT{
        qv.y*t.z - qv.z*t.y,
        qv.z*t.x - qv.x*t.z,
        qv.x*t.y - qv.y*t.x
    };
    return {v.x + q.w*t.x + qCrossT.x,
            v.y + q.w*t.y + qCrossT.y,
            v.z + q.w*t.z + qCrossT.z};
}

// Application de la pose
Vec3D AppliquerPose(const Pose &p, const Vec3D &v) {
    return Tourner(p.orientation, v) + p.position;
}

// Produit de Hamilton : QuatMul(a, b) tourne par b, puis par a.
Quat QuatMul(const Quat &a, const Quat &b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

// Compose deux poses : l'enfant est exprime dans le repere du parent.
Pose ComposerPose(const Pose &parent, const Pose &enfant) {
    return { Tourner(parent.orientation, enfant.position) + parent.position,
             QuatMul(parent.orientation, enfant.orientation) };
}

int main() {

    cout << "Entrez les coordonnees de la pose parent " << endl;
    cin >> parent.position.x >> parent.position.y >> parent.position.z;

    cout << "Entrez les coordonnees du quaternion parent " << endl;
    cin >> parent.orientation.x >> parent.orientation.y
        >> parent.orientation.z >> parent.orientation.w;

    cout << "Entrez les coordonnees de la pose enfant " << endl;
    cin >> enfant.position.x >> enfant.position.y >> enfant.position.z;

    cout << "Entrez les coordonnees du quaternion enfant " << endl;
    cin >> enfant.orientation.x >> enfant.orientation.y
        >> enfant.orientation.z >> enfant.orientation.w;

    cout << "Entrez les coordonnees du point " << endl;
    cin >> point.x >> point.y >> point.z;

    Pose compose = ComposerPose(parent, enfant);
    Vec3D parComposition = AppliquerPose(compose, point);
    Vec3D parEtapes = AppliquerPose(parent, AppliquerPose(enfant, point));

    cout << fixed << setprecision(4);
    cout << "PAR COMPOSITION : \n"
         << "X : "
         << parComposition.x << "\n"
         << "Y : "
         << parComposition.y << "\n"
         << "Z : "
         << parComposition.z << "\n"
         << "\n";

    cout << fixed << setprecision(4);
    cout << "PAR ETAPES : \n"
         << "X : "
         << parEtapes.x << "\n"
         << "Y : "
         << parEtapes.y << "\n"
         << "Z : "
         << parEtapes.z << "\n"
         << "\n";

    double ecart = Norme(parComposition - parEtapes);

    cout << fixed << setprecision(4);
    cout << "Ecart : " << ecart << "\n";

    return 0;
}