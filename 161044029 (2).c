#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line) {
    char *ch_iter = line; // so as not to lose beginning of line
    int counter = 0;
    // go until you see new line or null char
    while(*ch_iter != '\n' && *ch_iter != '\0') {
        ch_iter++; // next char
        counter++; // increment counter
    }
    
    return counter;
}

void copy_string(char *source, char *destination) {
    // get iterators over original pointers
    char *src_iter = source;
    char *dst_iter = destination;
    // until null char
    while (*src_iter != '\0') {
        // copy pointers
        *dst_iter = *src_iter;
        // advance to next char
        src_iter++;
        dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
    char *ch_iter = line;
    // go until you see new line
    while(*ch_iter != '\n') {
        ch_iter++; // next char
    }
    *ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
    int i;
    for(i = 0 ; i < DICT_SIZE ; i++) {
        printf("%s\n", dict[i]);
    }
}

void print_coord(int coord[DICT_SIZE][4]) {
    int i, j;
    for(i = 0 ; i < DICT_SIZE ; i++) {
        for(j = 0 ; j < 4 ; j++) {
            printf("%d ", coord[i][j]);
        }
        printf("\n");
    }
}
char rastgele(){ // returning random value
    return 97+ rand()%23 ; 
}
int compare(char str[],char str1[]){
    int lenght=get_line_size(str);
    int lenght1=get_line_size(str1);
    int i=0;
    if(lenght!=lenght1) return 0 ;
    else{
        for(i=0;i<lenght;i++){
            if(str[i]!=str1[i]) return 0;
        }
    }
    return 1;
}




void edit_dict(char * dict[DICT_SIZE] , char new_dict[][15] , int coord[DICT_SIZE][4]){ // kelimeleri yerleştirme // haritanın puzzleın yapbozumun içine kelimeleri yerleştirdigim fonksiyon
    int i;
    int y;
    int j;
    int x;
    char local[15];      
    for(i=0;i<DICT_SIZE;i++){
        for(j=0;j<15;j++){
            new_dict[i][j]=rastgele(); // ilk başta rastgele sayılarla dolduruyoruz
            //printf("%c",new_dict[i][j]);
        }
       // printf("\n");
    }
    
    for(i=0;i<15;i++){
       j=0;

        if(coord[i][1]==coord[i][3]){ //sütünlar aynıysa
            if(coord[i][0]<coord[i][2]){
                while(coord[i][0]<=coord[i][2] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    j++;
                    coord[i][0]++;
                }
            }
            else{
                while(coord[i][2]<=coord[i][0] && dict[i][j]!='\0'){
                    new_dict[coord[i][2]][coord[i][1]]=dict[i][j];
                    j++;
                    coord[i][2]++;
                }   
            }
        }
         if(coord[i][0]==coord[i][2]){ //satırlar aynıysa
            if(coord[i][1]<coord[i][3]){
                while(coord[i][1]<=coord[i][3] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    
                   
                    j++;
                    coord[i][1]++;
                }
                printf("\n");
            }
            else{
                while(coord[i][3]<=coord[i][1] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][3]]=dict[i][j];
                    j++;
                    coord[i][3]++;
                }   
            }
        }
        else if(coord[i][0]!=coord[i][2] && coord[i][1]!=coord[i][3]) { //satır ve sütünlar farklıysa
            if(coord[i][0]<coord[i][2] && coord[i][1]<coord[i][3]){ // sag asagı 
                while(coord[i][0]<=coord[i][2] && coord[i][1]<=coord[i][3] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    
                    
                    j++;
                    coord[i][0]++;
                    coord[i][1]++;
                }
            }
            else if(coord[i][0]<coord[i][2] && coord[i][3]<coord[i][1]){ // sol asagı
                while(coord[i][0]<=coord[i][2] && coord[i][3]<=coord[i][1] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    
                    
                    j++;
                    coord[i][0]++;
                    coord[i][1]--;
                }   
            }
            else if(coord[i][0]>coord[i][2] && coord[i][1]<coord[i][3]){ // sag yukarı
                while(coord[i][2]<=coord[i][0] && coord[i][1]<=coord[i][3] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    j++;
                    coord[i][1]++;
                    coord[i][0]--;
                }   
            }
            else if(coord[i][0]>coord[i][2] && coord[i][1]>coord[i][3]){ // sol yukarı
                while(coord[i][2]<=coord[i][0] && coord[i][1]>=coord[i][3] && dict[i][j]!='\0'){
                    new_dict[coord[i][0]][coord[i][1]]=dict[i][j];
                    j++;
                    coord[i][1]--;
                    coord[i][0]--;
                }   
            }
        }
    }
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            printf("|%c",new_dict[i][j]);
        }
        printf("|\n");
    }
}
void game(char puzzle[15][15],int target){ // game target = number of word data
    int x;
    int y;
    int uzunluk;
    int yedek;
    char find[DICT_SIZE];
    int i=0,result=1;
    int local=0;
    int l=0;
    // getting locations
    do{
        
        printf("Exit icin -> exit game yazın\n");
        printf("Satir giriniz ");
        scanf("%d",&x);
        while(x<0 || x>DICT_SIZE){
            printf("!! ");
            scanf("%d",&x);
        }
        printf("Sütun giriniz ");                                    // ilk [] x  ikinci [] y
        scanf("%d",&y);
        while(y<0 || y>DICT_SIZE){
            printf("!!");
            scanf("%d",&y);
        }
        
    
        printf("Enter string : ");
        scanf("%s",find);
       
        uzunluk=get_line_size(find); // find lenght
        i=0;
        if(y+uzunluk<=DICT_SIZE){
           
            while(i<uzunluk){
                if(puzzle[x][y+i]!=find[i]){
                    
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                   
                    local++;
                    result=1;
                    yedek=i;
                    for(i=0;i<=yedek;i++){
                        puzzle[x][y+i]=puzzle[x][y+i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                    
                }
                i++;
            }
        }
        i=0;
        if((y+1)-uzunluk>=0){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x][y-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x][y-i]=puzzle[x][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<15;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                  
                }
                i++;
            }
        }
        i=0;
        if((y+1)-uzunluk>=0){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x][y-i]!=find[uzunluk-i-1]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x][y-i]=puzzle[x][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                   
                }
                i++;
            }
        }i=0;
        if((x+1)-uzunluk>=0){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x-uzunluk+1+i][y]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y]=puzzle[x-i][y]-32;
                    }  
                    printf("\n");
                    for(i=0;i<15;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                  
                }
                i++;
            }
        }
        i=0;
        if(x+uzunluk<=DICT_SIZE){ 
               
            
            while(i<uzunluk){
                if(puzzle[x+i][y]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    for(i=0;i<=yedek;i++){
                        puzzle[x+i][y]=puzzle[x+i][y]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
           
                }
                i++;
            }
        }
        i=0;
        if((x+1)-uzunluk>=0){
            
             while(i<uzunluk){

                if(puzzle[x][y-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x][y-i]=puzzle[x][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                 
                }
                i++;
            }
        }
        i=0;
        if(x+1-uzunluk>=0){
            
            while(i<uzunluk){
                if(puzzle[x-i][y]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y]=puzzle[x-i][y]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
              
                }
                i++;
            }
        }
        i=0;
        if(y+uzunluk<=DICT_SIZE){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x][y+uzunluk-i-1]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    for(i=0;i<=yedek;i++){
                        puzzle[x][y+uzunluk-i-1]=puzzle[x][y+uzunluk-i-1]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                }
                i++;
            }
        }
        i=0;
        if(x+uzunluk<=DICT_SIZE){ // tersten okuma
           
            while(i<uzunluk){
                if(puzzle[x+uzunluk-i-1][y]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x+uzunluk-i-1][y]=puzzle[x+uzunluk-1-i][y]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                   
                }
                i++;
            }
        }i=0;
        if(x+uzunluk<=DICT_SIZE && y+uzunluk<=DICT_SIZE){ // sağ aşağı
            
            while(i<uzunluk){
                if(puzzle[x+i][y+i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x+i][y+i]=puzzle[x+i][y+i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                    
                }
                i++;
                
            }
        }
            i=0;
            if(x+uzunluk<=DICT_SIZE && y-uzunluk>=0){ // sol asagı
            
            while(i<uzunluk){
                if(puzzle[x+i][y-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x+i][y-i]=puzzle[x+i][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                   
                }
                i++;
                
            }

        }
        i=0;
        if(x-uzunluk>=0 && y+uzunluk<=DICT_SIZE){ // sag yukarı
            
            while(i<uzunluk){
                if(puzzle[x-i][y+i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y+i]=puzzle[x-i][y+i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                   
                }
                i++;
                
            }

        }
        i=0;
        if(x-uzunluk>=0 && y-uzunluk>=0){ // sol yukarı
           
            while(i<uzunluk){
                if(puzzle[x-i][y-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    result=1;
                    yedek=i;
                    local++;
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y-i]=puzzle[x-i][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }

                   
                }
                i++;
                
            }

        }
        i=0;
        if((x+1)-uzunluk>=0 && y+1-uzunluk>=0){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x-uzunluk+1+i][y-uzunluk+1+i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y-i]=puzzle[x-i][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                    
                }
                i++;
            }
        }
        i=0;
        if((x+1)-uzunluk>=0 && y+uzunluk<=DICT_SIZE){ // tersten okuma
           
            while(i<uzunluk){
                if(puzzle[x-uzunluk+1+i][y+uzunluk-1-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x-i][y+i]=puzzle[x-i][y+i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                    
                }
                i++;
            }
        }
        i=0;
        if(x+uzunluk<=DICT_SIZE && y+uzunluk<=DICT_SIZE){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x+uzunluk-1-i][y+uzunluk-1-i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x+i][y+i]=puzzle[x+i][y+i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                   
                }
                i++;
            }
        }
        if(x+uzunluk<=DICT_SIZE && y-uzunluk+1+i>=0){ // tersten okuma
            
            while(i<uzunluk){
                if(puzzle[x+uzunluk-1-i][y-uzunluk+1+i]!=find[i]){
                    result=0;
                    i=16;
                }
                else if(i==uzunluk-1){
                    local++;
                    result=1;
                    yedek=i;
                    
                    for(i=0;i<=yedek;i++){
                        puzzle[x+i][y-i]=puzzle[x+i][y-i]-32;
                    }  
                    printf("\n");
                    for(i=0;i<DICT_SIZE;i++){
                        for(int j=0;j<DICT_SIZE;j++){
                            printf("|%c",puzzle[i][j]);
                        }
                       printf("|\n");
                    }
                   
                }
                i++;
            }
        }




        
    }while(compare(find,"exit")!=1 && local!=target);
    if(local==target){
        printf("Found all words hah");
    }






}



int main(){
    char *dict[DICT_SIZE];
    char new_dict[DICT_SIZE][DICT_SIZE];
    int coord[DICT_SIZE][4];    
    int i=0;
    char line[LINE_LEN];
    FILE *fp = fopen("word_hunter.dat", "r");
    
    int line_counter = 0;
    int dict_counter = 0;
    srand(time(NULL));
    while(fgets(line, LINE_LEN, fp) != NULL) {
    //  printf("%s\n",line);
        if(line_counter%5 == 0) {
            dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
            i++;
            remove_newline(line);
            copy_string(line, dict[dict_counter]);
        } else if (line_counter%5 == 1){
            coord[dict_counter][0] = atoi(line);
        } else if (line_counter%5 == 2){            
            coord[dict_counter][1] = atoi(line);        
        } else if (line_counter%5 == 3){
            coord[dict_counter][2] = atoi(line);
        } else if (line_counter%5 == 4){
            coord[dict_counter][3] = atoi(line);
            dict_counter++;
        }
        line_counter++;
    }
    
    fclose(fp);
    edit_dict(dict,new_dict,coord);;
    game(new_dict,i);
    //print_dictionary(dict);
    //print_coord(coord);
    
    // WRITE HERE...
        
    return 0;
}



