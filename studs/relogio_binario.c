#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
void print_hora(int hora) {
 
switch (hora) {
case 1:
    printf("|   |                                 o  |   |\n");
    break;
case 2:
    printf("|   |                       o            |   |\n");
    break;
case 3:
    printf("|   |                       o         o  |   |\n");
    break;
case 4:
    printf("|   |             o                      |   |\n");
    break;
case 5:
    printf("|   |             o                   o  |   |\n");
    break;
case 6:
    printf("|   |             o         o            |   |\n");
    break;
case 7:
    printf("|   |             o         o         o  |   |\n");
    break;
case 8:
    printf("|   |   o                                |   |\n");
    break;
case 9:
    printf("|   |   o                             o  |   |\n");
    break;
case 10:
    printf("|   |   o                   o            |   |\n");
    break;
case 11:
    printf("|   |   o                   o         o  |   |\n");
    break;
case 12:
    printf("|   |   o         o                      |   |\n");
    break;
 
default:
   break;
}
}
 
void print_min(int min) {
 
switch (min) {
case 1:
    printf("|   |                                 o  |   |\n");
    break;
case 2:
    printf("|   |                           o        |   |\n");
    break;
case 3:
    printf("|   |                           o     o  |   |\n");
    break;
case 4:
    printf("|   |                     o              |   |\n");
    break;
case 5:
    printf("|   |                     o           o  |   |\n");
    break;
case 6:
    printf("|   |                     o     o        |   |\n");
    break;
case 7:
    printf("|   |                     o     o     o  |   |\n");
    break;
case 8:
    printf("|   |               o                    |   |\n");
    break;
case 9:
    printf("|   |               o                 o  |   |\n");
    break;
case 10:
    printf("|   |               o           o        |   |\n");
    break;
case 11:
    printf("|   |               o           o     o  |   |\n");
    break;
case 12:
    printf("|   |               o     o              |   |\n");
    break;
case 13:
    printf("|   |               o     o           o  |   |\n");
    break;
case 14:
    printf("|   |               o     o     o        |   |\n");
    break;
case 15:
    printf("|   |               o     o     o     o  |   |\n");
    break;
case 16:
    printf("|   |         o                          |   |\n");
    break;
case 17:
    printf("|   |         o                       o  |   |\n");
    break;
case 18:
    printf("|   |         o                 o        |   |\n");
    break;
case 19:
    printf("|   |         o                 o     o  |   |\n");
    break;
case 20:
    printf("|   |         o           o              |   |\n");
    break;
case 21:
    printf("|   |         o           o           o  |   |\n");
    break;
case 22:
    printf("|   |         o           o     o        |   |\n");
    break;
case 23:
    printf("|   |         o           o     o     o  |   |\n");
    break;
 
case 24:
    printf("|   |         o     o                    |   |\n");
    break;
case 25:
    printf("|   |         o     o                 o  |   |\n");
    break;
case 26:
    printf("|   |         o     o           o        |   |\n");
    break;
case 27:
    printf("|   |         o     o           o     o  |   |\n");
    break;
case 28:
    printf("|   |         o     o     o              |   |\n");
    break;
case 29:
    printf("|   |         o     o     o           o  |   |\n");
    break;
case 30:
    printf("|   |         o     o     o     o        |   |\n");
    break;
case 31:
    printf("|   |         o     o     o     o     o  |   |\n");
    break;
case 32:
    printf("|   |   o                                |   |\n");
    break;
case 33:
    printf("|   |   o                             o  |   |\n");
    break;
case 34:
    printf("|   |   o                       o        |   |\n");
    break;
case 35:
    printf("|   |   o                       o     o  |   |\n");
    break;
case 36:
    printf("|   |   o                 o              |   |\n");
    break;
case 37:
    printf("|   |   o                 o           o  |   |\n");
    break;
case 38:
    printf("|   |   o                 o     o        |   |\n");
    break;
case 39:
    printf("|   |   o                 o     o     o  |   |\n");
    break;
case 40:
    printf("|   |   o           o                    |   |\n");
    break;
case 41:
    printf("|   |   o           o                 o  |   |\n");
    break;
case 42:
    printf("|   |   o           o           o        |   |\n");
    break;
case 43:
    printf("|   |   o           o           o     o  |   |\n");
    break;
case 44:
    printf("|   |   o           o     o              |   |\n");
    break;
case 45:
    printf("|   |   o           o     o           o  |   |\n");
    break;
case 46:
    printf("|   |   o           o     o     o        |   |\n");
    break;
case 47:
    printf("|   |   o           o     o     o     o  |   |\n");
    break;
case 48:
    printf("|   |   o     o                          |   |\n");
    break;
case 49:
    printf("|   |   o     o                       o  |   |\n");
    break;
case 50:
    printf("|   |   o     o                 o        |   |\n");
    break;
case 51:
    printf("|   |   o     o                 o     o  |   |\n");
    break;
case 52:
    printf("|   |   o     o           o              |   |\n");
    break;
case 53:
    printf("|   |   o     o           o           o  |   |\n");
    break;
case 54:
    printf("|   |   o     o           o     o        |   |\n");
    break;
case 55:
    printf("|   |   o     o           o     o     o  |   |\n");
    break;
case 56:
    printf("|   |   o     o     o                    |   |\n");
    break;
case 57:
    printf("|   |   o     o     o                 o  |   |\n");
    break;
case 58:
    printf("|   |   o     o     o           o        |   |\n");
    break;
case 59:
    printf("|   |   o     o     o           o     o  |   |\n");
    break;
default:
    printf("|   |                                    |   |\n");
    break;
}
}
 
void print_relogio(int hora, int min){
    
//printf("%d:%d",hora,min);
printf(" ____________________________________________\n");
printf("|                                            |\n");
printf("|    ____________________________________    |_\n");
printf("|   |                                    |   |_)\n");
printf("|   |   8         4         2         1  |   |\n");
printf("|   |                                    |   |\n");
print_hora(hora);
printf("|   |                                    |   |\n");
printf("|   |                                    |   |\n");
print_min(min);
printf("|   |                                    |   |\n");
printf("|   |   32    16    8     4     2     1  |   |_\n");
printf("|   |____________________________________|   |_)\n");
printf("|                                            |\n");
printf("|____________________________________________|\n");
printf("\n");
 
}
 
   
 int main(){
    int n;
    char my[6], h[3], m[3];  
       
    while ( scanf("%s", &my[0]) == 1 ) {
             //printf("%s - ",my);
             strncpy(h, my,2);
             strcpy(m, &my[3]);
             //printf("%s - ",h);
             //printf("%s",m);
 
             print_relogio(atoi(h),atoi(m));
 
    } ;
           
     return(0);
 }
