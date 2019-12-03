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

	initializeGame(numPlayers, k, seed, &g);

	g.hand[0][0] = curse;
	g.hand[0][1] = estate;
	g.hand[0][2] = duchy;
	g.hand[0][3] = province;
	g.hand[0][4] = great_hall;
	g.hand[0][5] = gardens;

	g.handCount[0] = 6;

	g.discard[0][0] = curse;
	g.discard[0][1] = estate;
	g.discard[0][2] = duchy;
	g.discard[0][3] = province;
	g.discard[0][4] = great_hall;

	g.discardCount[0] = 5;

	g.deck[0][0] = curse;
	g.deck[0][1] = estate;
	g.deck[0][2] = duchy;
	g.deck[0][3] = province;

	g.deckCount[0] = 4;

	assert(scoreFor(0, &g) == 23);


return 0;
}