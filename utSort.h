#ifndef EXP_H
#define EXP_H

#define sortByPerimeterDebug 0
#define sortByAreaDebug 0
#define sortByCompactnessDebug 0

#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
using namespace std;

Sort sortFunctions;

#if !sortByPerimeterDebug
TEST (Sort, sortByIncreasingPerimeter) {
    vertex triV0={0,0};
    vertex triV1={0,3};
    vertex triV2={4,0};

    Triangle tri0(triV0,triV1,triV2);

    Rectangle rec0(0,0,4,2);

    Circle cir0(0,0,1);
    Circle cir1(0,0,3);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&rec0);
    Shapes.push_back (&tri0);
    Shapes.push_back (&cir1);
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

    vertex triV0={0,0};
    vertex triV1={0,3};
    vertex triV2={4,0};

    Triangle tri0(triV0,triV1,triV2);

    Rectangle rec0(0,0,4,2);

    Circle cir0(0,0,1);
    Circle cir1(0,0,3);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&rec0);
    Shapes.push_back (&tri0);
    Shapes.push_back (&cir1);
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

#if !sortByAreaDebug
TEST (Sort, sortByIncreasingArea) {
     vertex triV0={0,0};
    vertex triV1={0,3};
    vertex triV2={4,0};

    Triangle tri0(triV0,triV1,triV2);

    Rectangle rec0(0,0,4,2);

    Circle cir0(0,0,1);
    Circle cir1(0,0,3);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&rec0);
    Shapes.push_back (&tri0);
    Shapes.push_back (&cir1);
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
    vertex triV0={0,0};
    vertex triV1={0,3};
    vertex triV2={4,0};

    Triangle tri0(triV0,triV1,triV2);

    Rectangle rec0(0,0,4,2);

    Circle cir0(0,0,1);
    Circle cir1(0,0,3);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&rec0);
    Shapes.push_back (&tri0);
    Shapes.push_back (&cir1);
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

#if !sortByCompactnessDebug
TEST (Sort, sortByIncreasingCompactness) {
    vertex triV0={0,0};
    vertex triV1={0,3};
    vertex triV2={4,0};

    Triangle tri0(triV0,triV1,triV2);

    Rectangle rec0(0,0,4,2);

    Circle cir0(0,0,1);
    Circle cir1(0,0,3);

    std::list<Shape * > Shapes ;
    Shapes.push_back (&rec0);
    Shapes.push_back (&tri0);
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);
    sortFunctions.sortByIncreasingCompactness(&Shapes);

    std::list<Shape *>::iterator current;
    std::list<Shape *>::iterator last=Shapes.begin();
    for(current=Shapes.begin();current!=Shapes.end();current++){
        EXPECT_TRUE((*current)->area()/(*current)->perimeter()>=(*last)->area()/(*last)->perimeter());
        last=current;
    }
}
#endif // sortByCompactness

#endif
