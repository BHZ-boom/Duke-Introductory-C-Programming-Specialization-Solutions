#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "eval.h"
#include "deck.h"
#include "cards.h"
// card_t card_from_letters(char value_let, char suit_let);


void create_deck(deck_t *new_deck[]) {
    //创建deck_t指针的数组
    // deck_t **new_deck = (deck_t**)malloc(72 * sizeof(deck_t*));
    // if (new_deck == NULL) {
    //     // Handle memory allocation failure
    //     return NULL;
    // }
    for(int i=0; i<72; i++){  //测试数
        new_deck[i] = (deck_t*)malloc(sizeof(deck_t));
        if (new_deck[i]== NULL) {
            // Handle memory allocation failure
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(new_deck[j]);
            }
            free(new_deck);

            exit(EXIT_FAILURE);
            //return NULL;
        }
        // Assuming you want to create a deck with some initial size, for example, 7 cards
        new_deck[i]->n_cards = 7;
        new_deck[i]->cards = (card_t **)malloc(new_deck[i]->n_cards * sizeof(card_t *));
        if (new_deck[i]->cards == NULL) {
            // Handle memory allocation failure
            // Free previously allocated memory
            free(new_deck[i]);
            for (int j = 0; j < i; j++) {
                free(new_deck[j]);
            }
            free(new_deck);
            exit(EXIT_FAILURE);
            //return NULL;
        }
        for(int j=0; j<new_deck[i]->n_cards; j++){
            new_deck[i]->cards[j] = (card_t *)malloc(sizeof(card_t));
            // Handle memory allocation failure 略
        }

    }

    // Now, you would need to initialize each card in the deck based on your logic

    //return new_deck;
}

// Function to free the memory allocated for a deck
void free_deck_t(deck_t *new_deck[]) {
        // Free each card
    for (size_t i = 0; i < 72; i++) {
        for (int j = 0; i < new_deck[i]->n_cards; i++){
            free(new_deck[i]->cards[j]);
        }
        
        free(new_deck[i]->cards);
        free(new_deck[i]);
    }
}

int main() {
    FILE *fp = fopen("tests.txt","r");

    //创建deck_t指针的数组
    deck_t *total[72]; 
    create_deck(total);
    int index=0;
    // Use my_deck as needed
    char line[50];
    // for(int i=0; i<72; i++){
    //     total[i]->n_cards = 7;
    // }
    card_t t;
    while(fgets(line,50,fp) != NULL){
        char *p=line;
        int card_num=0;
        while(*p != '\0'){
            if(isdigit(*p) || isupper(*p)){
                t = card_from_letters(*p,*(p+1));
                //total[index]->cards[card_num++] = &t;  //直接取地址，t变了也会跟着变！
                total[index]->cards[card_num]->value = t.value;
                total[index]->cards[card_num]->suit = t.suit;
                card_num++;
            }
            if(card_num==7){
                    index++;
                    card_num=0;
            }
            p++;
        }
    }

     for(int i=0; i<36; i++){
         int output = compare_hands(total[i*2],total[i*2+1]);
     //    hand_eval_t eval1 = evaluate_hand(total[i*2]);
      //   hand_eval_t eval2 = evaluate_hand(total[i*2+1]);
         printf("%d\n",output);
     }
    
    fclose(fp);

    free_deck_t(total);

    return 0;
}

// card_t card_from_letters(char value_let, char suit_let)
// {  

//    card_t temp;
//    switch (value_let)
//    {
//    case '0' + 2:
//       temp.value = 2;
//       break;
//    case '0' + 3:
//       temp.value = 3;
//       break;
//    case '0' + 4:
//       temp.value = 4;
//       break;
//    case '0' + 5:
//       temp.value = 5;
//       break;
//    case '0' + 6:
//       temp.value = 6;
//       break;
//    case '0' + 7:
//       temp.value = 7;
//       break;
//    case '0' + 8:
//       temp.value = 8;
//       break;
//    case '0' + 9:
//       temp.value = 9;
//       break;
//    case '0':
//       temp.value = 10;
//       break;
//    case 'J':
//       temp.value = 11;
//       break;
//    case 'Q':
//       temp.value = 12;
//       break;
//    case 'K':
//       temp.value = 13;
//       break;
//    case 'A':
//       temp.value = 14;
//       break;
//    default:
//       printf("invalid value");
//       exit(EXIT_FAILURE);
//    }
//    switch (suit_let)
//    {
//    case 's':
//       temp.suit = 0;
//       break;
//    case 'h':
//       temp.suit = 1;
//       break;
//    case 'd':
//       temp.suit = 2;
//       break;
//    case 'c':
//       temp.suit = 3;
//       break;
//    default:
//      printf("invalid suit");
//      exit(EXIT_FAILURE); 
//    }
//    return temp;
// }

