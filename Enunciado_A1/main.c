#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

int FA1 (short** maze, int l, int c, int lin, int col);
int FA2 (short** maze, int l, int c, int lin, int col);
int FA3 (short** maze, int l, int c, int lin, int col);
int FA4 (short** maze, int l, int c, int lin, int col);
int FA5 (short** maze, int l, int c, int lin, int col);
int FA6 (short** maze, int l, int c, int lin, int col, int l2, int c2, short fim);
int out (int l, int c, int lin, int col);
void freetabela(short** maze, int lin);

int mod(short** maze, int l, int c, int lin, int col,char* modo, int l2, int c2){
    int resp;
    short fim = 0;
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
        if ((out(l,c,lin,col) ==-2) || (out(l2,c2,lin,col) ==-2)){
            return -2;
        }
        if(maze[l][c]!=0 || maze[l2][c2]!=0){
            return 0;
        }
        resp = FA6(maze, l, c, lin, col, l2, c2, fim);
        return resp;}
    else
    {
    exit(0);
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

void freetabela(short** maze,int lin){
    for (int i=0; i < lin;i++){
    free(maze[i]);
    }   
    free(maze);
}

int main(int argc, char *argv[]) {
opterr = 0;
int opt, lin = 0, col = 0, parede, l=0, c=0, tamanho = 0,linaux=0, colaux=0;
tamanho = strlen(argv[2])+1;
char* fileread =(char*) calloc(1,tamanho*sizeof(char)), *filewrite = (char*) calloc(1,(tamanho+1)*sizeof(char));
if (fileread == NULL || filewrite == NULL)
{
    exit(0);
}
char modo[3];
while((opt= getopt(argc, argv,"s:"))!= -1){
    switch (opt){
        case 's':
        sscanf(optarg," %s", fileread);
        if(fileread[tamanho-5] != '.'|| fileread[tamanho-4] != 'i' || fileread[tamanho-3] != 'n' || fileread[tamanho-2] != '1'){
            exit(0);
        }

        break; 
    default :
    {
        exit(0);
    }
}
}
FILE *fmaze = NULL;
FILE *fsol = NULL;
if((fmaze = fopen(fileread, "r")) == NULL)
{
    free(filewrite);
    free(fileread);
    exit(0);
}
separar(fileread);
sscanf(fileread, " %s", filewrite);
strcat(filewrite,".sol2");  //apenas para teste, garantir que MUDAMOS PARA SOL1!!!!!!
if ((fsol = fopen(filewrite, "w")) == NULL){ // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha
        free(filewrite);
        free(fileread);
        fclose(fmaze);
        exit(0);
        }
free(filewrite);
free(fileread);
if(fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo) != 5){
    fclose(fmaze);
    fclose(fsol);
    exit(0);}
int l2 = 0, c2 = 0;
if((strcmp(modo,"A6"))!=0)
    {
    if (fscanf(fmaze,"%d", &parede) != 1){
        fclose(fmaze);
        fclose(fsol);
        exit(0);}
    }
else
    {
    if (fscanf(fmaze,"%d %d %d",&l2, &c2, &parede) != 3){
        fclose(fmaze);
        fclose(fsol);
        exit(0);}
    }
linaux = lin;
colaux = col;
short** maze =(short**) malloc (lin*sizeof(short*));
if (maze == NULL)
{
    exit(0);
}
for (int i=0; i < lin;i++)
{
    maze[i]=(short*) calloc (1, col *sizeof(short));
    if(maze[i] == NULL){
        exit(0);
    }
} 
for(int i=0, l1, c1, custo; i < parede; i++)
{
if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3){
        fclose(fmaze);
        fclose(fsol);
        exit(0);}
maze[l1-1][c1-1] = custo;
}
int resposta; 
resposta = mod(maze, l-1, c-1, lin-1, col-1, modo, l2-1, c2-1);
fprintf(fsol,"%d\n\n", resposta);
while (1){
if (fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo) != 5) {
    if(feof(fmaze) != 0) break;
    else{
        fclose(fmaze);
        fclose(fsol);
        exit(0);}}
if((strcmp(modo,"A6"))!=0)
    {
    if (fscanf(fmaze,"%d", &parede) !=1){
        fclose(fmaze);
        fclose(fsol);
        exit(0);};
    }
else
    {
    if(fscanf(fmaze,"%d %d %d",&l2, &c2, &parede) != 3){
        fclose(fmaze);
        fclose(fsol);
        exit(0);}
    } 
/////////////////////////////////////////////////////////////

if(lin != linaux){
freetabela(maze, linaux);
linaux=lin;
colaux=-1;
maze =(short**) malloc (lin*sizeof(short*));
if (maze == NULL)
{ 
    exit(0);
}
}
if(col != colaux){
if(colaux != -1){
    for (int i=0; i < linaux;i++)
    {
    free(maze[i]);
    }
}
for (int i=0; i < lin;i++){
    maze[i]=(short*) calloc (1, col *sizeof(short));
    if(maze[i] == NULL){
        exit(0);
    }
} 
colaux = col;
}
else{
for(int i=0; i < lin; i++){
for(int j=0; j < col; j++){
maze[i][j] = 0;}}
}

//////////////////////////////////////////////////////////
for(int i=0, l1, c1, custo; i < parede; i++){
if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo)!= 3){
        fclose(fmaze);
        fclose(fsol);
        exit(0);}
maze[l1-1][c1-1] = custo;
}
resposta = mod(maze, l-1, c-1, lin-1, col-1, modo, l2-1, c2-1);
fprintf(fsol,"%d\n\n", resposta);
}
freetabela(maze, lin);
fclose(fsol);
fclose(fmaze);
return 0;
}


int out (int l, int c, int lin, int col) {
    if (l<0 || l>lin || c<0 || c>col) return -2;
    return 0;
}

int FA1 (short** maze, int l, int c, int lin, int col) {
    int A1= out(l, c, lin, col);
    if(A1 != -2){
    A1 = maze[l][c];}
    return A1;
}

int FA2 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==0) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==0) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==0) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==0)){ 
        return 1;}
    return 0;
}

int FA3 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]>=1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]>=1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]>=1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]>=1)){
    return 1;}
    return 0;
}

int FA4 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==-1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==-1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==-1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==-1)){
    return 1;}
    return 0;
}

int FA5 (short** maze, int l, int c, int lin, int col) {
    if (out(l, c, lin, col)==-2) return -2;
    else if (maze[l][c]<=0) return -1;
    else if ((out(l-1, c, lin, col) != -2) && (out(l+1, c, lin, col)!=-2) && maze[l-1][c]==0 && maze[l+1][c]==0){
        return 1;}
    else if ((out(l, c+1, lin, col) !=-2) && (out(l, c-1, lin, col) !=-2) && maze[l][c-1]==0 && maze[l][c+1]==0){
        return 1;}
    else {
        return 0;}
}

 int FA6 (short** maze, int l, int c, int lin, int col, int l2, int c2,short fim) {
        maze[l][c] = -6;
        if(maze[l2][c2] != -6){
            if((lin >= l+1) && (maze[l+1][c] == 0) && (fim == 0)){ /*cima*/
                fim = FA6(maze, l+1, c, lin, col, l2, c2, fim);}
            if((col >= c+1) && (maze[l][c+1] == 0 && fim == 0)){ /*direita*/
                fim = FA6(maze, l, c+1, lin, col, l2, c2, fim);
                }
            if((l >= 1) && (maze[l-1][c] == 0 && fim == 0)){      /*baixo*/
                fim = FA6(maze, l-1, c, lin, col, l2, c2,fim);
                }
            if((c >= 1) && (maze[l][c-1] == 0 && fim == 0)){      /*esquerda*/
                fim = FA6(maze, l, c-1, lin, col, l2, c2,fim);
                }
            if(fim==0){
                return 0;
                }
            else{
                return 1;
            }
        }
        else {
            return 1;
            }
 }