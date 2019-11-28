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

unittestresults: all unittestbug1.c unittestbug2.c unittestbug3.c unittestbug4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -o unittestbug1 -g unittestbug1.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittestbug2 -g unittestbug2.c dominion.o rngs.o $(CFLAGS)
	#gcc -fprofile-arcs -ftest-coverage -o unittestbug3 -g unittestbug3.c dominion.o rngs.o $(CFLAGS)
	#gcc -fprofile-arcs -ftest-coverage -o unittestbug4 -g unittestbug4.c dominion.o rngs.o $(CFLAGS)

	./unittestbug1 &> unittestresults.out
	./unittestbug2 >> unittestresults.out
	#./unittestbug3 >> unittestresults.out
	#./unittestbug4 >> unittestresults.out

	gcov -f unittestbug1.c >> unittestresults.out
	gcov -f unittestbug2.c >> unittestresults.out
	#gcov -f unittestbug3.c >> unittestresults.out
	#gcov -f unittestbug4.c >> unittestresults.out
	
	gcov -fb dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
