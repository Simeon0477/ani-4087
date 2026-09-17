#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };
struct Pose  { Vec3D position; Quat orientation; };

Vec3D operator+(const Vec3D &a, const Vec3D &b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3D operator*(const Vec3D &v, double s) { return {v.x*s, v.y*s, v.z*s}; }
double Norme(const Vec3D &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

// Produit de Hamilton : QuatMul(a, b) tourne par b, puis par a.
Quat QuatMul(const Quat &a, const Quat &b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

Quat Normaliser(const Quat &q) {
    double n = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    return {q.x/n, q.y/n, q.z/n, q.w/n};
}

// Avance la pose de dt secondes a vitesses constantes.
Pose AvancerPose(const Pose &pose, const Vec3D &vitesseLineaire,
                  const Vec3D &vitesseAngulaire, double dt) {
    Vec3D nouvellePosition = pose.position + vitesseLineaire * dt;

    double angle = Norme(vitesseAngulaire) * dt;

    Quat delta;
    if (fabs(angle) < 1e-12) {
        delta = {0.0, 0.0, 0.0, 1.0};
    } else {
        Vec3D axe = vitesseAngulaire * (1.0 / Norme(vitesseAngulaire));
        double demiAngle = angle / 2.0;
        double s = sin(demiAngle);
        delta = {axe.x*s, axe.y*s, axe.z*s, cos(demiAngle)};
    }

    Quat nouvelleOrientation = Normaliser(QuatMul(delta, pose.orientation));
    return {nouvellePosition, nouvelleOrientation};
}

int main() {
    Pose pose;
    cout << "Entrez la position de la pose " << endl;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;
    cout << "Entrez le quaternion unitaire de la pose " << endl;
    cin >> pose.orientation.x >> pose.orientation.y
        >> pose.orientation.z >> pose.orientation.w;

    Vec3D vitesseLineaire, vitesseAngulaire;
    cout << "Entrez la vitesse lineaire, m/s (x y z) " << endl;
    cin >> vitesseLineaire.x >> vitesseLineaire.y >> vitesseLineaire.z;
    cout << "Entrez la vitesse angulaire, rad/s (x y z) " << endl;
    cin >> vitesseAngulaire.x >> vitesseAngulaire.y >> vitesseAngulaire.z;

    double dt;
    cout << "Entrez dt, en secondes " << endl;
    cin >> dt;

    Pose poseExtrapolee = AvancerPose(pose, vitesseLineaire, vitesseAngulaire, dt);

    cout << fixed << setprecision(4);
    cout << "\nPose extrapolee :\n";
    cout << "Position   : " << poseExtrapolee.position.x << "  "
         << poseExtrapolee.position.y << "  " << poseExtrapolee.position.z << "\n";
    cout << "Quaternion : " << poseExtrapolee.orientation.x << "  "
         << poseExtrapolee.orientation.y << "  "
         << poseExtrapolee.orientation.z << "  "
         << poseExtrapolee.orientation.w << "\n";

    return 0;
}