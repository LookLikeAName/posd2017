all: hw2 #utAtom #utVariable  

hw2: main.o  
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o -lgtest
else
	g++ -o hw2 main.o -lgtest -pthread
endif

main.o: main.cpp atom.h variable.h number.h utTerm.h
	g++ --std=gnu++0x -c main.cpp

utAtom: mainAtom.o
ifeq (${OS}, Windows_NT)
	g++ -o utAtom mainAtom.o -lgtest
else
	g++ -o utAtom mainAtom.o -lgtest -pthread
endif
mainAtom.o: mainAtom.cpp utAtom.h atom.h
	g++ --std=gnu++0x -c mainAtom.cpp

utVariable: mainVariable.o
ifeq (${OS}, Windows_NT)
	g++ -o utVariable mainVariable.o -lgtest
else
	g++ -o utVariable mainVariable.o -lgtest -pthread
endif	
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ --std=gnu++0x -c mainVariable.cpp

#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

#utScannerParser: mainScannerParser.o term.o struct.o var.o list.o
#	g++ -o utScannerParser mainScannerParser.o term.o var.o struct.o list.o -lgtest -lpthread
#mainScannerParser.o: mainScannerParser.cpp utScanner.h utParser.h scanner.h parser.h term.h var.h struct.h list.h global.h node.h
#		g++ -std=c++11 -c mainScannerParser.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o utAtom utVariable hw2
stat:
	wc *.h *.cpp
