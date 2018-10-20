#include "./define.h"
int read_conect(char file_name[260]){
    FILE *fp00;
    fp00 = fopen(file_name, "r");

    //erro////////////////////////
    if( fp00 == NULL ) {
        perror("ERRO\n");
        return 1;
    }
    //read-conect_id[]///////////////////
    char str[20];
    int i=1;
    int temp=1;
    int c_temp;

    for(int a=0;a<20;a++){
        conect[0][a]=0;
    }
    num[0]=20;
    while( ( fgets(str,20,fp00) ) != NULL ){
        c_temp = atoi(str);
        if(c_temp!=9999){
            conect[i][temp] = c_temp;
        }
        temp=temp+1;
        if (c_temp==9999){
            num[i]=temp-1;
            i=i+1;
            temp=1;
        }
    }
    fclose(fp00);
}