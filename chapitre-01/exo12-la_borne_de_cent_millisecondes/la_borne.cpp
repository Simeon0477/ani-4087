#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };
struct Pose  { Vec3D position; Quat orientation; };

const double W0 = 180.0;   
const double TAU = 0.3;    

Vec3D operator+(const Vec3D &a, const Vec3D &b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
Vec3D operator*(const Vec3D &v, double s) { return {v.x*s, v.y*s, v.z*s}; }
double Norme(const Vec3D &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

Quat Conjugue(const Quat &q) { return {-q.x, -q.y, -q.z, q.w}; }
double Dot(const Quat &a, const Quat &b) { return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w; }

Quat QuatMul(const Quat &a, const Quat &b) {
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

Quat Normaliser(const Quat &q) {
    double n = sqrt(q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w);
    return {q.x/n, q.y/n, q.z/n, q.w/n};
}

// Avance la pose de dt secondes a vitesses constantes
Pose AvancerPose(const Pose &pose, const Vec3D &vLin, const Vec3D &vAngRad, double dt) {
    Vec3D nouvellePosition = pose.position + vLin * dt;
    double angle = Norme(vAngRad) * dt;

    Quat delta;
    if (fabs(angle) < 1e-12) {
        delta = {0,0,0,1};
    } else {
        Vec3D axe = vAngRad * (1.0 / Norme(vAngRad));
        double demi = angle / 2.0;
        double s = sin(demi);
        delta = {axe.x*s, axe.y*s, axe.z*s, cos(demi)};
    }
    Quat nouvelleOrientation = Normaliser(QuatMul(delta, pose.orientation));
    return {nouvellePosition, nouvelleOrientation};
}

// Ecart angulaire (deg) entre deux orientations, chemin court force.
double EcartAngulaireDeg(Quat qa, Quat qb) {
    if (Dot(qa, qb) < 0.0) qb = {-qb.x, -qb.y, -qb.z, -qb.w};
    Quat delta = QuatMul(qb, Conjugue(qa));
    double w = max(-1.0, min(1.0, delta.w));
    return 2.0 * acos(w) * 180.0 / M_PI;
}

// Vraie vitesse angulaire instantanee (autour de Haut = Y), en rad/s.
Vec3D VitesseVraieRad(double t) {
    double wDeg = W0 * exp(-t / TAU);
    return {0.0, wDeg * M_PI / 180.0, 0.0};
}

// Simulation du mouvement réel pas à pas jusqu'a T, petits pas dtSim.
Pose SimulerPasAPas(Pose depart, double T, double dtSim) {
    Pose pose = depart;
    double t = 0.0;
    while (t < T - 1e-12) {
        double pas = min(dtSim, T - t);
        Vec3D w = VitesseVraieRad(t + pas / 2.0); 
        pose = AvancerPose(pose, {0,0,0}, w, pas);
        t += pas;
    }
    return pose;
}

int main() {
    Pose depart{ {0,0,0}, {0,0,0,1} };
    Vec3D vAngExtrapolation{0.0, W0 * M_PI / 180.0, 0.0};

    vector<double> durees = {0.010, 0.020, 0.050, 0.100, 0.200, 0.300, 0.500, 0.750, 1.000};

    cout << fixed << setprecision(4);
    cout << "  dt (ms)   extrapole (deg)   vrai (deg)   erreur (deg)\n";
    for (double T : durees) {
        Pose extrapole = AvancerPose(depart, {0,0,0}, vAngExtrapolation, T);
        Pose vrai = SimulerPasAPas(depart, T, 0.0002); 

        double angleExtrapole = EcartAngulaireDeg(depart.orientation, extrapole.orientation);
        double angleVrai = EcartAngulaireDeg(depart.orientation, vrai.orientation);
        double erreur = EcartAngulaireDeg(extrapole.orientation, vrai.orientation);

        cout << setw(9) << (T * 1000.0) << setw(18) << angleExtrapole
             << setw(13) << angleVrai << setw(15) << erreur << "\n";
    }

    return 0;
}