#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; }; 
struct Pose  { Vec3D position; Quat orientation; };

Pose pose;
Vec3D point;
 
Vec3D operator+(const Vec3D &a, const Vec3D &b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3D operator-(const Vec3D &a, const Vec3D &b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }
Vec3D operator-(const Vec3D &a) { return {-a.x, -a.y, -a.z}; }
 
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
 
// Inverse de la pose
Pose Inverser(const Pose &p) {
    Quat conj{-p.orientation.x, -p.orientation.y, -p.orientation.z, p.orientation.w};
    Vec3D posInv = Tourner(conj, -p.position);
    return {posInv, conj};
}
 
int main() {
    
    cout << "Entrez les coordonnees de la pose " << endl;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;

    cout << "Entrez les coordonnees du quaternion " << endl;
    cin >> pose.orientation.x >> pose.orientation.y
              >> pose.orientation.z >> pose.orientation.w;

    cout << "Entrez les coordonnees de la position actuelle " << endl;
    cin >> point.x >> point.y >> point.z;
 
    Vec3D transforme = AppliquerPose(pose, point);
    Vec3D retour = AppliquerPose(Inverser(pose), transforme);

    cout << fixed << setprecision(4);
    cout << "POSE : \n" 
         << "X : " 
         << transforme.x << "\n"
         << "Y : " 
         << transforme.y << "\n"
         << "Z :  " 
         << transforme.z << "\n"
         << "\n";
 
    cout << fixed << setprecision(4);
    cout << "INVERSE DE LA POSE : \n" 
         << "X : " 
         << retour.x << "\n"
         << "Y : " 
         << " " << retour.y << "\n"
         << "Z :  " 
         << " " << retour.z << "\n"
         << "\n";

    double ecart = Norme(retour - point);
 
    cout << fixed << setprecision(4);
    cout << "Ecart : " << ecart << "\n";
 
    return 0;
}