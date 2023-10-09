#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
   assert(c.value>=2&&c.value<=14);
   assert(c.suit>=0&&c.suit<=3);
}

const char * ranking_to_string(hand_ranking_t r) {
   switch(r){
      
   case STRAIGHT_FLUSH:
      return "STRAIGHT_FLUSH";
      break;
   case FOUR_OF_A_KIND:
      return "FOUR_OF_A_KIND";
      break;
   case FULL_HOUSE:
      return "FULL_HOUSE";
      break;
   case FLUSH:
      return "FLUSH";
      break;
   case STRAIGHT:
      return "STRAIGHT";
      break;
   case THREE_OF_A_KIND:
      return "THREE_OF_A_KIND";
      break;
   case TWO_PAIR:
      return "TWO_PAIR";
      break;
   case PAIR:
      return "PAIR";
      break;
   case NOTHING:
      return "NOTHING";
      break;
   default :
      return "";
      break;
   }
}


char value_letter(card_t c) {
   switch(c.value){
      case 2:
      return '0'+2;
      break;
      case 3:
      return '0'+3;
      break;
      case 4:
      return '0'+4;
      break;
      case 5:
      return '0'+5;
      break;
      case 6:
      return '0'+6;
      break;
      case 7:
      return '0'+7;
      break;
      case 8:
      return '0'+8;
      break;
      case 9:
      return '0'+9;
      break;
      case 10:
      return '0';
      break;
      case 11:
      return 'J';
      break;
      case 12:
      return 'Q';
      break;
      case 13:
      return 'K';
      break;
      case 14:
      return 'A';
      break;
      default:
      return ' ';
      break;
   }
}

char suit_letter(card_t c) {
   switch(c.suit){
      case 0:
      return 's';
      break; 
      case 1:
      return 'h';
      break;
      case 2:
      return 'd';
      break;
      case 3:
      return 'c';
      break;
      default:
      return ' ';
      break;
   } 
}
void print_card(card_t c) {
   printf("%c%c",value_letter(c),suit_letter(c));
}
card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
   switch(value_let){
      case '0'+2 :
      temp.value= 2;
      break;
      case '0'+3 :
      temp.value= 3;
      break;
      case '0'+4 :
      temp.value= 4;
      break;
      case '0'+5 :
      temp.value= 5;
      break;
      case '0'+6 :
      temp.value= 6;
      break;
      case '0'+7 :
      temp.value= 7;
      break;
      case '0'+8 :
      temp.value= 8;
      break;
      case '0'+9 :
      temp.value= 9;
      break;
      case '0':
      temp.value=  0;
      break;
      case 'J':
      temp.value=  11;
      break;
      case 'Q':
      temp.value=  12;
      break;
      case 'K':
      temp.value=  13;
      break;
      case 'A':
      temp.value=  14;
      break;
      default:
      temp.value= 0;
      break;
   }
   switch(suit_let){
      case 's':
      temp.suit= 0;
      break; 
      case 'h':
      temp.suit= 1 ;
      break;
      case 'd':
      temp.suit= 2 ;
      break;
      case 'c':
      temp.suit= 3 ;
      break;
      default:
      temp.suit= 0;
      break;
   } 
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value=c%13+2;
  temp.suit=c/13-1;
  return temp;  
}  
