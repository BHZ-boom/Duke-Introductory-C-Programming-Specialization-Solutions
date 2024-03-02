#ifndef EVAL_H
#define EVAL_H
#include "deck.h"
struct hand_eval_tag {
  hand_ranking_t ranking;
  card_t *cards[5];
};
typedef struct hand_eval_tag hand_eval_t;

int card_ptr_comp(const void * vp1, const void * vp2);
hand_eval_t evaluate_hand(deck_t * hand, int * mode) ;
int compare_hands(deck_t * hand1, deck_t * hand2) ;
void free_hand_t(hand_eval_t t);


#endif
