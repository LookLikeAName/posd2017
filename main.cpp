#include <gtest/gtest.h>
#include "utSort.h"
#define buildDebug 0
int main( int argc , char **argv )
{
    #if buildDebug
      std::cout<<"hello world\n";
    #else
     testing :: InitGoogleTest( &argc , argv ) ;
     return RUN_ALL_TESTS( ) ;
    #endif // mainDebug

}

