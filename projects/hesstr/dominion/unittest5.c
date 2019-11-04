#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//tribute card
/*
    test 1: reveal card, return 0 copy of it to supply
    test 2: reveal card, return 1 copy of it to supply
    test 3: reveal card, return 2 copies of it to supply
    test 4: reveal card, try to return 3 copies of it to supply
    test 5: reveal card, try to return -1 copies of it to supply
    test 6: reveal the ambassador card that was played and try to return 1 copy of it to supply
*/

int main()
{
    /*
    int numPlayers; //number of players
    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    int embargoTokens[treasure_map+1];
    int outpostPlayed;
    int outpostTurn;
    int whoseTurn;
    int phase;
    int numActions; /* Starts at 1 each turn
    int coins; /* Use as you see fit!
    int numBuys; /* Starts at 1 each turn
    int hand[MAX_PLAYERS][MAX_HAND];
    int handCount[MAX_PLAYERS];
    int deck[MAX_PLAYERS][MAX_DECK];
    int deckCount[MAX_PLAYERS];
    int discard[MAX_PLAYERS][MAX_DECK];
    int discardCount[MAX_PLAYERS];
    int playedCards[MAX_DECK];
    int playedCardCount;
    */
    int cardsGained = 0;
    int cardsDiscarded = 0;
    int coinsGained = 0;
    int shuffledCards = 0;
    int actionsGained = 0;
    int buysGained = 0;



    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, copper, gold, mine, minion,
			sea_hag, baron, smithy, council_room};

//REPLACE ALL //assertS WITH OWN IMPLEMENTATION
    initializeGame(numPlayers, k, seed, &postG);

/*
    test 4:
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = ambassador;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
    choice1 = 4;
    choice2 = 3;
	cardEffect(ambassador, choice1, choice2, choice3, &postG, handpos, &bonus);

    return 0;
}