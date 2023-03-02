#include "Cube.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

Cube::Cube(std::vector<GLfloat> colors, GLfloat side) : side(side) {
    this->colors = colors;
    this->buildShape();
}

void Cube::buildShape() {
    this->vertices = {
        -this->side, -this->side, this->side,
        this->side, -this->side, this->side,
        -this->side, this->side, this->side,
        this->side, this->side, this->side,
        -this->side, -this->side, -this->side,
        this->side, -this->side, -this->side,
        -this->side, this->side, -this->side,
        this->side, this->side, -this->side
    };

    this->indices = {
        0, 1, 2, 2, 1, 3,
        5, 4, 7, 7, 4, 6,
        4, 0, 6, 6, 0, 2,
        1, 5, 3, 3, 5, 7,
        2, 3, 6, 6, 3, 7,
        4, 5, 0, 0, 5, 1
    };

    while (this->colors.size() < this->vertices.size()){
        this->colors.push_back(this->colors[0]);
    }
}