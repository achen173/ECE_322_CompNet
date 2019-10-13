#include "deck.h"

void shuffle() {
    int i, j;
    char suitlist[4] = {'C', 'D', 'H', 'S'};
    char ranklist[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 13; j++) {
            struct card new_card = {.suit=suitlist[i], .rank=ranklist[j]};
            deck_instance.list[deck_instance.top_card++] = new_card; 
        }
    } // complete deck instance
    for(i = 51; i > 0; i--) {
        j = rand() % i;
        struct card temp = deck_instance.list[i];
        deck_instance.list[i] = deck_instance.list[j];
        deck_instance.list[j] = temp;
    }
    deck_instance.top_card = 52;
}

struct hand* deal_player_cards(struct hand* target, int end){
  struct hand *p = target;
  struct hand *temp = target;
  struct hand *start = target;
  temp=(struct hand*)malloc(sizeof(struct hand));
  temp->top = deck_instance.list[end - 7];  //temp->top = deck_instance.list[end - 7];
  temp->next = NULL;
  p = temp, start = temp;
  for(int i = end-6; i < end; i++){ //for(int i = end-6; i < end; i++){
    temp=(struct hand*)malloc(sizeof(struct hand));
    temp->top = deck_instance.list[i];
    temp->next = NULL;
    p->next = temp;
    p = p->next;
  }
  return start;
}

void print_hand(int k, struct hand* temp ){
  struct hand* ThePointer = temp;
  if(k == 1){
    printf("Player 1's Hand - ");
  }else{
    printf("Player 2's Hand - ");
  }
  while(ThePointer != NULL) {
    if((ThePointer->top.rank) == '0'){
      printf("1%c%c ", (ThePointer->top.rank), (ThePointer->top.suit));
    }else{
      printf("%c%c ", (ThePointer->top.rank), (ThePointer->top.suit));
    }
    ThePointer = ThePointer->next;
  }
  printf("\n");
 }

