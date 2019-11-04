#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//tribute card
/*
    test 1: player2 has no cards
    test 2: player2 has one card in hand (copper)
    test 3: player2 has one card in deck (action card)
    test 4: player2 has a hand of five cards (victory card, action card)
    test 5: player2 has a hand of five cards (copper, copper)
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
    test 1: player2 has no cards
    expect: no change
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = tribute;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
	cardEffect(tribute, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);

/*
    test 2: player2 has one card in hand (copper)
    expect: player1 gain +2 coin; player2 one less card in hand (potentially a full deck because he would shuffle a new hand?)
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = tribute;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.hand[player2][0] = copper;

    memcpy(&preG, &postG, sizeof(struct gameState));
    coinsGained = 2;
	cardEffect(tribute, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);

    //assert(preG.handCount[player2] - 1 == postG.handCount[player2]);

/*
    test 3: player2 has one card in deck (action card)
    expect: player1 gain +2 actions; player2 to have one less card in deck (maybe he will have more from a shuffle?)
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = tribute;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.deck[player2][0] = tribute;
    actionsGained = 2;
    memcpy(&preG, &postG, sizeof(struct gameState));
    
	cardEffect(tribute, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);
    //assert(preG.numActions + actionsGained == postG.numActions);

    //assert(preG.deckCount[player2] - 1 == postG.deckCount[player2]);

/*
    test 4: player2 has a hand of five cards (victory card, action card)
    expect: player1 gains +2 cards and +2 actions; player2 loses two cards from hand
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = tribute;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.hand[player2][0] = minion;
	postG.hand[player2][1] = estate;
	postG.hand[player2][2] = tribute;
	postG.hand[player2][3] = estate;
	postG.hand[player2][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
    actionsGained = 2;
    cardsGained = 2;
	cardEffect(tribute, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);
    //assert(preG.numActions + actionsGained == postG.numActions);

    //assert(preG.handCount[player2] - 2 == postG.handCount[player2]);

/*
    test 5: player2 has a hand of five cards (copper, copper)
    expect: player1 gains +2 coins; player2 loses two cards (?)
*/
    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = tribute;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.hand[player2][0] = copper;
	postG.hand[player2][1] = copper;
	postG.hand[player2][2] = tribute;
	postG.hand[player2][3] = estate;
	postG.hand[player2][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
    coinsGained = 2;
	cardEffect(tribute, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);
    //assert(preG.numActions + actionsGained == postG.numActions);

    //assert(preG.handCount[player2] - 2 == postG.handCount[player2]);

    return 0;
}