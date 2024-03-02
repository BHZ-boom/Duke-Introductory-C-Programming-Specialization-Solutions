#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(int i=0; i<hand->n_cards; i++){
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0; i<d->n_cards; i++){
    card_t curr = *(d->cards[i]);
    if(curr.suit==c.suit && curr.value==c.value){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  int j;
  int range=d->n_cards;
  for(int i=0; i<range; i++){
    j=random() % range;
    card_t *temp=d->cards[i];
    d->cards[i]=d->cards[j];
    d->cards[j]=temp;
  }
}

void assert_full_deck(deck_t * d) {
  int num=d->n_cards;
  int count=0;
  for(int i=0; i<52; i++){
    card_t curr=*(d->cards[i]);
    assert_card_valid(curr);
    if(deck_contains(d,card_from_num(i))) 
      count++;
  }
  assert(count == num);
}

void add_card_to(deck_t * deck, card_t c){
  int num = ++deck->n_cards;
  deck->cards = (card_t**)realloc(deck->cards, sizeof(card_t*) * num);
  deck->cards[num-1] = (card_t*)malloc(sizeof(card_t));
  deck->cards[num-1]->value = c.value;
  deck->cards[num-1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
  card_t c;
  c.suit = 0;
  c.value = 0;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t *full = (deck_t *)malloc(sizeof(deck_t));
  full->n_cards = 0;
  full->cards = NULL;

  for(int i=0; i<52; i++){
    card_t temp = card_from_num(i);
    if(!deck_contains(excluded_cards, temp)){
      add_card_to(full, temp);
    }  
  }
  return full;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t *all_to_be_excluded = (deck_t *)malloc(sizeof(deck_t));
  all_to_be_excluded->n_cards = 0;
  all_to_be_excluded->cards = NULL;
  for(int i=0; i<52; i++){
    card_t temp = card_from_num(i);
    int flag = 0;
    for(int j=0; j<n_hands; j++){
      if(deck_contains(hands[j], temp)){
        flag = 1;
      }
    }
    if(flag){
      add_card_to(all_to_be_excluded, temp);
    }
  }
  deck_t *ans = make_deck_exclude(all_to_be_excluded);
  free_deck(all_to_be_excluded);
  return ans;
}

void free_deck(deck_t * deck){
  for(int i=0; i<deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
