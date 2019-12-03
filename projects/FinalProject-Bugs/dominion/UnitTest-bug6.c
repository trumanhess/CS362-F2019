#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[]) {

	int seed = 1000;
	int numPlayers = 1;
	int k[10] = { adventurer, embargo, village,
	              minion, mine, cutpurse,
	              sea_hag, baron, smithy,
	              council_room };
	struct gameState g;
	int card = feast;
	int choice1 = gold;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = -1;
	int bonus = 0;

	initializeGame(numPlayers, k, seed, &g);
	g.hand[0][0] = copper;
	g.handCount[0] = 1;

	cardEffect(card, choice1, choice2, choice3, state, handPos, &bonus);

	assert(g.handCount[0] == 1);



return 0;
}