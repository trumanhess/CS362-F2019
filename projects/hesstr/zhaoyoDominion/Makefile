CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults: all unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	gcov -f unittest1.c >> unittestresults.out
	gcov -f unittest2.c >> unittestresults.out
	gcov -f unittest3.c >> unittestresults.out
	gcov -f unittest4.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: all randomtestcard1.c randomtestcard2.c randomtestcard3.c
	gcc -fprofile-arcs -ftest-coverage -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 &> tmpresults.txt
	./randomtestcard2 >> tmpresults.txt
	./randomtestcard3 >> tmpresults.txt
	gcov -f randomtestcard1.c &> randomtestresults.out
	gcov -f randomtestcard2.c >> randomtestresults.out
	gcov -f randomtestcard3.c >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	cat tmpresults.txt >> randomtestresults.out
	rm -f tmpresults.txt

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
