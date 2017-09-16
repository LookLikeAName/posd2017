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

    std::list<Shape *>::iterator current;
    std::list<Shape *>::iterator last=Shapes.begin();
    for(current=Shapes.begin();current!=Shapes.end();current++){
        EXPECT_TRUE((*current)->perimeter()>=(*last)->perimeter());    //By increasing the value of the current object should be bigger then the last one.
        last=current;
    }



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

    std::list<Shape *>::iterator current;
    std::list<Shape *>::iterator last=Shapes.begin();
    for(current=Shapes.begin();current!=Shapes.end();current++){
        EXPECT_TRUE((*current)->perimeter()<=(*last)->perimeter());
        last=current;
    }


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

    std::list<Shape *>::iterator current;
    std::list<Shape *>::iterator last=Shapes.begin();
    for(current=Shapes.begin();current!=Shapes.end();current++){
        EXPECT_TRUE((*current)->area()>=(*last)->area());
        last=current;
    }


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

    std::list<Shape *>::iterator current;
    std::list<Shape *>::iterator last=Shapes.begin();
    for(current=Shapes.begin();current!=Shapes.end();current++){
        EXPECT_TRUE((*current)->area()<=(*last)->area());
        last=current;
    }

}
#endif // sortByAreaDebug

#if sortByCompactness
TEST (Sort, sortByIncreasingCompactness) {

}
#endif // sortByCompactness

#endif
