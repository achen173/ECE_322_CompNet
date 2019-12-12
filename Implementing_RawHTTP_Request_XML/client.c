// Alan Chen
// ECE 322 Assignment 6
// 12/10/2019

/*
 * client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"
#include <string.h>

int main(int argc, char **argv) 
{
    
    int clientfd;
    int round;
    char *num1, *num2;
    char *host, *port, buf2[MAXLINE]; // , ans1[MAXLINE], ans2[MAXLINE];
    if (argc != 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        exit(0);
    }
    num1 = argv[1];
    num2 = argv[2];
    if(strlen(num1) >= strlen(num2)){
        round = strlen(num1);
    }else{
        round = strlen(num2);
    }
    host = "localhost";
    port = "8080";
    char initial_setup[MAXLINE];
    char final_setup[MAXLINE];
    char roud[MAXLINE];
    char ans1[MAXLINE], ans2[MAXLINE];
    clientfd = Open_clientfd(host, port);
    sprintf(final_setup, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><methodCall><methodName>%s</methodName><params><param><value><double>%s</double></value></param><param><value><double>%s</double></value></param></params></methodCall>","sample.addmultiply",num1,num2);
    sprintf(initial_setup, "POST /RPC2 HTTP/1.1\r\nHost: %s\r\nContent-Type: text/xml\nContent-Length: %d\r\n\r\n", "localhost:8080",strlen(final_setup));
    Rio_writen(clientfd, initial_setup, strlen(initial_setup));
    Rio_writen(clientfd, final_setup, strlen(final_setup));
    Rio_readn(clientfd, buf2, MAXLINE);
    Close(clientfd);  
   //  printf("%s\n", buf2); 
    int print2 = 0;
    char a = '>'; 
    char b = '<';
    char c = '\n';
    // All the answers are stored in buf2, therefore we need to parse it
    int i = 0;
    int temp1 = 0;
    int temp2 = 0;
    while(i < sizeof(buf2)){
        if(buf2[i] == a){
            break;
        }
        i += 1;
    }
    while(i < strlen(buf2)){
        if(buf2[i] == a){
            print2 = 1;
            i += 1;
            continue;
        }
        if(buf2[i] != b && buf2[i] != c && print2){
            // int temp = 0;
            if(temp1 == 0){
                while(buf2[i] != b && buf2[i] != c && print2){
                    ans1[temp1] = buf2[i];
                    temp1 += 1;
                    i+= 1;
                }
            }else{
                while(buf2[i] != b && buf2[i] != c && print2){
                    ans2[temp2] = buf2[i];
                    temp2 += 1;
                    i+= 1;
                }  
            }
        }
        if(buf2[i] == b){
            print2 = 0;
        }
        i += 1;
    }
    float f;
    f = (float)atof(ans1);
    float f2;
    f2 = (float)atof(ans2);
    if(round >= 3){
        sprintf(roud, "%.%.%df", round-2);
        printf(roud, f);
        printf("%s", "   ");
        printf(roud, f2);      
    }else{
        printf("%s", ans1);
        printf("%s", "   ");
        printf("%s", ans2);
    }
    printf("\n");
    exit(0);  
} 

