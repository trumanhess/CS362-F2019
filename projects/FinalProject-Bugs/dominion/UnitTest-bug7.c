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
	g.hand[1][1] = baron;
	g.coins = 0;
	g.numActions = 0;
	g.handCount[0] = 0;

	cardEffect(card, choice1, choice2, choice3, state, handPos, &bonus);

	assert(g.coins == 2);
	assert(g.numActions == 2);
	assetr(g.handCount[0] == 0);



return 0;
}