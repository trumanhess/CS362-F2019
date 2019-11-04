#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
    check player has +1 action in all of these
    test 1: first option, gain +2 coins
    test 2: second option, have 5 cards and try to gain a new set, check new set of cards (?)
            player 2 will have 4 cards and should not gain a new set
    test 3: second option, have 3 cards and check new set of cards (?)
            player 2 will have 5 cards and should gain a new set
    more tests?
*/

int main()
{
    int cardsGained = 0;
    int cardsDiscarded = 0;
    int coinsGained = 0;
    int shuffledCards = 0;

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
    test 1: first option, gain +2 coins
    expect to gain +2 coins
*/
    coinsGained = 2;

    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = duchy;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.hand[player2][0] = minion;
	postG.hand[player2][1] = copper;
	postG.hand[player2][2] = duchy;
	postG.hand[player2][3] = estate;
	postG.hand[player2][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
    choice1 = 1; //choose to gain +2 coins
	cardEffect(minion, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained - cardsDiscarded == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);

    //assert(preG.handCount[player2] + 0 - 0 == postG.handCount[player2]);
    //assert(preG.deckCount[player2] - 0 == postG.deckCount[player2]);

/*
    test 2: second option, have 5 cards and check new set of cards (?)
    player 2 will have 4 cards and should not gain a new set
    expect for player 1 to have a new hand and player 2 to keep hand
*/
    cardsGained = 4;
    cardsDiscarded = 5;
    coinsGained = 0;

    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = duchy;
	postG.hand[player1][3] = estate;
	postG.hand[player1][4] = mine;

    postG.hand[player2][0] = minion;
	postG.hand[player2][1] = copper;
	postG.hand[player2][2] = duchy;
	postG.hand[player2][3] = estate;

    memcpy(&preG, &postG, sizeof(struct gameState));
    choice1 = 1; //choose to gain +2 coins
	cardEffect(minion, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);

    //assert(preG.handCount[player2] + 0 - 0 == postG.handCount[player2]);
    //assert(preG.deckCount[player2] - 0 == postG.deckCount[player2]);

    //need to check how discard pile was affected?

/*
    test 3: second option, have 3 cards and check new set of cards (?)
    player 2 will have 5 cards and should gain a new set
    expect player one to gain a new hand and player 2 to gain a new hand
*/
    cardsGained = 4;
    cardsDiscarded = 3;
    coinsGained = 0;

    postG.hand[player1][0] = minion;
	postG.hand[player1][1] = copper;
	postG.hand[player1][2] = duchy;

    postG.hand[player2][0] = minion;
	postG.hand[player2][1] = copper;
	postG.hand[player2][2] = duchy;
	postG.hand[player2][3] = estate;
    postG.hand[player2][4] = mine;

    memcpy(&preG, &postG, sizeof(struct gameState));
    choice1 = 1; //choose to gain +2 coins
	cardEffect(minion, choice1, choice2, choice3, &postG, handpos, &bonus);

    //assert(preG.handCount[player1] + cardsGained == postG.handCount[player1]);
    //assert(preG.deckCount[player1] - cardsGained == postG.deckCount[player1]);
    //assert(preG.coins + coinsGained == postG.coins);

    //assert(preG.handCount[player2] + 4 == postG.handCount[player2]);
    //assert(preG.deckCount[player2] - 4 == postG.deckCount[player2]);

    //check discard piles for change

    return 0;
}