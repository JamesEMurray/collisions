/// <summary>
/// Name: James Murray - C00272116
/// Date: 09/11/23
/// Programme Purpose: Make a default collider for different collision types
/// Known Bugs/Errors: None
/// </summary>

#include <iostream>

//Function Initialisers:
void c2Circle_Circle(); //Circle to Circle Collisions
void c2Capsule_Circle(); //Capsule to Circle Collisions
void c2AABB_AABB_Circle(); //Axis-Aligned Bounding Box to Axis-Aligned Bounding Box to Circle Collisions
void c2Ray_Circle_AABB_Capsule(); //Ray to Circle to Axis-Aligned Bounding Boxes to Capsule Collisions

int main()
{
    std::cout << "Hello World!\n";

    return 0;
}

/// <summary>
/// Types of Collisions To Emulate:
/// c2Circle to Circle
/// c2Capsule Circle, AABB
/// c2AABB, AABB, Circle
/// c2Ray, Circle, AABB and Capsule
/// </summary>

//Circle to Circle Collisions
void c2Circle_Circle() {
    bool collide = false;
    
}

//Capsule to Circle Collisions
void c2Capsule_Circle() {
    bool collide = false;

}

//Axis-Aligned Bounding Box to Axis-Aligned Bounding Box to Circle Collisions
void c2AABB_AABB_Circle() {
    bool collide = false;
}

//Ray to Circle to Axis-Aligned Bounding Boxes to Capsule Collisions
void c2Ray_Circle_AABB_Capsule() {
    bool collide = false;
}