#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  // 如果没有命令行参数，则手动设置默认值
  int num_trials = 10000;

  //read input
  const char* input = argv[1];
  if(input == NULL) return EXIT_FAILURE;
  FILE * fp = fopen(input, "r");
  size_t n_hands = 0;
  future_cards_t fc;
  fc.n_decks = 0;
  char line[50];
  fc.decks = NULL;
  deck_t ** hands = NULL;
  while(fgets(line,sizeof(line),fp) != NULL){
    n_hands+=1;
    hands = (deck_t**)realloc(hands, sizeof(deck_t*) * n_hands);
    hands[n_hands - 1] = hand_from_string(line, &fc);
    assert(hands[n_hands - 1]->n_cards >=5 && "至少有5张牌");
  }






 // deck_t ** hands = read_input(fp, &n_hands, &fc);

  //找出未知卡牌的可能选择
  deck_t* to_be_chosen = build_remaining_deck(hands, n_hands);

  //记录各手牌赢的次数
  int win[n_hands + 1];
  for(int i=0; i<=n_hands; i++){
    win[i] = 0;
  }

  //Monte Carlo试验
  if(argc == 3){
    const char* num = argv[2];
    num_trials = atoi(num); 
  }
  //trial times
  for(int i=0; i<num_trials; i++){
    shuffle(to_be_chosen);
    future_cards_from_deck(to_be_chosen, &fc);
    print_hand(hands[0]);
    print_hand(hands[1]);

    int max_index = 0;
    int num_draw = 0; //平局数
    for(int j=1; j<n_hands; j++){
      int output = compare_hands(hands[max_index], hands[j]);
      if(output < 0){
        max_index = j;
      }
    }
    for(int k=0; k<n_hands; k++){
      int output = compare_hands(hands[max_index], hands[k]);
      if(output == 0){
        num_draw++;
      }
    }
    if(num_draw>=2){
      win[n_hands]++;
    }
    else{
      win[max_index]++;
    }
  }

  //打印结果
  for(size_t i=0; i<n_hands; i++){
    float ratio = (float)win[i]/(float)num_trials * 100;
    printf("Hand %zu won %d / %d times (%.2f%%)\n", i, win[i], num_trials, ratio);
  }
  printf("ties %d\n", win[n_hands]);

  //释放内存
  free_deck(to_be_chosen);
  for(int i=0; i<n_hands; i++){
    free_deck(hands[i]);
  }
  free(hands);
  for(int i=0; i<fc.n_decks; i++){
    free(fc.decks[i].cards);
  }
  free(fc.decks);
  //关闭文件
  fclose(fp);

  return EXIT_SUCCESS;
}

void print_hand(deck_t* hand){
  
}