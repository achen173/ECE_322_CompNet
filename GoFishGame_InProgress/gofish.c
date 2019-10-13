#include <stdio.h>
#include "card.h"
#include "player.h"
#include "deck.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define   message_for(a, b)  \
          printf(#a " and " #b ": We love you!\n")

int card_index;
int userbook_index = 0;
int compbook_index = 0; 


int user_turn(){
  int again = 1;
    while(again){
      print_book(1, user);
      print_book(0, computer);
      char found_card_rank = ask_for_input(1, user, computer);  // user = 0, yourself, opponent
      // print_book(1, user);
      // print_book(0, computer);
      if(found_card_rank == 'N'){ // if not found
        struct card newCard = deck_instance.list[card_index];
        user.card_list = add_OneCard_To_Hand(user.card_list, newCard);
        print_drawed_card(1, newCard);
        // if there is 4-kind -> checkBOOK = rank
        char checkBOOK = check_add_book(newCard, user.card_list);
        if(checkBOOK != 'N'){ // N = No four of a kind
          user.book[userbook_index] = checkBOOK;
          if(userbook_index == 6){
            return 7;
          }  
          userbook_index ++;
          // remove all four ranks
          int hasCard = search2(user.card_list, checkBOOK);
          while(hasCard){ // remove all four ranks
            user.card_list = remove_card(1, user.card_list, found_card_rank);
            hasCard = search2(user.card_list, checkBOOK);
          }
          print_book(1, user);
        }
        print_book(1, user);
        print_book(0, computer);
        printf("\n");
        // checking purposes above
        card_index++;
        again = 0;
      }else{  // if found
        int continue2 = search2(computer.card_list, found_card_rank);
        printf("\n    - Player 2 has ");
        while(continue2){   // keeps on searching and removing/adding
          struct card temp = transfer_card(1, found_card_rank);
          // if there is 4-kind -> checkBOOK = rank
          char checkBOOK = check_add_book(temp, user.card_list);
          if(checkBOOK != 'N'){ // N = No four of a kind
            user.book[userbook_index] = checkBOOK; 
            if(userbook_index == 6){
              return 7;
            }   
            userbook_index ++;
            // remove all four ranks
            int hasCard = search2(user.card_list, checkBOOK);
            while(hasCard){ // remove all four ranks
              user.card_list = remove_card(1, user.card_list, found_card_rank);
              hasCard = search2(user.card_list, checkBOOK);
            }
            print_book(1, user);
          }
          if(temp.rank == '0'){
            printf("10%c ", (temp.rank));
          }else{
            printf("%c%c ", temp.rank, temp.suit);
          }
          continue2 = search2(computer.card_list, found_card_rank);
        }

        printf("\n");
        printf("    - Player 1 gets another turn \n");
        print_hand(0, computer.card_list);
        print_hand(1, user.card_list);
        printf("\n");
      }
    }  
}

int comp_turn(){
  int again2 = 1;
    while(again2){
      char found_card_rank = ask_for_input(0, computer, user);  // user = 0, yourself, opponent
      if(found_card_rank == 'N'){ // if not found
        struct card newCard = deck_instance.list[card_index];
        computer.card_list = add_OneCard_To_Hand(computer.card_list, newCard);
        print_drawed_card(0, newCard);

        // if there is 4-kind -> checkBOOK = rank
        char checkBOOK = check_add_book(newCard, computer.card_list);
        if(checkBOOK != 'N'){ // N = No four of a kind
          computer.book[userbook_index] = checkBOOK;  
          if(compbook_index == 6){
            return 7;
          }  
          compbook_index ++;
          // remove all four ranks
          int hasCard = search2(computer.card_list, checkBOOK);
          while(hasCard){ // remove all four ranks
            computer.card_list = remove_card(1, computer.card_list, found_card_rank);
            hasCard = search2(computer.card_list, checkBOOK);
          }
          print_book(1, user);
        }

        print_book(1, user);
        print_book(0, computer);
        printf("\n");
        card_index++;
        again2 = 0;
      }else{  // if found
        int continue2 = search2(user.card_list, found_card_rank);
        printf("    - Player 1 has ");
        while(continue2){   // keeps on searching and removing/adding
          struct card temp = transfer_card(0, found_card_rank);
          
          
          char checkBOOK = check_add_book(temp, computer.card_list);
          if(checkBOOK != 'N'){ // N = No four of a kind
            computer.book[userbook_index] = checkBOOK; 
          if(compbook_index == 6){
            return 7;
          } 
            compbook_index ++;
            // remove all four ranks
            int hasCard = search2(computer.card_list, checkBOOK);
            while(hasCard){ // remove all four ranks
              computer.card_list = remove_card(0, computer.card_list, found_card_rank);
              hasCard = search2(computer.card_list, checkBOOK);
            }
            print_book(1, computer);
          }
          
          
          if(temp.rank == '0'){
            printf("10%c ", temp.suit);
          }else{
            printf("%c%c ", temp.rank, temp.suit);           
          }
          continue2 = search2(computer.card_list, found_card_rank);
        }
        printf("\n    - Player 2 gets another turn \n");
        printf("\n");
      }
    }
}

void print_drawed_card(int k, struct card newCard){
  if(k==1){
        if(newCard.rank == '0'){
          printf("    - Go Fish, Player 1 draws 10%c \n", newCard.suit);
        }else{
          printf("    - Go Fish, Player 1 draws %c%c \n", newCard.rank, newCard.suit);
        }
        print_hand(1, user.card_list);
        printf("    - Player 2's turn\n\n");
    }else{
        if(newCard.rank == '0'){
          printf("    - Go Fish, Player 2 draws 10%c \n", newCard.suit);
        }else{
          printf("    - Go Fish, Player 2 draws %c%c \n", newCard.rank, newCard.suit);
        }
        print_hand(0, computer.card_list);
        printf("    - Player 1's turn\n\n");
    }
  }
// 1 will always be user
int main(int args, char* argv[]) 
{
  // initialization
  srand(time(NULL));
  shuffle();
  computer.card_list = deal_player_cards(computer.card_list, 7); //player 2
  print_hand(0, computer.card_list);
  user.card_list = deal_player_cards(user.card_list, 14); //player 1
  print_hand(1, user.card_list);
  card_index = 14; // last one is 51
  // all initialization are finished

  bool winner = false;
  int gofish = 1;
  char yn;
  while(gofish){
    while(card_index < 52 && !winner){
      int isUserWinner = user_turn(); // will return 7 if won by book
      int isCompWinner = comp_turn(); // will return 7 if won by book
      if(isUserWinner == 7){
        winner = true;
        printf("\n\n YOU WON !!!!!!!! \n");
      }else if (isCompWinner == 7){
        winner = true;
        printf("\n\n YOU LOST !!!!!!!! \n");
      }
    }
    printf( "\nDo you want to play again [Y/N]: ");
    scanf("%2s", yn);
    if(yn == 'N'){
      gofish = 0; // gets out of the loop
    }
  }
//   for(int k = 0; k < 18; k++){
//     printf("Rank: %p , Suit: %x\n", deck_instance.list[k].rank, deck_instance.list[k].suit);
//     printf("Value: %c, Suits: %c \n" , *deck_instance.list[k].rank, *deck_instance.list[k].suit);
//  }
  return 0; 
}
