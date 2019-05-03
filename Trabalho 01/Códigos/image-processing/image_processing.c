#include <stdio.h>
#include <stdlib.h>

int main(){

    // clock_t start, stop;
    // start = clock(); 

    int i,j,y,x;
    unsigned char byte[54];
    int height = 512;
    int width = 512;
    float kernel[3][3]={0.11111};
    int size = height*width;    
    unsigned char buffer[262144][3];                                
    unsigned char out[262144][3];
    
    for(i=0;i<54;i++){                                  
        byte[i] = rand()%255;                               
    }

    for(i=0;i<size;i++)                                         
    {
        buffer[i][2]=rand()%255;                                    
        buffer[i][1]=rand()%255;                                
        buffer[i][0]=rand()%255;                                
    }



    for(x=1;x<height-1;x++)
    {                   
        for(y=1;y<width-1;y++)
        {
            float sum0= 0.0;
            float sum1= 0.0;
            float sum2= 0.0;
            for(i=-1;i<=1;++i)
            {
                for(j=-1;j<=1;++j)
                {                               
                    sum0=sum0+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][0];
                    sum1=sum1+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][1];
                    sum2=sum2+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][2];
                }
            }
            out[(x)*width+(y)][0]=sum0;
            out[(x)*width+(y)][1]=sum1;
            out[(x)*width+(y)][2]=sum2;
        }
    }

    for(i=0;i<size;i++)                                         
    {
        out[i][2]=rand()%255;
        out[i][1]=rand()%255;
        out[i][0]=rand()%255;
    }
        
    // stop = clock();
    // printf("\nCLOCKS_PER_SEC = %ld\n",stop-start); //1000000
    // printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );

    printf("\n*Blur on color image*\n");

    return 0;
}