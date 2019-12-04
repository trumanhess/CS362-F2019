#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[]) {

	int seed = 1000;
	int numPlayers = 2;
	int k[10] = { adventurer, embargo, village,
	              minion, mine, cutpurse,
	              sea_hag, baron, smithy,
	              council_room };
	struct gameState g;
	int card = tribute;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = -1;
	int bonus = 0;

	initializeGame(numPlayers, k, seed, &g);
	g.whoseTurn = 0;
	g.handCount[1] = 2;
	g.hand[1][0] = copper;
	g.hand[1][1] = estate;
	g.coins = 0;
	g.numActions = 0;
	g.handCount[0] = 0;

	cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus);

	printf("coins: %d\n", g.coins);
	printf("Excepted coins: 2\n");
	printf("numActions: %d\n", g.numActions);
	printf("Excepted numActions: 0\n");
	printf("handCount: %d\n", g.handCount[0]);
	printf("Excepted handCount: 2\n");

	assert(g.coins == 2);
	assert(g.numActions == 0);
	assert(g.handCount[0] == 2);
	printf("Test passed !!!!!!!!!!!!!\n");


return 0;
}
