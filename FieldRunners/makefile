CC = g++ -std=c++11
RSDL_FLAGS = -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: main.o FieldRunners.o Tower.o Gatling.o Missile.o Tesla.o Glue.o Waves.o Enemy.o Runner.o StubbornRunner.o SuperTrooper.o Scrambler.o Background.o rsdl.o
	${CC} main.o FieldRunners.o Tower.o Gatling.o Missile.o Tesla.o Glue.o Waves.o Enemy.o Runner.o StubbornRunner.o SuperTrooper.o Scrambler.o Background.o rsdl.o $(RSDL_FLAGS) -o FieldRunners.out

main.o: main.cpp FieldRunners.hpp
	${CC} -c main.cpp -o main.o

FieldRunners.o: FieldRunners.cpp Tower.hpp Gatling.hpp Missile.hpp Tesla.hpp Glue.hpp Enemy.hpp Runner.hpp StubbornRunner.hpp Scrambler.hpp Background.hpp Waves.hpp src/rsdl.hpp
	${CC} -c FieldRunners.cpp -o FieldRunners.o

Waves.o: Waves.cpp Waves.hpp Enemy.hpp Runner.hpp StubbornRunner.hpp SuperTrooper.hpp Scrambler.hpp Background.hpp src/rsdl.hpp
	${CC} -c Waves.cpp -o Waves.o

Enemy.o: Enemy.cpp Enemy.hpp Waves.hpp Background.hpp src/rsdl.hpp
	${CC} -c Enemy.cpp -o Enemy.o

Runner.o: Runner.cpp Runner.hpp Enemy.hpp Background.hpp src/rsdl.hpp
	${CC} -c Runner.cpp -o Runner.o

Scrambler.o: Scrambler.cpp Scrambler.hpp Enemy.hpp Background.hpp src/rsdl.hpp
		${CC} -c Scrambler.cpp -o Scrambler.o

StubbornRunner.o: StubbornRunner.cpp StubbornRunner.hpp Enemy.hpp Background.hpp src/rsdl.hpp
	${CC} -c StubbornRunner.cpp -o StubbornRunner.o

SuperTrooper.o: SuperTrooper.cpp SuperTrooper.hpp Enemy.hpp Background.hpp src/rsdl.hpp
	${CC} -c SuperTrooper.cpp -o SuperTrooper.o

Tower.o: Tower.cpp Tower.hpp Background.hpp src/rsdl.hpp
	${CC} -c Tower.cpp -o Tower.o

Gatling.o: Gatling.cpp Gatling.hpp Tower.hpp src/rsdl.hpp
	${CC} -c Gatling.cpp -o Gatling.o

Missile.o: Missile.cpp Missile.hpp Tower.hpp src/rsdl.hpp
		${CC} -c Missile.cpp -o Missile.o

Tesla.o: Tesla.cpp Tesla.hpp Tower.hpp src/rsdl.hpp
		${CC} -c Tesla.cpp -o Tesla.o

Glue.o: Glue.cpp Glue.hpp Tower.hpp src/rsdl.hpp
		${CC} -c Glue.cpp -o Glue.o

Background.o: Background.cpp Background.hpp  Enemy.hpp Tower.hpp src/rsdl.hpp
	${CC} -c Background.cpp -o Background.o

rsdl.o: src/rsdl.cpp src/rsdl.hpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o
