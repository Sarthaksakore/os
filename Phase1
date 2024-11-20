#include<stdio.h>
#include<string.h>

void init();
void loadInstructionSetIntoMemory();

char M[4][100], IR[4], R[4], BUFF[40], BUFF2[4][10];
int m, IC, SI, PCI=0, DCI=0, r=0, bp=0, c=1, temp=0, x=0;
FILE *input, *output;
char line[256], job[4], line2[256];

void printMemory(){
    for(int i=0; i<100; i++){
        printf("%d  ", i);
        for(int j=0; j<4; j++){
            printf("%c ", M[j][i]);
        }
        printf("\n");
    }
}

// void serviceRequest(int x){
//     switch(x){
//         case 1:
//         //Get Data
//     }
// }

void printBuffer(){
    for(int i=0; i<10; i++){
        printf("%d   ", i);
        for(int j=0; j<4; j++){
            printf("%c ", BUFF2[j][i]);
        }
        printf("\n");
    }
}

void printBuffer1(){
    for(int i=0; i<40; i++){
        printf("%c", BUFF[i]);
    }
    printf("\n");
}

void loadInstructionToBuffer(char*s, int x, int y){
    for(int i=40*(x-y); i<40+40*(x-y); i++){
        // printf("%d\n", i);
        BUFF[i] = s[i];
    }
    printf("%s\n", s);
    loadInstructionSetIntoMemory();
    if(y > 0){
        // printf("%s\n", s);
        loadInstructionToBuffer(s, x, y-1);
    }
}

void init(){
    for(int i=0; i<4; i++){
        for(int j=0; j<100; j++){
            M[i][j] = '-';
        }
    }
    for(int i=0; i<4; i++){
        IR[i] = '-';
        R[i] = '-';
        for(int j=0; j<10; j++){
            BUFF2[j][i] = '-';
        }
    }
    for(int i=0; i<40; i++){
        BUFF[i] = '-';
    }
    m=0, SI=0, IC=0;
}

void read_file(){
    input = fopen("input.txt", "r");
    while (fgets(line, sizeof(line), input) != NULL) {
        if(PCI == 1){
            int x=0;
            for(int i=0; i<strlen(line); i++){
                if(line[i] != ' '){
                    line2[x] = line[i];
                    x++;
                }
            }
            // printf("%d", strlen(line2));

            loadInstructionToBuffer(line2, strlen(line2)/40, strlen(line2)/40);
            PCI=0;
        }

        if(DCI == 1){
            if(line[0] == '$'){
                DCI = 0;
                bp=0;
            }else{
                int j=0;
                for(int i=0; i<strlen(line); i++){
                    if(j>3){
                        j=0;
                        bp++;
                    }
                    BUFF2[j][bp] = line[i];
                    j++;
                }
                bp++;
            }
        }

        if(line[0] == '$'){
            switch(line[1]){
                case 'A':
                init();
                for(int i=0; i<4; i++){
                    job[i] = line[5+i];
                }
                PCI=1;
                break;

                case 'D':
                DCI=1;
                bp=0;
                break;

                default:
                PCI=0, DCI=0;
            }
        }
    }
}

void execute(){
    for(int i=0; i<4; i++){
        IR[i] = M[i][m];
    }
    switch(IR[0]){
        case 'G':
        //GD
        IC = (IR[2] - '0')*10 + (IR[3] - '0');

        int lf=0, e=0;
        while(lf==0){
            for(int i=0; i<4; i++){
                if(BUFF2[i][bp] != '\n'){
                    M[i][IC+e] = BUFF2[i][bp];
                }else{
                    lf = 1;
                }
            }
            bp++;
            e++;
        }
        break;

        case 'P':
        //PD
        IC = (IR[2] - '0')*10 + (IR[3] - '0');

        output = fopen("output.txt", "a");

        for(int j=0; j<10; j++){
            for(int i=0; i<4; i++){
                if(M[i][IC+j] == '\n' || M[i][IC+j] == '-'){
                    break;
                }
                fprintf(output, "%c", M[i][IC+j]);
            }
        }
        fprintf(output, "\n");
        fclose(output);

        break;

        case 'L':
        //LR
        IC = (IR[2] - '0')*10 + (IR[3] - '0');
        for(int i=0; i<4; i++){
            R[i] = M[i][IC];
        }
        break;

        case 'S':
        //SR
        IC = (IR[2] - '0')*10 + (IR[3] - '0');
        for(int i=0; i<4; i++){
            M[i][IC] = R[i];
        }
        break;

        case 'C':
        //CR
        IC = (IR[2] - '0')*10 + (IR[3] - '0');
        for(int i=0; i<4; i++){
            if(M[i][IC] != R[i]){
                c = 0;
            }
        }
        break;

        case 'B':
        //BT
        IC = (IR[2] - '0')*10 + (IR[3] - '0');
        if(c == 1){
            m = IC-1;
        }
        c=1;
        break;

        case 'H':
        return;
        break;

        default:
        // printf("Error\n");
        break;
    }
    m++;
    if(m<100){
        execute();
    }
}

void loadInstructionSetIntoMemory(){
    int y=0;

    while(BUFF[y] != '-' && y<40){
        if(temp==1){
            temp=0;
            for(int i=4-x; i<4; i++){
                M[i][m] = BUFF[i];
                y+=x;
            }
            m++;
        }else{
            M[0][m] = BUFF[y];
            // printf("%c %d %d\n", BUFF[y], y, m);

            if(BUFF[y] != 'H'){
                if(y<=36){
                    M[1][m] = BUFF[y+1];
                    M[2][m] = BUFF[y+2];
                    M[3][m] = BUFF[y+3];
                    y+=4;
                    m++;
                }else{
                    temp = 1;
                    x = 40-y;
                }
            }else{
                y++;
                m++;
            }
        }
    }

    // for(int i=0; i<40; i+=4){
    //     if(BUFF[i] == '-'){
    //         break;
    //     }
    //     M[0][m] = BUFF[i];
    //     if(BUFF[i] == 'H'){
    //         continue;
    //     }else{
    //         M[1][m] = BUFF[i+1];
    //         M[2][m] = BUFF[i+2];
    //         M[3][m] = BUFF[i+3];
    //         m++;
    //     }
    // }
    for(int i=0; i<40; i++){
        BUFF[i] = '-';
    }
}

void main(){
    read_file();
    m=0;
    // printBuffer1();
    execute();
    printMemory();
    fclose(input);
}
