#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "input.h"

deck_t * hand_from_string(char * str, future_cards_t * fc){
  deck_t * hand = (deck_t*)malloc(sizeof(deck_t));
  hand->n_cards = 0;
  hand->cards = NULL;
  char * p = str;
  card_t t;
  while(*p != '\0'){
    if((isdigit(*p) || isupper(*p))){
      t = card_from_letters(*p,*(p+1));
      //total[index]->cards[card_num++] = &t;  //直接取地址，t变了也会跟着变！
      //hand->cards = (card_t**)realloc(hand->cards, sizeof(card_t*) * hand->n_cards);
      add_card_to(hand, t);
      p+=2;
    }
    else if(*p == '?'){
      card_t * ptr = add_empty_card(hand);
      size_t n = *(p+1) - '0';
      add_future_card(fc, n, ptr);
      p+=2;
    }
    p++;
  }
  return hand;
}

// deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
//   char line[50];
//   deck_t ** ans;
//   *n_hands = 0;
//   while(fgets(line,sizeof(line),f) != NULL){
//     ans = (deck_t**)realloc(ans, sizeof(deck_t*) * ++(*n_hands));
//     ans[*n_hands - 1] = hand_from_string(line, fc);
//     assert(ans[*n_hands - 1]->n_cards >=5 && "至少有5张牌");
//   }
//   return ans;
// }