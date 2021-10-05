#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows

int main(int argc, char *argv[]) {
opterr = 0;
char file[maxficheiro]={""};
int s = 0, opt, l = 0, c = 0;
 while((opt= getopt(argc, argv,"s"))!= -1){
    switch (opt){
        case 's':
        s = 1;
        sscanf(optarg, "%s", file);
        break; 
    default :
    {
        exit(-1);
    }
}
}
FILE *fmaze = NULL;
if((fmaze = fopen(file, "r")) == NULL)
{
    exit(-1);
}
fscanf(fmaze, "%d %d", &l, &c);
int** maze =(int**) malloc (l*sizeof(int*));
if (maze == NULL)
{
    exit(-1);
}
for (int i=0; i < l;i++)
{
    maze[i]=(int*) calloc (1, c *sizeof(int));
    if(maze[i] == NULL){
        exit(-1);
    }
}
fscanf(fmaze, "%d %d", &l, &c);
}


int FA1 (int** maze, int l, int c) {
    int A1=0;
    switch (maze[l][c]) {
        case 0: 
        A1 = 0; 
        break;
        case -1: 
        A1 = -1; 
        break;
        default:
        A1 = maze[c][l]; 
        break;
    }
    return A1;
}

/*int FA2 (int** maze, int l, int c){
    int A2=0;
    if (maze[l+1][c] == 0 || maze[l][c+1]==0 || maze[l-1][c]==0 || maze[l][c-1]==0){
    A2++;
    return A2;}
}*/

int FA2 (int** maze, int l, int c) {
    int A2=0;
    if (maze[l+1][c]==0){ A2++;
        return A2;}
    else if (maze[l][c+1]==0){ A2++;
        return A2;}
    else if (maze[l-1][c]==0){ A2++;
        return A2;}
    else if (maze[l+1][c]==0){ A2++;
        return A2;}
}

int FA3 (int** maze, int l, int c) {
    int A3=0;
    if (maze[l+1][c]<=1){ A3++;
        return A3;}
    else if (maze[l][c+1]<=1){ A3++;
        return A3;}
    else if (maze[l-1][c]<=1){ A3++;
        return A3;}
    else if (maze[l+1][c]<=1){ A3++;
        return A3;}
}

int FA4 (int** maze, int l, int c) {
    int A4=0;
    if (maze[l+1][c]==-1 && A4==0) A4++;
        else return A4;
    if (maze[l][c+1]==-1 && A4==0) A4++;
        else return A4;
    if (maze[l-1][c]==-1 && A4==0) A4++;
        else return A4;
    if (maze[l+1][c]==-1 && A4==0) A4++;
        else return A4;
}

int FA4 ()