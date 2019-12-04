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

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

UnitTest-bug5: dominion.o UnitTest-bug5.c
	gcc -o UnitTest-bug5 UnitTest-bug5.c -g dominion.o rngs.o $(CFLAGS)

UnitTest-bug6: dominion.o UnitTest-bug6.c
	gcc -o UnitTest-bug6 UnitTest-bug6.c -g dominion.o rngs.o $(CFLAGS)

UnitTest-bug7: dominion.o UnitTest-bug7.c
	gcc -o UnitTest-bug7 UnitTest-bug7.c -g dominion.o rngs.o $(CFLAGS)


rununit5: UnitTest-bug5
	./UnitTest-bug5 &> unittestresults.out
	gcov -b -f UnitTest-bug5.c >> unittestresults.out
	cat UnitTest-bug5.c.gcov >> unittestresults.out

rununit6: UnitTest-bug6
	./UnitTest-bug6 &> unittestresults.out
	gcov -b -f UnitTest-bug6.c >> unittestresults.out
	cat UnitTest-bug6.c.gcov >> unittestresults.out

rununit7: UnitTest-bug7
	./UnitTest-bug7 &> unittestresults.out
	gcov -b -f UnitTest-bug7.c >> unittestresults.out
	cat UnitTest-bug7.c.gcov >> unittestresults.out

unittestresults: rununit5 rununit6 rununit7









clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
