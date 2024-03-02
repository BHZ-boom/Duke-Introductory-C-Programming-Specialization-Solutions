#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
    if(index+1>fc->n_decks){
        fc->decks = (deck_t*)realloc(fc->decks, sizeof(deck_t) * (index+1));
        for(int i=fc->n_decks; i<=index; i++){
            fc->decks[i].n_cards = 0;
            fc->decks[i].cards = NULL;
        }
        fc->n_decks = index + 1;
    }
    int num = fc->decks[index].n_cards;
    fc->decks[index].cards = (card_t**)realloc(fc->decks[index].cards, sizeof(card_t*) * (num+1));
    fc->decks[index].cards[num] = ptr;
    fc->decks[index].n_cards++;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  assert(fc->n_decks <= deck->n_cards);
  for(int i=0; i<fc->n_decks; i++){
    for(int j=0; j<fc->decks[i].n_cards; j++){
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
    }
  }
}