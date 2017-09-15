#ifndef EXP_H
#define EXP_H

#define sortByPerimeterDebug 1
#define sortByAreaDebug 1
#define sortByCompactness 0

#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
using namespace std;

Sort sortFunctions;

#if sortByPerimeterDebug
TEST (Sort, sortByIncreasingPerimeter) {

    Circle cir0(0,0,1);
    Circle cir1(0,0,2);
    Circle cir2(0,0,3);
    Circle cir3(0,0,4);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir3);
    Shapes.push_back (&cir2);
    Shapes.push_back (&cir0);
    sortFunctions.sortByIncreasingPerimeter(&Shapes);



}

TEST (Sort, sortByDecreasingPerimeter) {

    Circle cir0(0,0,1);
    Circle cir1(0,0,2);
    Circle cir2(0,0,3);
    Circle cir3(0,0,4);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir3);
    Shapes.push_back (&cir2);
    Shapes.push_back (&cir0);
    sortFunctions.sortByDecreasingPerimeter(&Shapes);

}
#endif // sortByPerimeterDebug

#if sortByAreaDebug
TEST (Sort, sortByIncreasingArea) {
     Circle cir0(0,0,1);
    Circle cir1(0,0,2);
    Circle cir2(0,0,3);
    Circle cir3(0,0,4);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir3);
    Shapes.push_back (&cir2);
    Shapes.push_back (&cir0);
    sortFunctions.sortByIncreasingArea(&Shapes);

}

TEST (Sort, sortByDecreasingArea) {
     Circle cir0(0,0,1);
    Circle cir1(0,0,2);
    Circle cir2(0,0,3);
    Circle cir3(0,0,4);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir3);
    Shapes.push_back (&cir2);
    Shapes.push_back (&cir0);
    sortFunctions.sortByDecreasingArea(&Shapes);

}
#endif // sortByAreaDebug

#if sortByCompactness
TEST (Sort, sortByIncreasingCompactness) {

}
#endif // sortByCompactness

#endif
