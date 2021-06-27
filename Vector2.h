//
// Created by Saul on 6/26/2021.
//

#ifndef LIMPCHIMP_CS_GO_VECTOR2_H
#define LIMPCHIMP_CS_GO_VECTOR2_H

struct Vector2 {
    float x, y;

    Vector2 operator+(Vector2 d) {
        return { x + d.x, y + d.y};
    }
    Vector2 operator-(Vector2 d) {
        return { x - d.x, y - d.y};
    }
    Vector2 operator*(float d) {
        return { x * d, y * d};
    }
};

#endif //LIMPCHIMP_CS_GO_VECTOR2_H
