#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int is_ace_low_straight_at(deck_t *hand, size_t index, suit_t fs);

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const *cp1 = (const card_t **)vp1;
  const card_t * const *cp2 = (const card_t **)vp2;
  if ((*cp1)->value != (*cp2)->value) {
    return (*cp2)->value - (*cp1)->value;
  }
  return (*cp2)->suit - (*cp1)->suit;
}

suit_t flush_suit(deck_t * hand) {
  int num=hand->n_cards;
  int s=0,h=0,d=0,c=0;
  for(int i=0; i<num;i++){
    switch(hand->cards[i]->suit){
      case 0:
        s++;
        break;
      case 1:
        h++;
        break;
      case 2:
        d++;
        break;
      case 3:
        c++;
        break;
      default:
        break;
    }
  }
  if(s>=5) return SPADES;
  else if(h>=5) return HEARTS;
  else if(d>=5) return DIAMONDS;
  else if(c>=5) return CLUBS;
  return NUM_SUITS;  
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max=arr[0];
  for(int i=1; i<n; i++){
    if(arr[i]>max) max=arr[i];
  }
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for(int i=0; i<n; i++){
    if(match_counts[i]==n_of_akind) return i;
  }
  exit(EXIT_FAILURE);
}

int find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  int num = hand->n_cards;
  for(int i=0; i<num; i++){
    if(match_counts[i]>=2)
      if(hand->cards[i]->value != hand->cards[match_idx]->value)
        return i;
  }
  return -1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int remaining_cards = hand->n_cards-index;
  int num = hand->n_cards;
  if(fs==NUM_SUITS){
    if(remaining_cards<5) return 0;
    else{
      if(is_ace_low_straight_at(hand,index,fs)) return -1;
      else{
        int count=1;
        for(int j=index; j<num-1; j++){
          int head=hand->cards[j]->value;
          int tail=hand->cards[j+1]->value;
          if(head==tail) ;
          else if(head-tail==1) count++;
          else break;
        }
        if(count==5)return 1;
      }
    }
    return 0;
  }
  else{
    if(remaining_cards<5) return 0;
    else{
      if(is_ace_low_straight_at(hand,index,fs)) return -1;
      else{
        int dist=1;
    //    for(int i=index; i<num-4; i++){
        int head=hand->cards[index]->value;
        suit_t head_suit=hand->cards[index]->suit;
        for(int j=index+1; j<num; j++){
          if(head_suit!=fs) break;
          int search_value=hand->cards[j]->value;
          suit_t search_suit=hand->cards[j]->suit;
          if(head-search_value==dist && search_suit==fs){
            dist++;
          }
        }
        if(dist==5){
          return 1;
        }
    //    } 
      }
    return 0;
    }
  }
}

int is_ace_low_straight_at(deck_t *hand, size_t index, suit_t fs){
  int num=hand->n_cards;
  int flag[4]={0};
  if(fs==NUM_SUITS){
    if(hand->cards[0]->value!=14) return 0;
    for(int i=2; i<=5; i++){
      for(int j=index; j<num; j++){
        if(hand->cards[j]->value==i){
          flag[i-2]=1;
        }
      }
    }
  }
  else{
    if(hand->cards[0]->value!=14 || hand->cards[0]->suit!=fs) return 0;
    for(int i=2; i<=5; i++){
      for(int j=index; j<num; j++){
        if(hand->cards[j]->value==i || hand->cards[j]->suit==fs){
          flag[i-2]=1;
        }
      }
    }
  }
  for(int i=0; i<4; i++){
    if(flag[i]!=1) return 0;
  }
  return 1;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  if(what==FULL_HOUSE){
    int t=0;
    for(int i=idx; i<idx+n; i++){
      ans.cards[t++]=hand->cards[idx];
    }
  }
  else if(what==FOUR_OF_A_KIND){
    int t=0;
    for(int i=idx; i<idx+4; i++){
      ans.cards[t++]=hand->cards[idx];
    }
    if(idx==0) ans.cards[t]=hand->cards[4];
    else ans.cards[t]=hand->cards[4];
  }
  else if(what==THREE_OF_A_KIND){
    int t=0, k=0;
    for(int i=idx; i<idx+n; i++){
      ans.cards[t++]=hand->cards[idx];
    }
    while(t<5){
      if(k-idx!=0&&k-idx!=1&&k-idx!=2){
        ans.cards[t++]=hand->cards[k];
      }
      k++;
    }
  }
  else if(what==TWO_PAIR){
    int t=0; 
    for(int i=idx; i<idx+n; i++){
      ans.cards[t++]=hand->cards[i];
    }
  }
  else if(what==PAIR){
    int t=0, k=0;
    for(int i=idx; i<idx+n; i++){
      ans.cards[t++]=hand->cards[idx];
    }
    while(t<5){
      if(k-idx!=0&&k-idx!=1){
        ans.cards[t++]=hand->cards[k];
      }
      k++;
    }
  }
  else if(what==NOTHING){
    int t=0;
    for(int i=0; i<5; i++){
      ans.cards[t++]=hand->cards[idx];
    }
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards,hand1->n_cards,sizeof(card_t),card_ptr_comp);
  qsort(hand2->cards,hand2->n_cards,sizeof(card_t),card_ptr_comp);
  int mode1 = 0, mode2 = 0;
  hand_eval_t eval1 = evaluate_hand(hand1, &mode1);
  hand_eval_t eval2 = evaluate_hand(hand2, &mode2);
  if(eval1.ranking<eval2.ranking) {
    if(mode1) free_hand_t(eval1);
    if(mode2) free_hand_t(eval2);
    return 1;
  }
  else if(eval1.ranking>eval2.ranking){
    if(mode1) free_hand_t(eval1);
    if(mode2) free_hand_t(eval2);
    return -1;
  }
  else{
    for(int i=0; i<5; i++){
      if(eval1.cards[i]->value > eval2.cards[i]->value){ 
        if(mode1) free_hand_t(eval1);
        if(mode2) free_hand_t(eval2);
        return 1;
      }
      else if(eval1.cards[i]->value < eval2.cards[i]->value){
        if(mode1) free_hand_t(eval1);
        if(mode2) free_hand_t(eval2);
        return -1;
      }
    }
  }
  if(mode1) free_hand_t(eval1);
  if(mode2) free_hand_t(eval2);
  return 0;
}

void free_hand_t(hand_eval_t t){
  for(int i=0; i<5; i++){
      free(t.cards[i]);
    }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){
  int num = hand->n_cards;
  unsigned *match = (unsigned*)malloc(num * sizeof(unsigned));
  for(int i=0; i<num; i++){
    match[i] = 0;
    for(int j=0; j<num; j++){
      if(hand->cards[j]->value == hand->cards[i]->value){
        match[i]++;
      }
    }
  }
  return match;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, card_t * from, suit_t fs, int mode) {
  assert(fs == NUM_SUITS || from->suit == fs);
  for(int i=0; i<5; i++){
    to[i] = (card_t*)malloc(sizeof(card_t));
  }
  if(mode<0){
    if(fs==NUM_SUITS){
      to[4]->value = 14;
      to[4]->suit = 0;
      for(int i=0; i<4; i++){
        to[i]->value = i+2;
        to[i]->suit = i;
      }
    }
    else{
      to[4]->value = 14;
      to[4]->suit = fs;
      for(int i=0; i<4; i++){
        to[i]->value = i+2;
        to[i]->suit = fs;
      }
    }
  }
  else{
    if(fs==NUM_SUITS){
      int init_value = from->value;
      for(int i=0; i<5; i++){
        to[i]->value = init_value - i;
        to[i]->suit = i%3;
      }
    }
    else{
      int init_value = from->value;
      for(int i=0; i<5; i++){
        to[i]->value = init_value - i;
        to[i]->suit = fs;
      }
    }
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards-5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	      assert(hand->cards[i]->value == VALUE_ACE &&
	        (fs == NUM_SUITS || hand->cards[i]->suit == fs));
        copy_straight(ans->cards, hand->cards[i], fs, x);
	    //   ans->cards[4] = hand->cards[i];
	    //   size_t cpind = i+1;
	    //   while(hand->cards[cpind]->value != 5 ||
	    //     !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	    //   cpind++;
	    //   assert(cpind < hand->n_cards);
	    //   }
	    // copy_straight(ans->cards, hand, cpind, fs,4) ;  
      }
      else {
	      copy_straight(ans->cards, hand->cards[i], fs, x);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand, int * mode) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      *mode = 1;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  int other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	      ans.cards[copy_idx] = hand->cards[i];
	      copy_idx++;
	      if (copy_idx >=5){
	        break;
	      }
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    *mode = 1;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
