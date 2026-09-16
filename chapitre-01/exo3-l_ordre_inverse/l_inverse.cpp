#include <iostream>
#include <iomanip>

using namespace std;

struct Vec3D {
    double x, y, z;
};

struct Quat {
    double x, y, z, w; 
};

struct Pose {
    Vec3D position;
    Quat orientation; 
};

Pose pose;
Vec3D point;


Vec3D tourner(const Quat &q, const Vec3D &v) {
    Vec3D qv{q.x, q.y, q.z};
 
    Vec3D t{
        2.0 * (qv.y * v.z - qv.z * v.y),
        2.0 * (qv.z * v.x - qv.x * v.z),
        2.0 * (qv.x * v.y - qv.y * v.x)
    };
 
    Vec3D qCrossT{
        qv.y * t.z - qv.z * t.y,
        qv.z * t.x - qv.x * t.z,
        qv.x * t.y - qv.y * t.x
    };
 
    return Vec3D{
        v.x + q.w * t.x + qCrossT.x,
        v.y + q.w * t.y + qCrossT.y,
        v.z + q.w * t.z + qCrossT.z
    };
}
 
// Application de la pose à un point : Rotation puis translation
Vec3D appliquerPose(const Pose &pose, const Vec3D &point) {
    Vec3D tourne = tourner(pose.orientation, point);
    return Vec3D{
        tourne.x + pose.position.x,
        tourne.y + pose.position.y,
        tourne.z + pose.position.z
    };
}
 
// Application de la pose a un point dans l'ordre inverse : translatio
Vec3D appliquerInverse(const Pose &pose, const Vec3D &point) {
    Vec3D translate{
        point.x + pose.position.x,
        point.y + pose.position.y,
        point.z + pose.position.z
    };
    return tourner(pose.orientation, translate);
}

int main() {
    
    cout << "Entrez les coordonnees de la pose " << endl;
    cin >> pose.position.x >> pose.position.y >> pose.position.z;

    cout << "Entrez les coordonnees du quaternion " << endl;
    cin >> pose.orientation.x >> pose.orientation.y
              >> pose.orientation.z >> pose.orientation.w;

    cout << "Entrez les coordonnees de la position actuelle " << endl;
    cin >> point.x >> point.y >> point.z;

    Vec3D resultat = appliquerPose(pose, point);

    cout << fixed << setprecision(4);
    cout << "Rotation puis Translation : \n" 
         << "X : " 
         << resultat.x << "\n"
         << "Y : " 
         << resultat.y << "\n"
         << "Z :  " 
         << resultat.z << "\n"
         << "\n";

    Vec3D translationDabord = appliquerInverse(pose, point);
 
    cout << fixed << setprecision(4);
    cout << "Translation puis Rotation : \n" 
         << "X : " 
         << translationDabord.x << "\n"
         << "Y : " 
         << " " << translationDabord.y << "\n"
         << "Z :  " 
         << " " << translationDabord.z << "\n"
         << "\n";;

    return 0;
}