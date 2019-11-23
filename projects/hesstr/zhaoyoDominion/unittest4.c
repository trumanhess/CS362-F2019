#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "custom_assert.h"
#include "rngs.h"

//tribute card
/*
    test 1: player2 has no cards
    test 2: player2 has one card in deck (copper) CHANGED
    test 3: player2 has one card in discard pile (action card) CHANGED
    test 4: player2 has a deck of five cards (treasure card, action card)
    test 5: player2 has a deck of five cards but duplicate (copper, copper)
*/

int universalTest(struct gameState *pre, struct gameState *post, int discarded, int cardsGained, int buysGained, int coinsGained, int actionsGained, int player)
{
    printf("Number buys:\n");
    ASSERT((pre->numBuys + buysGained) == post->numBuys);
    printf("\texpected = %d, actual = %d\n", pre->numBuys + buysGained, post->numBuys);

    printf("Number Actions:\n");
    ASSERT(post->numActions == pre->numActions + actionsGained);
    printf("\texpected = %d, actual = %d\n", pre->numActions + actionsGained, post->numActions);

    printf("Number coins:\n");
    ASSERT((pre->coins + coinsGained) == post->coins);
    printf("\texpected = %d, actual = %d\n", pre->coins + coinsGained, post->coins);

    printf("Hand count:\n");
    ASSERT(post->handCount[player] == pre->handCount[player] - discarded + cardsGained);
    printf("\texpected = %d, actual = %d\n", pre->handCount[player] - discarded + cardsGained, post->handCount[player]);

    return 0;
}

int main()
{
    int cardsGained = 0;
    int cardsDiscarded = 0;
    int coinsGained = 0;
    int buysGained = 0;
    int actionsGained = 0;

    int tributeRevealedCards[2] = {-1, -1};

    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState preG, postG;
	int k[10] = {adventurer, silver, copper, gold, mine, minion,
			sea_hag, baron, smithy, council_room};

    printf("\n\n---------------------------------Testing Tribute--------------------------\n\n");
    initializeGame(numPlayers, k, seed, &preG);

/*
    test 1: player2 has no cards
    expect: no change
*/
    printf("\n\nTest 1:\n");
    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;
    preG.handCount[player1] = 5;

    preG.handCount[player2] = 0;
    preG.deckCount[player2] = 0;
    preG.discardCount[player2] = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 0;
    cardsGained = 0;
	card_tribute(&postG, player2, tributeRevealedCards, player1);
    //card_tribute(struct gameState *state,int nextPlayer,int *tributeRevealedCards,int currentPlayer)

    ASSERT(preG.numActions + actionsGained == postG.numActions);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

/*
    test 2: player2 has one card in deck (copper)
    expect: player1 gain +2 coin; player2 one less card in hand (potentially a full deck because he would shuffle a new hand?)
*/
    printf("\n\nTest 2:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.deck[player2][0] = copper;
    preG.deckCount[player2] = 1;
    preG.discardCount[player2] = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 0;
	card_tribute(&postG, player2, tributeRevealedCards, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.handCount[player2] - 1 == postG.handCount[player2]);

/*
    test 3: player2 has one card in deck (action card)
    expect: player1 gain +2 actions; player2 to have one less card in deck (maybe he will have more from a shuffle?)
*/
    printf("\n\nTest 3:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.deck[player2][0] = tribute;
    preG.deckCount[player2] = 1;
    preG.discardCount[player2] = 0;

    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 0;
    actionsGained = 2;
    cardsGained = 0;
    memcpy(&postG, &preG, sizeof(struct gameState));
    
	card_tribute(&postG, player2, tributeRevealedCards, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.deckCount[player2] - 1 == postG.deckCount[player2]);

/*
    test 4: player2 has a hand of five cards (victory card, treasure card)
    expect: player1 gains +2 cards and +2 actions; player2 loses two cards from hand
*/
    printf("\n\nTest 4:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = tribute;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;
    preG.handCount[player1] = 5;

    preG.deck[player2][0] = copper;
	preG.deck[player2][1] = estate;
	preG.deck[player2][2] = estate;
	preG.deck[player2][3] = estate;
	preG.deck[player2][4] = copper;

    preG.deckCount[player2] = 5;
    preG.discardCount[player2] = 0;
    preG.handCount[player2] = 0;

    memcpy(&postG, &preG, sizeof(struct gameState));
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 2;
	card_tribute(&postG, player2, tributeRevealedCards, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.handCount[player2] - 2 == postG.handCount[player2]);

/*
    test 5: player2 has a hand of five cards (copper, copper)
    expect: player1 gains +2 coins; player2 loses two cards (?)
*/
    printf("\n\nTest 5:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;

    preG.deck[player2][0] = copper;
	preG.deck[player2][1] = copper;
	preG.deck[player2][2] = tribute;
	preG.deck[player2][3] = estate;
	preG.deck[player2][4] = mine;

    memcpy(&postG, &preG, sizeof(struct gameState));
    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 0;
	card_tribute(&postG, player2, tributeRevealedCards, player1);

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    ASSERT(preG.handCount[player2] - 2 == postG.handCount[player2]);

    /*
    test 6: player2 has two cards in discard (treasure, victory)
    expect: player2 will shuffle discard into deck and player1 will gain stats from the top two cards
*/
    printf("\n\nTest 6:\n");

    preG.hand[player1][0] = minion;
	preG.hand[player1][1] = copper;
	preG.hand[player1][2] = tribute;
	preG.hand[player1][3] = estate;
	preG.hand[player1][4] = mine;
    preG.discard[player1][0] = mine;

    preG.discard[player2][0] = copper;
    preG.discard[player2][1] = estate;
    preG.discard[player2][2] = estate;
    preG.discard[player2][3] = copper;
    preG.discardCount[player2] = 4;
    preG.deckCount[player2] = 0;
    //discardCard(handPos, currentPlayer, state, 0);

    for(int i = 0; i < preG.discardCount[player2]; i++)
    {
        printf("\ndiscard Card: %d\n", preG.discard[player2][i]);
    }

    cardsDiscarded = 0;
    buysGained = 0;
    coinsGained = 2;
    actionsGained = 0;
    cardsGained = 2;
    memcpy(&postG, &preG, sizeof(struct gameState));
    
	card_tribute(&postG, player2, tributeRevealedCards, player1);

    printf("\nDiscard before: %d, Discard after: %d\n", preG.discardCount[player2], postG.discardCount[player2]);
    printf("\nDeck before: %d, Deck after: %d\n", preG.deckCount[player2], postG.deckCount[player2]);

    ASSERT((preG.discardCount[player2] - preG.discardCount[player2]) == postG.discardCount[player2]);
    ASSERT((preG.deckCount[player2] + preG.discardCount[player2] - 2) == postG.deckCount[player2]);

    for(int i = 0; i < postG.discardCount[player2]; i++)
    {
        printf("\ndiscard Card after: %d\n", postG.discard[player2][i]);
    }

    universalTest(&preG, &postG, cardsDiscarded, cardsGained, buysGained, coinsGained, actionsGained, player1);

    //ASSERT(preG.deckCount[player2] - 1 == postG.deckCount[player2]);
    //check player2 deck and discard piles

        printf("\n\n---------------------------------End Testing Tribute--------------------------\n\n");

    return 0;
}