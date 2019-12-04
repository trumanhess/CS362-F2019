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

unittestresults: all unittestbug9.c unittestbug10.c unittestbug11.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -o unittestbug9 -g unittestbug9.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittestbug10 -g unittestbug10.c dominion.o rngs.o $(CFLAGS)
	gcc -fprofile-arcs -ftest-coverage -o unittestbug11 -g unittestbug11.c dominion.o rngs.o $(CFLAGS)

	./unittestbug9 >> unittestresults.out
	./unittestbug10 >> unittestresults.out
	./unittestbug11 >> unittestresults.out

	gcov -f unittestbug9.c >> unittestresults.out
	gcov -f unittestbug10.c >> unittestresults.out
	gcov -f unittestbug11.c >> unittestresults.out
	
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
	rm -rf *.dSYM *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestbug9 unittestbug10 unittestbug11
