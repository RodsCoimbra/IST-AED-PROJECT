#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

int FA1 (int** maze, int l, int c, int lin, int col);
int FA2 (int** maze, int l, int c, int lin, int col);
int FA3 (int** maze, int l, int c, int lin, int col);
int FA4 (int** maze, int l, int c, int lin, int col);
int FA5 (int** maze, int l, int c, int lin, int col);
/*int FA6 (int** maze, int l, int c, int lin, int col, int l2, int c2);*/
int out (int l, int c, int lin, int col);

int mod(int** maze, int l, int c, int lin, int col,char* modo, int l2, int c2){
    int resp;
    if((strcmp(modo,"A1"))==0){
        resp = FA1(maze, l, c, lin, col);
        return resp;
    }
    else if((strcmp(modo,"A2"))==0){
        resp = FA2(maze, l, c, lin, col);
        return resp;
    }
    else if((strcmp(modo,"A3"))==0){
        resp = FA3(maze, l, c, lin, col);
        return resp;
    }
    else if((strcmp(modo,"A4"))==0){
        resp = FA4(maze, l, c, lin, col);
        return resp;
    }
    else if((strcmp(modo,"A5"))==0){
        resp = FA5(maze, l, c, lin, col);
        return resp;
    }
    else if((strcmp(modo,"A6"))==0){
        //resp = FA6(maze, l, c, lin, col, l2, c2);
        return -5;}
    else
    {
    exit(-1);
    }
}
void separar(char* str)
{
    int i;
    char* ptroca = NULL;
    for(i=0; str[i] != '\0' ; i++)   // Executa enquanto não chegar ao final da string
    {
        if(str[i] == '.')
        {
            ptroca = &str[i];
        }
    }
    *ptroca = ' ';
}


int main(int argc, char *argv[]) {
opterr = 0;
int opt, lin = 0, col = 0, parede, l=0, c=0, tamanho = 0,linaux=0, colaux=0;
tamanho = strlen(argv[2])+1;
char* fileread =(char*) calloc(1,tamanho*sizeof(char)), *filewrite = (char*) calloc(1,(tamanho+1)*sizeof(char));
if (fileread == NULL || filewrite == NULL)
{
    exit(-1);
}
char modo[3];
while((opt= getopt(argc, argv,"s:"))!= -1){
    switch (opt){
        case 's':
        sscanf(optarg," %s", fileread);
        break; 
    default :
    {
        exit(-1);
    }
}
}
FILE *fmaze = NULL;
FILE *fsol = NULL;
if((fmaze = fopen(fileread, "r")) == NULL)
{
    exit(-1);
}
separar(fileread);
sscanf(fileread, " %s", filewrite);
strcat(filewrite,".sol2");  //apenas para teste, garantir que MUDAMOS PARA SOL1!!!!!!
if ((fsol = fopen(filewrite, "w")) == NULL)      // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha
        {
         fclose(fmaze);
         exit(-1);
        }

fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo);
int l2 = 0, c2 = 0;
if((strcmp(modo,"A6"))!=0)
    {
    fscanf(fmaze,"%d", &parede);
    }
else
    {
    fscanf(fmaze,"%d %d %d",&l2, &c2, &parede);
    }
linaux = lin;
colaux = col;
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
int resposta; 
resposta = mod(maze, l-1, c-1, lin-1, col-1, modo, l2, c2);
fprintf(fsol,"%d\n\n", resposta);
while (1){
fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo);
if((strcmp(modo,"A6"))!=0)
    {
    fscanf(fmaze,"%d", &parede);
    }
else
    {
    fscanf(fmaze,"%d %d %d",&l2, &c2, &parede);
    } 
if(feof(fmaze) != 0) break;
if(lin != linaux){
maze =(int**) realloc (maze,lin*sizeof(int*));
if (maze == NULL)
{
    exit(-1);
}
linaux=lin;
}
if(col != colaux){
for (int i=0; i < lin; i++)
{
    maze[i]=(int*) realloc (maze[i], col*sizeof(int));
    if(maze[i] == NULL){
        exit(-1);
    }
}
colaux = col;
}

for(int i=0; i < lin; i++){
for(int j=0; j < col; j++){
maze[i][j] = 0;}}
for(int i=0, l1, c1, custo; i < parede; i++){
fscanf(fmaze, "%d %d %d", &l1, &c1, &custo);
maze[l1-1][c1-1] = custo;
}
resposta = mod(maze, l-1, c-1, lin-1, col-1, modo, l2, c2);
fprintf(fsol,"%d\n\n", resposta);
}
free(fileread);
free(filewrite);
for (int i=0; i < lin;i++){
    free(maze[i]);
}
free(maze);
fclose(fsol);
fclose(fmaze);
}




int out (int l, int c, int lin, int col) {
    if (l<0 || l>lin || c<0 || c>col) return -2;
    return 0;
}

int FA1 (int** maze, int l, int c, int lin, int col) {
    int A1= out(l, c, lin, col);
    if(A1 != -2){
    A1 = maze[l][c];}
    return A1;
}

int FA2 (int** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==0) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==0) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==0) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==0)){ 
        return 1;}
    return 0;
}

int FA3 (int** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]>=1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]>=1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]>=1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]>=1)){
    return 1;}
    return 0;
}

int FA4 (int** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==-1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==-1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==-1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==-1)){
    return 1;}
    return 0;
}

int FA5 (int** maze, int l, int c, int lin, int col) {
    if (out(l, c, lin, col)==-2) return -2;
    else if (maze[l][c]<=0) return -1;
    else if ((out(l-1, c, lin, col) != -2) && (out(l+1, c, lin, col)!=-2) && maze[l-1][c]==0 && maze[l+1][c]==0){
        return 1;}
    else if ((out(l, c+1, lin, col) !=-2) && (out(l, c-1, lin, col) !=-2) && maze[l][c-1]==0 && maze[l][c+1]==0){
        return 1;}
    else {
        return 0;}
}

 /*int FA6 (int** maze, int l, int c, int lin, int col) {
        if (maze[l][c]==0 && maze[l2[c2]==0] && (out(l,c,lin,col)!=-2) && (out(l2,c2,lin,col)!=-2)){
            for (maze[l][c]!=maze[l+1][c] && maze[l][c]!=maze[l][c+1]) {
                
            }
        }
        else {return 0;}
 }*/