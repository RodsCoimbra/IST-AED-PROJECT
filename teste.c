#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void main(){
    int i=0,j=0, n=0, maze[3][3];
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
        n++;
        maze[i][j] =n;
        printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    for (int p = 0; p < 3; p++) {
        for(int q = 0; q < 2; q++);
            printf("%d ", *(*(maze)+p*3+q+1));
printf("\n");
}
}