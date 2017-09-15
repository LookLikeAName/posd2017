#ifndef sort_header
#define sort_header
#include <list>
#include "Shapes.h"

#define sortDebug 0

class Sort {

  public :
      static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList)
      {
        std::list<Shape *>::iterator itor=shapeList->begin();

        for(int i=0;i<shapeList->size();i++)
        {
            std::list<Shape *>::iterator temp=shapeList->begin();
            for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {

                if((*itor)->perimeter()<(*temp)->perimeter()){
                    std::swap(*itor,*temp);
                }
                temp=itor;
            }

        }
        #if sortDebug
        for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {
                std::cout<<(*itor)->perimeter()<<" ";
            }
               std::cout<<std::endl;
        #endif // sortDebug
      };

      static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList)
      {

        std::list<Shape *>::iterator itor=shapeList->begin();

        for(int i=0;i<shapeList->size();i++)
        {
            std::list<Shape *>::iterator temp=shapeList->begin();
            for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {

                if((*itor)->perimeter()>(*temp)->perimeter()){
                    std::swap(*itor,*temp);
                }
                temp=itor;
            }

        }
        #if sortDebug
        for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {
                std::cout<<(*itor)->perimeter()<<" ";
            }
               std::cout<<std::endl;
        #endif // sortDebug
      };

      static void sortByIncreasingArea(std::list<Shape *> * shapeList)
      {

        std::list<Shape *>::iterator itor=shapeList->begin();

        for(int i=0;i<shapeList->size();i++)
        {
            std::list<Shape *>::iterator temp=shapeList->begin();
            for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {

                if((*itor)->area()<(*temp)->area()){
                    std::swap(*itor,*temp);
                }
                temp=itor;
            }

        }
        #if sortDebug
        for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {
                std::cout<<(*itor)->area()<<" ";
            }
               std::cout<<std::endl;
        #endif // sortDebug
      };
      static void sortByDecreasingArea(std::list<Shape *> * shapeList)
      {
         std::list<Shape *>::iterator itor=shapeList->begin();

        for(int i=0;i<shapeList->size();i++)
        {
            std::list<Shape *>::iterator temp=shapeList->begin();
            for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {

                if((*itor)->area()>(*temp)->area()){
                    std::swap(*itor,*temp);
                }
                temp=itor;
            }

        }
        #if sortDebug
        for(itor=shapeList->begin();itor!=shapeList->end();itor++)
            {
                std::cout<<(*itor)->area()<<" ";
            }
               std::cout<<std::endl;
        #endif // sortDebug
      };

      static void sortByIncreasingCompactness(std::list<Shape *> * shapeList)
      {

      };

};

#endif
