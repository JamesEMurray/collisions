/// <summary>
/// Name: James Murray - C00272116
/// Date: 09/11/23
/// Programme Purpose: Make a default collider for different collision types
/// Known Bugs/Errors:
/// 1) ray_AABB is incomplete, can't figure out how to structure if statement in code to check for collisions having occurred. Layout of function in place.
/// 2) ray_Capsule is dependant on an Axis-Aligned Rectangle for it's centre as it currently stands. [Error] (Proposed Fix: Duplicate Process from ray_AABB but modify code to be more flexible - Use ray_Circle for inspiration[Specifically code for sensing where Ray is in releation to Rectangle edges])
/// </summary>

#include <iostream>

//structs
struct Circle {
    float radius;
    float x; float y;
};

struct Rectangle {
    float height; float width;
    float x; float y; //top left corner
};

struct Capsule {
    Circle circle1;
    Rectangle rectangle;
    Circle circle2;
};

//Axis-Aligned Bounding Box: Rectangle for calculations that don't account for rotations
struct AABB {
    Rectangle rectangle;
};

struct Ray {
    float x_StartPoint; float y_StartPoint;
    float x_EndPoint; float y_EndPoint;
};

struct Point {
    float x; float y;
};

//Function Initialisers:
void c2Circle_Circle(Circle circle1, Circle circle2); //Circle to Circle Collisions
void rectangle_Circle(Rectangle rectangle, Circle circle); //Rectangle to Circle Collisions
void c2Capsule_Circle(Capsule capsule, Circle circle); //Capsule to Circle Collisions
void rectangle_Rectangle(Rectangle rectangle1, Rectangle rectangle2); //Rectangle to Rectangle Collisions
void c2AABB_AABB_Circle(AABB aabb1, AABB aabb2, Circle circle); //Axis-Aligned Bounding Box to Axis-Aligned Bounding Box to Circle Collisions
void ray_Circle(Ray ray, Circle circle); //Ray to Circle Collisions
struct Point getPointOfIntersection(Ray ray1, Ray ray2); //Ray to Ray Intersection Points(Collisions)
void ray_AABB(Ray ray, AABB aabb); //Ray to AABB Collisions
void ray_Capsule(Ray ray, Capsule capsule); //Ray to Capsule Collisions
void AABB_Capsule(AABB aabb, Capsule capsule); //AABB to Capsule Collisions
void c2Ray_Circle_AABB_Capsule(Ray ray, Circle circle, AABB aabb, Capsule capsule); //Ray to Circle to Axis-Aligned Bounding Boxes to Capsule Collisions

//For Testing Build & Compile:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//int main()
//{
//    std::cout << "Hello World!\n";
//
//    return 0;
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// <summary>
/// Types of Collisions To Emulate:
/// c2Circle to Circle
/// c2Capsule Circle, AABB
/// c2AABB, AABB, Circle
/// c2Ray, Circle, AABB and Capsule
/// </summary>

//Circle to Circle Collisions
void c2Circle_Circle(Circle circle1, Circle circle2) {
    bool collide = false;
    float sumOfRadii;
    float distanceBetween;

    // If the distance is less than or equal to the sum of the radii of the two circles, then the circles are colliding.
    sumOfRadii = circle1.radius + circle2.radius;
    //Distance Between: d = √((x_2 - x_1)² + (y_2 - y_1)²)
    distanceBetween = sqrt((pow(circle2.x - circle1.x, 2) + pow(circle2.y - circle1.y, 2)));

    if (distanceBetween <= sumOfRadii)
    {
        collide = true;
    }
    
    if (collide == true)
    {
    std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "circle to circle collision check complete\n";
#endif
}

//Rectangle to Circle Collisions
void rectangle_Circle(Rectangle rectangle, Circle circle) {
    bool collide = false;
    float testX = circle.x;
    float testY = circle.y;

    //Check where the "Circle circle" is in relation to the rectangle
    if (circle.x < rectangle.x)
    {
        testX = rectangle.x; // left edge
    }
    else if (circle.x > rectangle.x + rectangle.width)
    {
        testX = rectangle.x + rectangle.width; // right edge
    }
    if (circle.y < rectangle.y)
    {
        testY = rectangle.y; // top edge
    }
    else if (circle.y > rectangle.y + rectangle.height)
    {
        testY = rectangle.y + rectangle.height; // bottom edge
    }

    float distX = circle.x - testX;
    float distY = circle.y - testY;
    float distance = sqrt((distX * distX) + (distY * distY)); //Pythagorous's Theorem | Distance Between Formula

    if (distance <= circle.radius) {
        collide = true;
    }

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "rectangle to circle collision check complete\n";
#endif
}

//Capsule to Circle Collisions
void c2Capsule_Circle(Capsule capsule, Circle circle) {
    bool collide = false;

    c2Circle_Circle(capsule.circle1, circle);
    c2Circle_Circle(capsule.circle2, circle);
    rectangle_Circle(capsule.rectangle, circle);

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "capsule to circle collision check complete\n";
#endif
}

//Axis-Aligned Bounding Box Collisions
void rectangle_Rectangle(Rectangle rectangle1, Rectangle rectangle2) {
    bool collide = false;

    //rect1 Vertices/Corners
    float rect1TopLeftCorner_x = rectangle1.x; float rect1TopLeftCorner_y = rectangle1.y;
    float rect1TopRightCorner_x = rectangle1.x + rectangle1.width; float rect1TopRightCorner_y = rectangle1.y;
    float rect1BottomLeftCorner_x = rectangle1.x; float rect1BottomLeftCorner_y = rectangle1.y + rectangle1.height;
    float rect1BottomRightCorner_x = rectangle1.x + rectangle1.width; float rect1BottomRightCorner_y = rectangle1.y + rectangle1.height;

    //rect2 Vertices/Corners
    float rect2TopLeftCorner_x = rectangle2.x; float rect2TopLeftCorner_y = rectangle2.y;
    float rect2TopRightCorner_x = rectangle2.x + rectangle2.width; float rect2TopRightCorner_y = rectangle2.y;
    float rect2BottomLeftCorner_x = rectangle2.x; float rect2BottomLeftCorner_y = rectangle2.y + rectangle2.height;
    float rect2BottomRightCorner_x = rectangle2.x + rectangle2.width; float rect2BottomRightCorner_y = rectangle2.y + rectangle2.height;

    //check if top left corner of rect2 is within confines of rect1
    if (rect2TopLeftCorner_x > rect1TopLeftCorner_x && rect2TopLeftCorner_x < rect1TopRightCorner_x && rect2TopLeftCorner_y > rect1TopLeftCorner_y && rect2TopLeftCorner_y < rect1BottomRightCorner_y)
    {
        collide = true;
    }
    //check if top left corner of rect1 is within confines of rect2
    else if (rect1TopLeftCorner_x > rect2TopLeftCorner_x && rect1TopLeftCorner_x < rect2TopRightCorner_x && rect1TopLeftCorner_y > rect2TopLeftCorner_y && rect1TopLeftCorner_y < rect2BottomRightCorner_y)
    {
        collide = true;
    }

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "rectangle to rectangle collision check complete\n";
#endif
}

//Axis-Aligned Bounding Box to Axis-Aligned Bounding Box to Circle Collisions
void c2AABB_AABB_Circle(AABB aabb1, AABB aabb2, Circle circle) {
    bool collide = false;

    rectangle_Rectangle(aabb1.rectangle, aabb2.rectangle);
    rectangle_Circle(aabb1.rectangle, circle);
    rectangle_Circle(aabb2.rectangle, circle);
    
    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "AABB to AABB to circle collision check complete\n";
#endif
}

//Ray to Circle Collisions
void ray_Circle(Ray ray, Circle circle) {
    bool collide = false;

    // get length of the line/ray
    float distX = ray.x_StartPoint - ray.x_EndPoint;
    float distY = ray.y_StartPoint - ray.y_EndPoint;
    float length = sqrt((distX * distX) + (distY * distY));

    // get dot product of the line/ray and circle
    float dot = (((circle.x - ray.x_StartPoint) * (ray.x_EndPoint - ray.x_StartPoint)) + ((circle.y - ray.y_StartPoint) * (ray.y_EndPoint - ray.y_StartPoint))) / pow(length, 2);

    // find the closest point on the line/ray
    float closestX = ray.x_StartPoint + (dot * (ray.x_EndPoint - ray.x_StartPoint));
    float closestY = ray.y_StartPoint + (dot * (ray.y_EndPoint - ray.y_StartPoint));

    // get distance to closest point
    distX = closestX - circle.x;
    distY = closestY - circle.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= circle.radius) {
        collide = true;
    }

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "ray to circle collision check complete\n";
#endif
}

//Ray to Ray Intersection Point(Collisions)
struct Point getPointOfIntersection(Ray ray1, Ray ray2) {
    // Need to Get the equation of the line [y = mx + c] for each ray, to then plug into line intersection formula
    float ray1_slope = (ray1.y_EndPoint - ray1.y_StartPoint) / (ray1.x_EndPoint - ray1.x_StartPoint);
    float ray1_c = ray1.y_StartPoint / (ray1_slope * ray1.x_StartPoint);

    float ray2_slope = (ray2.y_EndPoint - ray2.y_StartPoint) / (ray2.x_EndPoint - ray2.x_StartPoint);
    float ray2_c = ray2.y_StartPoint / (ray2_slope * ray2.x_StartPoint);

    // Formula for finding point of intersection between lines: (x, y) = ((b1c2-b2c1)/(a1b2-a2b1), (c1a2-c2a1)/(a1b2-a2b1))
    Point pointOfIntersection;
    pointOfIntersection.x = (ray2_c - ray1_c) / (ray1_slope - ray2_slope); //(b1*c2-b2*c1)/(a1*b2-a2*b1) | b's must equal 1 for formulas to remain consistent
    pointOfIntersection.y = ((ray1_c * ray2_slope) - (ray2_c * ray1_slope) / (ray1_slope - ray2_slope)); //(c1*a2-c2*a1)/(a1*b2-a2*b1) | b's must equal 1 for formulas to remain consistent

    return pointOfIntersection;
}

//Ray to AABB Collisions
void ray_AABB(Ray ray, AABB aabb) {
    bool collide = false;

    // Break a Rectangle into 4 seperate rays, where each ray represents a side
    // Note: 2 copies for widthRay & 2 copies for heightRay
    Ray rectWidthRay1;
    rectWidthRay1.x_StartPoint = aabb.rectangle.x; rectWidthRay1.y_StartPoint = aabb.rectangle.y; //Start Point
    rectWidthRay1.x_EndPoint = aabb.rectangle.x + aabb.rectangle.width; rectWidthRay1.y_EndPoint = aabb.rectangle.y; //End Point

    Ray rectWidthRay2;
    rectWidthRay2.x_StartPoint = aabb.rectangle.x; rectWidthRay2.y_StartPoint = aabb.rectangle.y + aabb.rectangle.height; //Start Point
    rectWidthRay2.x_EndPoint = aabb.rectangle.x + aabb.rectangle.width; rectWidthRay2.y_EndPoint = aabb.rectangle.y + aabb.rectangle.height; //End Point
    
    Ray rectHeightRay1;
    rectHeightRay1.x_StartPoint = aabb.rectangle.x; rectHeightRay1.y_StartPoint = aabb.rectangle.y; //Start Point
    rectHeightRay1.x_EndPoint = aabb.rectangle.x; rectHeightRay1.y_EndPoint = aabb.rectangle.y + aabb.rectangle.height; //End Point

    Ray rectHeightRay2;
    rectHeightRay2.x_StartPoint = aabb.rectangle.x + aabb.rectangle.width; rectHeightRay2.y_StartPoint = aabb.rectangle.y; //Start Point
    rectHeightRay2.x_EndPoint = aabb.rectangle.x + aabb.rectangle.width; rectHeightRay2.y_EndPoint = aabb.rectangle.y + aabb.rectangle.height; //End Point

    Point intersection1 = getPointOfIntersection(ray, rectWidthRay1);
    //if (intersection1 == point on the line or ray) { collide = true; }
    Point intersection2 = getPointOfIntersection(ray, rectWidthRay2);
    //if (intersection2 == point on the line or ray) { collide = true; }
    Point intersection3 = getPointOfIntersection(ray, rectHeightRay1);
    //if (intersection3 == point on the line or ray) { collide = true; }
    Point intersection4 = getPointOfIntersection(ray, rectHeightRay2);
    //if (intersection4 == point on the line or ray) { collide = true; }

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "ray to AABB collision check complete\n";
#endif
}

//Ray to Capsule Collisions
void ray_Capsule(Ray ray, Capsule capsule) {
    bool collide = false;
    AABB capRect;
    capRect.rectangle = capsule.rectangle;

    ray_Circle(ray, capsule.circle1);
    ray_AABB(ray, capRect); //Ray - Rectangle | Needs Fixing to not be Axis-Aligned Specific
    ray_Circle(ray, capsule.circle2);

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "ray to capsule collision check complete\n";
#endif
}

//AABB to Capsule Collisions
void AABB_Capsule(AABB aabb, Capsule capsule) {
    bool collide = false;

    rectangle_Circle(aabb.rectangle, capsule.circle1);
    rectangle_Rectangle(aabb.rectangle, capsule.rectangle);
    rectangle_Circle(aabb.rectangle, capsule.circle2);

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "AABB to capsule collision check complete\n";
#endif
}

//Ray to Circle to Axis-Aligned Bounding Boxes to Capsule Collisions
void c2Ray_Circle_AABB_Capsule(Ray ray, Circle circle, AABB aabb, Capsule capsule) {
    bool collide = false;

    ray_Circle(ray, circle);
    ray_AABB(ray, aabb);
    ray_Capsule(ray, capsule);
    rectangle_Circle(aabb.rectangle, circle);
    c2Capsule_Circle(capsule, circle);
    AABB_Capsule(aabb, capsule);

    if (collide == true)
    {
        std::cout << "Collision\n";
    }
#ifdef DEBUG
    std::cout << "ray to circle to AABB to capsule collision check complete\n";
#endif
}