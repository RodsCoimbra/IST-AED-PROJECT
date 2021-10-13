#include "Ficheiros_dados.h"

void Labirinto (char* modo, FILE* fmaze, FILE* fsol){ // confirmar se é void
    int lin = 0, col = 0, parede, l=0, c=0,linaux=-2, colaux = -1,l2 = 0, c2 = 0, resposta;
    short** maze = NULL;
    while (1){
        if (fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo) != 5) {
            if(feof(fmaze) != 0) break;
            else{
            fechar(fmaze, fsol);}}
        if((strcmp(modo,"A6"))!=0)
        {
            if(fscanf(fmaze,"%d", &parede) !=1){
                fechar(fmaze,fsol);}
        }
        else
        {
            if(fscanf(fmaze,"%d %d %d",&l2, &c2, &parede) != 3){
                fechar(fmaze,fsol);}
        } 
    if(lin != linaux){
        if(linaux != -2){
        freetabela(maze, linaux);}
        linaux=lin;
        colaux=-1;
        short** maze =(short**) malloc (lin*sizeof(short*));
        if (maze == NULL){ 
            exit(0);
        }
    }
    if(col != colaux){
        if(colaux != -1){
            for (int i=0; i < linaux;i++){   
            free(maze[i]);
            }
        }
    for (int i=0; i < lin;i++){
        maze[i]=(short*) calloc (1, col*sizeof(short));
        if(maze[i] == NULL){
            exit(0);
        }
    } 
    colaux = col;
    }
    else{
        for(int i=0; i < lin; i++){
            for(int j=0; j < col; j++){
                maze[i][j] = 0;}
        }
    }

    for(int i=0, l1, c1, custo; i < parede; i++){
        if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo)!= 3){
            fechar(fmaze,fsol);}
        maze[l1-1][c1-1] = custo;
        }
    resposta = mod(maze, l-1, c-1, lin-1, col-1, modo, l2-1, c2-1);
    fprintf(fsol,"%d\n\n", resposta);
    }
    freetabela(maze, lin);
    fechar(fmaze,fsol);
}

void open_files(FILE* fmaze,FILE* fsol,char* fileread,char* filewrite){
    if((fmaze = fopen(fileread, "r")) == NULL)
{
    free(filewrite);
    free(fileread);
    exit(0);
}
separar(fileread);
sscanf(fileread, " %s", filewrite);
strcat(filewrite,".sol1");  //apenas para teste, garantir que MUDAMOS PARA SOL1!!!!!!
if ((fsol = fopen(filewrite, "w")) == NULL){ // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha
        free(filewrite);
        free(fileread);
        fclose(fmaze);
        exit(0);
        }
free(filewrite);
free(fileread);
}
