INC_DIR = include

all: exp

exp: mainExp.o Shapes.o Media.o
	g++ -o exp mainExp.o Shapes.o Media.o -lgtest
	
mainExp.o: mainExp.cpp exp.h global.h
	g++ -std=gnu++0x -c mainExp.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp
Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp

clean:
	del *.o *.exe
stat:
	wc *.h *.cpp
