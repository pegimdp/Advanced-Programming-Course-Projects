CC = g++ -std=c++11

all: utrip.out

utrip.out: main.o Utrip.o Hotel.o Reservation.o Filter.o User.o Rating.o Weights.o
	${CC} main.o Utrip.o Hotel.o Reservation.o Filter.o User.o Rating.o Weights.o -o utrip.out

main.o: main.cpp Utrip.hpp
	${CC} -c main.cpp

Utrip.o: Utrip.cpp Utrip.hpp Hotel.hpp Filter.hpp User.hpp Macros.hpp Weights.hpp
	${CC} -c Utrip.cpp

Hotel.o: Hotel.cpp Hotel.hpp Exceptions.hpp Rating.hpp Macros.hpp User.hpp Weights.hpp
	${CC} -c Hotel.cpp

Reservation.o: Reservation.cpp Reservation.hpp Macros.hpp
	${CC} -c Reservation.cpp

Filter.o: Filter.cpp Filter.hpp Hotel.hpp Exceptions.hpp Macros.hpp
	${CC} -c Filter.cpp

User.o: User.cpp User.hpp Hotel.hpp Reservation.hpp Exceptions.hpp Macros.hpp Rating.hpp
	${CC} -c User.cpp

Rating.o: Rating.hpp Macros.hpp Exceptions.hpp
	${CC} -c Rating.cpp

Weights.o: Weights.cpp Macros.hpp User.hpp Hotel.hpp
	${CC} -c Weights.cpp
