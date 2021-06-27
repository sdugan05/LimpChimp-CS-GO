//
// Created by Saul on 6/26/2021.
//

#ifndef LIMPCHIMP_CS_GO_VECTOR3_H
#define LIMPCHIMP_CS_GO_VECTOR3_H


struct Vector3 {
    float x, y, z;

    Vector3 operator+(Vector3 d) {
        return { x + d.x, y + d.y, z + d.z};
    }
    Vector3 operator-(Vector3 d) {
        return { x - d.x, y - d.y, z - d.z};
    }
    Vector3 operator*(float d) {
        return { x * d, y * d, z * d};
    }

    void normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = 360;
        }

        while ( x > 89) {
            x = 89;
        }
        while (x < -89) {
            x = -89;
        }
    }
};

struct Vector4 {
    float x, y, z, w;
};

#endif //LIMPCHIMP_CS_GO_VECTOR3_H
