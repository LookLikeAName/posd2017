INC_DIR = include

all: exp

exp: mainExp.o Shapes.o Media.o
ifeq (${OS}, Windows_NT)
	g++ -o exp mainExp.o Shapes.o Media.o -lgtest
else
	g++ -o exp mainExp.o Shapes.o Media.o -lgtest -lpthread
endif
	
mainExp.o: mainExp.cpp exp.h
	g++ -std=gnu++0x -c mainExp.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp
Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
