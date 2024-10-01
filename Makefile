test:
		g++ -c main.cpp Book.cpp User.cpp Journals.cpp PublicationRank.cpp Library.cpp classFunctions.cpp functions.cpp LibraryItem.cpp
		g++ -g main.o Book.o User.o Journals.o PublicationRank.o Library.o classFunctions.o functions.o LibraryItem.o -o Output

all: test

clean:
		rm -f *.o Output
