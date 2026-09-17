#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Vec3D { double x, y, z; };
struct Quat  { double x, y, z, w; };
struct Pose  { Vec3D position; Quat orientation; };
struct Mat4  { double m[4][4]; };

Vec3D operator-(const Vec3D &a) { return {-a.x, -a.y, -a.z}; }

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

// Conjugue du quaternion, position opposee tournee par ce conjugue.
Pose InverserAnalytique(const Pose &p) {
    Quat conj{-p.orientation.x, -p.orientation.y, -p.orientation.z, p.orientation.w};
    Vec3D posInv = Tourner(conj, -p.position);
    return {posInv, conj};
}

// Pose (position + quaternion UNITAIRE suppose) -> matrice homogene 4x4.
Mat4 PoseVersMatrice(const Pose &p) {
    double x = p.orientation.x, y = p.orientation.y, z = p.orientation.z, w = p.orientation.w;
    Mat4 r;
    r.m[0][0] = 1 - 2*(y*y + z*z); r.m[0][1] = 2*(x*y - w*z);     r.m[0][2] = 2*(x*z + w*y);     r.m[0][3] = p.position.x;
    r.m[1][0] = 2*(x*y + w*z);     r.m[1][1] = 1 - 2*(x*x + z*z); r.m[1][2] = 2*(y*z - w*x);     r.m[1][3] = p.position.y;
    r.m[2][0] = 2*(x*z - w*y);     r.m[2][1] = 2*(y*z + w*x);     r.m[2][2] = 1 - 2*(x*x + y*y); r.m[2][3] = p.position.z;
    r.m[3][0] = 0;                 r.m[3][1] = 0;                 r.m[3][2] = 0;                 r.m[3][3] = 1;
    return r;
}

Mat4 Identite4() {
    Mat4 id{};
    for (int i = 0; i < 4; i++) id.m[i][i] = 1.0;
    return id;
}

// Inversion generale par Gauss-Jordan avec pivot partiel.
Mat4 InverserGenerale(const Mat4 &in) {
    const double EPS = 1e-9;
    double a[4][8];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) a[i][j] = in.m[i][j];
        for (int j = 0; j < 4; j++) a[i][4+j] = (i == j) ? 1.0 : 0.0;
    }

    for (int col = 0; col < 4; col++) {
        int pivotRow = col;
        double maxVal = fabs(a[col][col]);
        for (int r = col + 1; r < 4; r++) {
            if (fabs(a[r][col]) > maxVal) { maxVal = fabs(a[r][col]); pivotRow = r; }
        }
        if (maxVal < EPS) {
            return Identite4(); 
        }
        if (pivotRow != col) {
            for (int j = 0; j < 8; j++) swap(a[col][j], a[pivotRow][j]);
        }
        double pivot = a[col][col];
        for (int j = 0; j < 8; j++) a[col][j] /= pivot;
        for (int r = 0; r < 4; r++) {
            if (r == col) continue;
            double facteur = a[r][col];
            for (int j = 0; j < 8; j++) a[r][j] -= facteur * a[col][j];
        }
    }

    Mat4 out;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out.m[i][j] = a[i][4+j];
    return out;
}

void Afficher(const string &nom, const Mat4 &mat) {
    cout << nom << " :\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) cout << setw(10) << mat.m[i][j];
        cout << "\n";
    }
}

double EcartMax(const Mat4 &a, const Mat4 &b) {
    double maxEcart = 0.0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            maxEcart = max(maxEcart, fabs(a.m[i][j] - b.m[i][j]));
    return maxEcart;
}

int main() {
    Pose pose;
    cout << "Entrez la position de la pose " << endl;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;
    cout << "Entrez le quaternion unitaire de la pose " << endl;
    cin >> pose.orientation.x >> pose.orientation.y
        >> pose.orientation.z >> pose.orientation.w;

    cout << fixed << setprecision(4);

    Mat4 matricePose = PoseVersMatrice(pose);
    Mat4 inverseGenerale = InverserGenerale(matricePose);
    Mat4 inverseAnalytique = PoseVersMatrice(InverserAnalytique(pose));

    cout << "\n=== Comparaison sur une pose valide ===\n\n";
    Afficher("Inversion generale (Gauss-Jordan)", inverseGenerale);
    cout << "\n";
    Afficher("Inversion analytique (conjugue + translation opposee)", inverseAnalytique);
    cout << "\nEcart maximum sur les seize coefficients : "
         << EcartMax(inverseGenerale, inverseAnalytique) << "\n";

    // --- Pose degeneree : deux lignes identiques -> matrice singuliere.

    Mat4 poseDegeneree{{
        {1, 0, 0, 5},
        {0, 1, 0, 3},
        {0, 1, 0, 3},   
        {0, 0, 0, 1}
    }};

    cout << "\n=== Pose degeneree passee a l'inversion generale ===\n\n";
    Afficher("Matrice degeneree (rang deficient)", poseDegeneree);
    cout << "\n";
    Afficher("Ce que rend InverserGenerale", InverserGenerale(poseDegeneree));
    cout << "\nAucune erreur, aucun message : la fonction rend l'identite\n"
            "comme si la pose etait neutre, alors que la matrice d'entree\n"
            "ne represente aucune transformation valide.\n";

    return 0;
}