#include <stdio.h> 

void optimal(int frame_size, int pages, int seq[]);

int main()
{
    int frame_size = 3;
    int seq[] = {1, 2, 3, 3, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};
    int pages = 15;
    // int pages = sizeof(seq) / sizeof(seq[0]);
    optimal(frame_size, pages, seq);
    
    return 0;
}


void optimal(int frame_size, int pages, int seq[]) {
    int flag1, flag2, flag3, m, f, k, position, max, pagefaults = 0;
    int frames[frame_size];
    int temp[frame_size];

    for(f = 0; f < frame_size; f++){
        frames[f] = -1;         //empty frame
    }

    for(m = 0; m < pages; m++) {
        
        flag1 = flag2 = 0;

        for(f = 0; f < frame_size; f++){
            if(frames[f] == seq[m]){    // page HIT
                   flag1 = flag2 = 1;
                   break;
               }
        }

        if(flag1 == 0){     // page not HIT
            for(f = 0; f < frame_size; f++){
                if(frames[f] == -1){        // empty frame
                    pagefaults++;
                    frames[f] = seq[m];
                    flag2 = 1;
                    break;
                }
            }    
        }

        if(flag2 == 0){     // miss - optimal apply
            flag3 =0;

            for(f = 0; f < frame_size; f++){
                temp[f] = -1;   // temp -1 

                for(k = m + 1; k < pages; k++){
                    if(frames[f] == seq[k]){
                        temp[f] = k;
                        break;
                    }
                }
            }

            for(f = 0; f < frame_size; f++){
                if(temp[f] == -1){  // never again
                    position = f;
                    flag3 = 1;
                    break;
                }
            }

            if(flag3 ==0){      // all appear again
                max = temp[0];
                position = 0;

                for(f = 1; f < frame_size; f++){
                    if(temp[f] > max){
                        max = temp[f];
                        position = f;
                    }
                }               
            }

            frames[position] = seq[m];
            pagefaults++;
        }

        printf("\n");
        

        for(f = 0; f < frame_size; f++){
            printf("%d\t", frames[f]);
        }
    }

    printf("\n\nTotal Page pagefaults = %d", pagefaults);
    // printf("\nTotal Hits = %d", pages-pagefaults);

}
