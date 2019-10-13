#include "player.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


char converter(char rank[]){
   char check;
    if(rank[1] != NULL && rank[1] == '0'){
        check = '0';
    }else{
        check = rank[0];
    };
    return check;
}


struct hand* add_OneCard_To_Hand(struct hand* ThePointer, struct card Addcard){
  struct hand *temp = ThePointer;
  struct hand *start = ThePointer;
  temp=(struct hand*)malloc(sizeof(struct hand));
  temp->top = Addcard;
  temp->next = ThePointer;
  return temp;
}

char ask_for_input(int kj, struct player your_hand, struct player opponent_hand){
    char ranklist[] = {'2','3','4','5','6','7','8','9','0','J','Q','K','A'};
    char i;
    bool correct_input=false;
    if(kj == 1){
        while(!correct_input){           
            printf("Player 1's turn, enter a Rank: ");  // Player 1 is the user
            scanf("%2c", &i);
            int have = search2(your_hand.card_list, i); // checks if you have the card
            if(!have){
                printf("\nError - must have at least one card from rank to play \n");
            }else{
                int k = search2(opponent_hand.card_list, i);
                if(k == 1){
                        return i;
                    }
                else{
                    if(&i == '0'){
                        printf("    - Player 2 has no 10's \n");
                    }else{
                        printf("    - Player 2 has no %c's \n",i);
                    }
                    return 'N';
                }
                
            }
        }
    }else{  // computer side
        while(!correct_input){
            int num = (rand() % (12 - 0 + 1)) + 0;
            int have = search2(your_hand.card_list, ranklist[num]); // checks if you have the card
            if(have){
                printf("Player 2's turn, enter a Rank: %c \n", ranklist[num]);  // Player 2 is the computer
                print_hand(0, your_hand.card_list);
                print_hand(1, opponent_hand.card_list);
                int kk = search2(opponent_hand.card_list, ranklist[num]);
                correct_input = true;
                if(kk == 1){
                    if(ranklist[0] == '0'){
                        correct_input = true;
                        return '0';
                    }else{
                        correct_input = true;
                        return ranklist[0];
                    }
                }else{
                    if(ranklist[num] == '0'){
                        printf("    - Player 1 has no 10's \n");
                    }else{
                        printf("    - Player 1 has no %c's \n",ranklist[num]);
                    }
                    correct_input = true;
                    return 'N';
                }
            }
        }
    }
}

struct card search_RC(struct hand* target, char rank){ 
    while(target != NULL){
        if(target->top.rank == rank ){    // convert rank to char
            return target->top;
        }
    target = target->next;
    }
    return target->top;
}

int search2(struct hand* target2, char rank){ 
    struct hand* target = target2;
    int i = 0;
    while((target) != NULL){
        if((target->top.rank) == rank ){    // convert rank to char
            return 1;
        }
        i++;
    target = target->next;
    }
    return 0;
}

struct hand* remove_card(int k, struct hand* target, char check){
    struct card return_card;
    struct hand* temp = target;
    struct hand* prev = target; 
    if (temp != NULL && (temp->top.rank) == check){ 
        return_card = temp->top;
        prev = temp->next;   // Changed head 
        free(temp);               // free old head 
        return prev; 
    }
    struct hand* PINTER = temp;
    while (temp != NULL && (temp->top.rank) != check) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
    //return_card = temp->top;
    prev->next = temp->next; 
    free(temp);  // Free memory 
    return PINTER; 
} 

char check_add_book(struct card check_card, struct hand* target){
    int winner = 0;
    struct hand* ThePointer = target;
    while(ThePointer != NULL) {
        if((ThePointer->top.rank) == check_card.rank){
            winner ++;
        }
        ThePointer = ThePointer -> next;
    }
    if(winner == 4){
        return check_card.rank;
    }
    return 'N';
}


void print_book(int ID, struct player target){
    if(ID == 1){
        printf("Player 1's Book - ");
    }else{
        printf("Player 2's Book - ");
    }
    for(int i = 0; i < sizeof(target.book); i++){
        if((target.book)[i] != NULL){
            printf(" %c", (target.book)[i]);
        }
    }
    printf("\n");
}

struct card transfer_card(int ID, char found_card_rank){// returns the tranfered card
    struct card temp;
    if(ID == 1){
        temp = search_RC(computer.card_list, found_card_rank); // this will always be true
        computer.card_list = remove_card(1, computer.card_list, found_card_rank);
        user.card_list = add_OneCard_To_Hand(user.card_list, temp);
    }else{
        temp = search_RC(user.card_list, found_card_rank);
        user.card_list = remove_card(0, user.card_list, found_card_rank);
        computer.card_list = add_OneCard_To_Hand(computer.card_list, temp);
    }
    return temp;
}