#include "A's.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"

int main(int argc, char *argv[]) {
    opterr = 0;
    int opt, tamanho = 0;
    FILE *fmaze = NULL, *fsol = NULL;
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
    open_files(fmaze,fsol,fileread,filewrite);
    Labirinto (modo,fmaze,fsol);

}




