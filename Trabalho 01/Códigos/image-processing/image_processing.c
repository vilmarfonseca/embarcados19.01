#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void black_white(){

	clock_t start, stop;
	start = clock();	

	FILE *fIn = fopen("lena512.bmp","r");				//Input File name
	FILE *fOut = fopen("b_w.bmp","w+");		            //Output File name

	int THRESHOLD = 128;
	int WHITE = 255;
	int BLACK = 0;
	int i;
	unsigned char byte[54];								//to get the image header
	unsigned char colorTable[1024];						//to get the colortable

	if(fIn==NULL)										// check if the input file has not been opened succesfully.
	{										
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)									//read the 54 byte header from fIn
	{									
		byte[i]=getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);			//write the header back

	// extract image height, width and bitDepth from imageHeader 
	int height = 512;
	int width = 512;
	int bitDepth = 8;

	int size=height*width;								//calculate image size

	if(bitDepth<=8)										//if ColorTable present, extract it.
	{
		fread(colorTable,sizeof(unsigned char),1024,fIn);
		fwrite(colorTable,sizeof(unsigned char),1024,fOut);
	}

	unsigned char buffer[size];							//to store the image data

	fread(buffer,sizeof(unsigned char),size,fIn);		//read image data

	for(i=0;i<size;i++)									//store 0(black) and 255(white) values to buffer 
		{
			buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
		}
	
	fwrite(buffer,sizeof(unsigned char),size,fOut);		//write back to the output image

	fclose(fIn);
	fclose(fOut);
	stop = clock();
	printf("\nCLOCKS_PER_SEC = %ld\n",stop-start); //1000000
	printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );
	printf("\n*Black and White image*\n");
}

void image_blur_color(){

	clock_t start, stop;
	start = clock();	

	FILE *fIn = fopen("lena_color.bmp","r");					//Input File name
	FILE *fOut = fopen("lena_blur_color.bmp","w+");		    		//Output File name

	int i,j,y,x;
	unsigned char byte[54];
	
	if(fIn==NULL)												// check if the input file has not been opened succesfully.
	{											
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)											//read the 54 byte header from fIn
	{									
		byte[i] = getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);					//write the header back

	int height = 512;
	int width = 512;
	int bitDepth = 8;

	int size = height*width;									//calculate the image size

	unsigned char buffer[size][3];								//store the input image data
	unsigned char out[size][3];									//store the output image data

	for(i=0;i<size;i++)											//read image data character by character
	{
		buffer[i][2]=getc(fIn);									//blue
		buffer[i][1]=getc(fIn);									//green
		buffer[i][0]=getc(fIn);									//red
	}

	float v=1.0 / 9.0;											//initialize the blurrring kernel
	float kernel[3][3]={{v,v,v},
						{v,v,v},
						{v,v,v}};

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
				{								//matrix multiplication with kernel with every color plane
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

	for(i=0;i<size;i++)											//write image data back to the file
	{
		putc(out[i][2],fOut);
		putc(out[i][1],fOut);
		putc(out[i][0],fOut);
	}
		
	fclose(fOut);
	fclose(fIn);

	stop = clock();
	printf("\nCLOCKS_PER_SEC = %ld\n",stop-start); //1000000
	printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );

	printf("\n*Blur on color image*\n");
}

void image_bright(){
	
	int MAX_COLOR = 255;
	int BRIGHTNESS_FACTOR = 25;

	FILE *fIn = fopen("lena512.bmp","r");			//Input File name
	FILE *fOut = fopen("lena_bright.bmp","w+");	    	//Output File name

	int i;
	unsigned char byte[54],colorTable[1024];
	
	if(fIn==NULL)						// check if the input file has not been opened succesfully.
	{											
		printf("File does not exist.\n");
		exit(1);
	}

	for(i=0;i<54;i++)					//read the 54 byte header from fIn
	{									
		byte[i] = getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);		//write the header back

	// extract image height, width and bitDepth from imageHeader 
	int height = 512;
	int width = 512;
	int bitDepth = 8;

	// printf("width: %d\n",width);
	// printf("height: %d\n",height );

	int size = height*width;				//calculate image size

	if(bitDepth <= 8)					//if ColorTable present, extract it.
	{
		fread(colorTable,sizeof(unsigned char),1024,fIn);
		fwrite(colorTable,sizeof(unsigned char),1024,fOut);
	}

	
	unsigned char buffer[size];				//to store the image data
	int temp;

	fread(buffer,sizeof(unsigned char),size,fIn);		//read image data

	for(i=0;i<size;i++)					//increasing pixel values to get image bright
	{
		temp = buffer[i] + BRIGHTNESS_FACTOR;
		buffer[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp;
	}
	
	fwrite(buffer,sizeof(unsigned char),size,fOut);		//write back to the output image

	fclose(fIn);
	fclose(fOut);
	printf("\n*Bright Image*\n");
}

void image_colortosepia(){

	int MAX_VALUE = 255;

	clock_t start, stop;

	start = clock();											// Note the start time for profiling purposes.

	FILE *fIn = fopen("lena_color.bmp","r");					//Input File name
	FILE *fOut = fopen("lena_sepia.bmp","w+");		    		//Output File name

	int i,r,g,b;
	unsigned char byte[54];
	
	if(fIn==NULL)												// check if the input file has not been opened succesfully.
	{											
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)											//read the 54 byte header from fIn
	{									
		byte[i] = getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);					//write the header back

	// extract image height, width and bitDepth from imageHeader 
	int height = 512;
	int width = 512;
	int bitDepth = 8;

	int size = height*width;									//calculate image size

	unsigned char buffer[size][3];								//to store the image data

	for(i=0;i<size;i++){
		r = 0;
		g = 0;
		b = 0;
		buffer[i][2] = getc(fIn);									//blue
		buffer[i][1] = getc(fIn);									//green
		buffer[i][0] = getc(fIn);									//red

		//conversion formula of rgb to sepia
		r = (buffer[i][0]*0.393) + (buffer[i][1]*0.769)	+ (buffer[i][2]*0.189);
		g = (buffer[i][0]*0.349) + (buffer[i][1]*0.686)	+ (buffer[i][2]*0.168);
		b = (buffer[i][0]*0.272) + (buffer[i][1]*0.534)	+ (buffer[i][2]*0.131);

		if(r > MAX_VALUE){											//if value exceeds
			r = MAX_VALUE;
		}
		if(g > MAX_VALUE){
			g = MAX_VALUE;
		}
		if(b > MAX_VALUE){
			b = MAX_VALUE;
		}
		putc(b,fOut);
		putc(g,fOut);
		putc(r,fOut);
		
	}
	
		
	fclose(fOut);
	fclose(fIn);

	stop = clock();
	// printf("\nCLOCKS_PER_SEC = %ld\n",stop-start); 
	// printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );
	printf("\n*Color to Sepia*\n");
}

void image_rotate(){

	clock_t start, stop;
	start = clock();	

	FILE *fIn = fopen("lena512.bmp","r");					//Input File name
	FILE *fOut = fopen("lena_rotate.bmp","w+");		    	//Output File name

	int i,j,choice;
	unsigned char byte[54],colorTable[1024];
	
	if(fIn==NULL)											// check if the input file has not been opened succesfully.
	{											
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)										//read the 54 byte header from fIn
	{									
		byte[i] = getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);				//write the header back

	int height = 512;
	int width = 512;
	int bitDepth = 8;

	int size = height*width;								//calculate image size

	if(bitDepth <= 8)										//if ColorTable present, extract it.
	{
		fread(colorTable,sizeof(unsigned char),1024,fIn);
		fwrite(colorTable,sizeof(unsigned char),1024,fOut);
	}

	unsigned char buffer[width][height];					//to store the image data
	unsigned char out_buffer[width][height];

	fread(buffer,sizeof(unsigned char),size,fIn);			//read the image data

	printf("\n*Upside down image*\n");

	for(i=0;i<width;i++)								//to rotate 180 degree
	{
		for(j=0;j<height;j++)
		{
			out_buffer[width-i][j]=buffer[i][j];
		}
	}
	
	fwrite(out_buffer,sizeof(unsigned char),size,fOut);		//write back to the output image

	fclose(fIn);
	fclose(fOut);

	stop = clock();
	printf("\nCLOCKS_PER_SEC = %ld\n",stop-start); //1000000
	printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );
}

int main(){

	// black_white();
	image_blur_color();
	// image_bright();
	// image_colortosepia();
	// image_rotate();

	return 0;
}