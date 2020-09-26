CC = g++ -std=c++11

all: utrip.out

utrip.out: main.o Utrip.o Hotel.o Reservation.o Filter.o User.o
	${CC} main.o Utrip.o Hotel.o Reservation.o Filter.o User.o -o utrip.out

main.o: main.cpp Utrip.hpp
	${CC} -c main.cpp

Utrip.o: Utrip.cpp Utrip.hpp Hotel.hpp Filter.hpp User.hpp
	${CC} -c Utrip.cpp

Hotel.o: Hotel.cpp Hotel.hpp Exceptions.hpp
	${CC} -c Hotel.cpp

Reservation.o: Reservation.cpp Reservation.hpp
	${CC} -c Reservation.cpp

Filter.o: Filter.cpp Filter.hpp Hotel.hpp Exceptions.hpp
	${CC} -c Filter.cpp

User.o: User.cpp User.hpp Hotel.hpp Reservation.hpp Exceptions.hpp
	${CC} -c User.cpp
