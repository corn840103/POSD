all: hw7

madRace: mainMadRace.o
ifeq (${OS}, Windows_NT)
	g++ -o madRace mainMadRace.o -lgtest
else
	g++ -o madRace mainMadRace.o -lgtest -lpthread
endif
mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

utAtom: mainAtom.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o utAtom mainAtom.o atom.o -lgtest
else
	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
endif
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o utVariable mainVariable.o atom.o -lgtest
else
	g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
endif
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp

list.o:list.cpp list.h
	g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

utScanner: mainScanner.o atom.o list.o struct.o variable.h utScanner.h utParser.h parser.h
ifeq (${OS}, Windows_NT)
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest
else
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
endif
mainScanner.o: mainScanner.cpp scanner.h
		g++ -std=gnu++0x -c mainScanner.cpp

utIterator: mainIterator.o atom.o list.o struct.o iterator.h
ifeq (${OS}, Windows_NT)
	g++ -o utIterator mainIterator.o atom.o list.o struct.o  -lgtest
else
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread
endif
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

hw7: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest
else
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest -lpthread
endif

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner
stat:
	wc *.h *.cpp
