#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows

int FA1 (int** maze, int l, int c, int lin, int col);
int FA2 (int** maze, int l, int c, int lin, int col);
int FA3 (int** maze, int l, int c, int lin, int col);
int FA4 (int** maze, int l, int c, int lin, int col);
int out (int l, int c, int lin, int col);


int main(int argc, char *argv[]) {
opterr = 0;
char file[maxficheiro] = {""};
int s = 0, opt, lin = 0, col = 0, parede, l=0, c=0;
char modo[3];
while((opt= getopt(argc, argv,"s:"))!= -1){
    switch (opt){
        case 's':
        s = 1;
        sscanf(optarg," %s", file);
        break; 
    default :
    {
        exit(-1);
    }
}
}
FILE *fmaze = NULL;
FILE *fsol = NULL;
if((fmaze = fopen(file, "r")) == NULL)
{
    exit(-1);
}
if ((fsol = fopen(file, "w")) == NULL)      // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha
        {
         fclose(fmaze);
         exit(-1);
        }
fscanf(fmaze, "%d %d %d %d %s %d", &lin, &col, &l, &c, modo, &parede);
int** maze =(int**) malloc (lin*sizeof(int*));
if (maze == NULL)
{
    exit(-1);
}
for (int i=0; i < lin;i++)
{
    maze[i]=(int*) calloc (1, col *sizeof(int));
    if(maze[i] == NULL){
        exit(-1);
    }
} 
for(int i=0, l1, c1, custo; i < parede; i++)
{
fscanf(fmaze, "%d %d %d", &l1, &c1, &custo);
maze[l1-1][c1-1] = custo;
}
int d = FA2(maze, l-1, c-1, lin-1, col-1);
fprintf(fsol,"%d\n\n", d);

while (1){  
fscanf(fmaze, "%d %d %d %d %s %d", &lin, &col, &l, &c, modo, &parede);
if(feof(fmaze) != 0) break;

maze =(int**) realloc (maze,lin*sizeof(int*));
if (maze == NULL)
{
    exit(-1);
}

for (int i=0; i < lin; i++)
{
    maze[i]=(int*) realloc (maze[i], col*sizeof(int));
    if(maze[i] == NULL){
        exit(-1);
    }
}


for(int i=0; i < lin; i++){
for(int j=0; j < col; j++){
maze[i][j] = 0;}}
for(int i=0, l1, c1, custo; i < parede; i++)
{
fscanf(fmaze, "%d %d %d", &l1, &c1, &custo);
maze[l1-1][c1-1] = custo;
}
d = FA2(maze, l-1, c-1, lin-1, col-1);
fprintf(fsol,"%d\n\n", d);
}
}






























int out (int l, int c, int lin, int col) {
    if (l<0 || l>lin || c<0 || c>col) return -2;
}


int FA1 (int** maze, int l, int c, int lin, int col) {
    int A1= out(l, c, lin, col);
    if(A1 != -2){
    A1 = maze[l][c];}
    return A1;
}

/*int FA2 (int** maze, int l, int c, int lin, int col){
    int A2=0;
    if (maze[l+1][c] == 0 || maze[l][c+1]==0 || maze[l-1][c]==0 || maze[l][c-1]==0){
    A2++;
    return A2;}
}*/

int FA2 (int** maze, int l, int c, int lin, int col) { // ver ambiguidade do enunciado se é -2 ou 0 se tiver uma fora e uma dentro
    int A2=0;
    if ((out(l, c, lin, col)==-2)) return -2;
    if (out(l+1, c, lin, col)!=-2 && maze[l+1][c]==0){ A2++;
        return A2;}
    else if (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==0){ A2++;
        return A2;}
    else if (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==0){ A2++;
        return A2;}
    else if (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==0){ A2++;
        return A2;}
}
int FA3 (int** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2) || (out(l-1, c, lin, col) == -2) || (out(l+1, c, lin, col)==-2) || (out(l, c+1, lin, col)==-2) || (out(l, c-1, lin, col)==-2)) return -2;
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

int FA4 (int** maze, int l, int c, int lin, int col) {
    int A4 = 0;
    if ((out(l, c, lin, col)==-2) || (out(l-1, c, lin, col) == -2) || (out(l+1, c, lin, col)==-2) || (out(l, c+1, lin, col)==-2) || (out(l, c-1, lin, col)==-2)) return -2;    
    if (maze[l+1][c]==-1) A4++;
        return A4;
    if (maze[l][c+1]==-1) A4++;
        return A4;
    if (maze[l-1][c]==-1) A4++;
        return A4;
    if (maze[l+1][c]==-1) A4++;
        return A4;
}

int FA5 (int** maze, int l, int c, int lin, int col) {
    int A5 = 0; 
    if ((out(l, c, lin, col)==-2) || (out(l-1, c, lin, col) == -2) || (out(l+1, c, lin, col)==-2) || (out(l, c+1, lin, col)==-2) || (out(l, c-1, lin, col)==-2)) return -2;
    if (maze[l-1][c]==0 || maze[l+1][c]==0 ) A5++;
        return A5;
    if (maze[l][c-1]==0 || maze[l][c+1]==0) A5++;
        return A5;
}
