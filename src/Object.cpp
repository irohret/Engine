
#include <iostream>
#include <vector>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/Vector.h"
#include "../math/Matrix.h"

// used to create a 3D object
class Object{

    public:
    std::vector<float> vertices;

    Object();
    ~Object();

    Matrix4x4* translate;
    Matrix4x4* scale;
    Matrix4x4* rotate_X;
    Matrix4x4* rotate_Y;
    Matrix4x4* rotate_Z;


    void translateObject(float x, float y, float z);
    void scaleObject(double x, double y, double z);

    void rotateXObject(double t);
    void rotateYObject(double t);
    void rotateZObject(double t);
};


Object::Object(){
    translate = new Matrix4x4();
    scale = new Matrix4x4();
    rotate_X = new Matrix4x4();
    rotate_Y = new Matrix4x4();
    rotate_Z = new Matrix4x4();
};

// Destructor
Object::~Object() {
    delete translate;
    delete scale;
    delete rotate_X;
    delete rotate_Y;
    delete rotate_Z;
}

void Object::translateObject(float x, float y, float z){
    (*translate) = MatixTranslation(x, y, z);
}

void Object::scaleObject(double x, double y, double z){
    (*scale) = MatrixScale(x, y, z);
}

void Object::rotateXObject(double t){
    (*rotate_X) = MatrixRotationXaxis(t);
}

void Object::rotateYObject(double t){
    (*rotate_Y) = MatrixRotationYaxis(t);
}

void Object::rotateZObject(double t){
    (*rotate_Z) = MatrixRotationZaxis(t);
}

// int main() {
//     // Example usage
//     Object myObject;

//     // Print the initial translation matrix
//     std::cout << "Initial Translation Matrix:" << std::endl;
//     printMatrix(*(myObject.translate));

//     // Translate the object
//     myObject.translateObject(1.0f, 2.0f, 3.0f);

//     // Print the updated translation matrix
//     std::cout << "Updated Translation Matrix:" << std::endl;
//     printMatrix(*(myObject.translate));

//     return 0;
// }