#include <iostream>
#include <iomanip>
#include <cmath>

#define LONGUEUR_BRAS 0.30      
#define LONGUEUR_AVANT_BRAS 0.25

using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };
struct Pose  { Vec3D position; Quat orientation; };

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

// Application de la pose : rotation puis translation.
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

void AfficherPosition(const string &nom, const Vec3D &p) {
    cout << nom << " : "
         << p.x << "  " << p.y << "  " << p.z << "\n";
}

int main() {
    const Quat IDENTITE{0.0, 0.0, 0.0, 1.0};

    // Poses LOCALES fixes, exprimees dans le repere du parent respectif.
    Pose coudeLocal{ {LONGUEUR_BRAS, 0.0, 0.0}, IDENTITE };
    Pose mainLocal{ {LONGUEUR_AVANT_BRAS, 0.0, 0.0}, IDENTITE };

    cout << fixed << setprecision(4);

    // --- Bras au repos : epaule sans rotation ---
    Pose epauleRepos{ {0.0, 0.0, 0.0}, IDENTITE };
    Pose coudeMondeRepos = ComposerPose(epauleRepos, coudeLocal);
    Pose mainMondeRepos  = ComposerPose(coudeMondeRepos, mainLocal);

    cout << "--- Bras au repos ---\n";
    AfficherPosition("Coude", coudeMondeRepos.position);
    AfficherPosition("Main ", mainMondeRepos.position);
    cout << "\n";

    // --- On fait tourner l'epaule ---
    cout << "Entrez le quaternion de rotation de l'epaule (qx qy qz qw) " << endl;
    Quat rotationEpaule;
    cin >> rotationEpaule.x >> rotationEpaule.y >> rotationEpaule.z >> rotationEpaule.w;

    Pose epauleTournee{ {0.0, 0.0, 0.0}, rotationEpaule };
    Pose coudeMondeTourne = ComposerPose(epauleTournee, coudeLocal);
    Pose mainMondeTournee = ComposerPose(coudeMondeTourne, mainLocal);

    cout << "\n--- Apres rotation de l'epaule ---\n";
    AfficherPosition("Coude", coudeMondeTourne.position);
    AfficherPosition("Main ", mainMondeTournee.position);

    // --- Verification : la main "suit" -> le bras reste rigide.
    double avant1 = Norme(coudeMondeRepos.position);
    double avant2 = Norme(mainMondeRepos.position - coudeMondeRepos.position);
    double apres1 = Norme(coudeMondeTourne.position);
    double apres2 = Norme(mainMondeTournee.position - coudeMondeTourne.position);

    cout << "\n--- Verification (longueurs conservees) ---\n";
    cout << "Epaule-Coude  avant : " << avant1 << "   apres : " << apres1 << "\n";
    cout << "Coude-Main    avant : " << avant2 << "   apres : " << apres2 << "\n";

    return 0;
}