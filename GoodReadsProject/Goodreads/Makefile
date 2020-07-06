CC=g++ -std=c++11

all:	Goodreads.out

Goodreads.out: main.o Date.o Author.o Book.o User.o Review.o Goodreads.o compare.o
	${CC} main.o Date.o Author.o Book.o User.o Review.o Goodreads.o compare.o -o Goodreads.out

main.o: main.cpp User.hpp Author.hpp Date.hpp Goodreads.hpp compare.hpp
	${CC} -c main.cpp

Goodreads.o: Goodreads.cpp Date.hpp Author.hpp Book.hpp User.hpp Review.hpp compare.hpp
	${CC} -c Goodreads.cpp

Review.o: Review.cpp Book.hpp User.hpp Date.hpp
	${CC} -c Review.cpp

User.o: User.cpp Date.hpp Author.hpp Book.hpp compare.hpp
	${CC} -c User.cpp

Book.o: Book.cpp Author.hpp
	${CC} -c Book.cpp

Author.o: Author.cpp Date.hpp compare.hpp
	${CC} -c Author.cpp

Date.o: Date.cpp Date.hpp
	${CC} -c Date.cpp

compare.o: compare.cpp compare.hpp
	${CC} -c compare.cpp
