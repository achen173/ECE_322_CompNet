#ifndef CARD_H
#define CARD_H

/*
  Valid suits: C, D, H, and S
  Valid ranks: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A
*/
struct card
{
  char rank; // Max Value + null character
  char suit; // Suits Name + null character
  //char rank[3]; // Max Value + null character
};
/*
  Linked list of cards in hand.
    top: first card in hand
    next: pointer to next card in hand
*/
struct hand //struct linked_list
{
  struct card top;  //int payload;
  struct hand* next;  //struct linked_list* next;
};

#endif
