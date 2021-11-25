#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MTD "MainToDecoder"
#define MTP "MainToPlacer"
#define MTF "MainToFinder"
#define DTF "DecoderToFinder"



int main()
{
	
	char text[1000];
	int fd1;

	char *MainToDecoder = MTD;
	mkfifo(MainToDecoder, 0666);
	fd1 = open(MainToDecoder, O_RDONLY);
	read(fd1, text, 1000);
	
	int i = 0;




	while(text[i] != '\0'){
		if(text[i] >= 'A' && text[i] <= 'Z'){
			if(text[i] == 'A'){
				text[i] = 'X';
			}			
			else if(text[i] == 'B'){
				text[i] = 'Y';
			}
			else if(text[i] == 'C'){
				text[i] = 'Z';
			}
			else{
				text[i] -= 3;
			}
			
		}
		if(text[i] >= 'a' && text[i] <= 'z'){
			if(text[i] == 'a'){
				text[i] = 'x';
			}			
			else if(text[i] == 'b'){
				text[i] = 'y';
			}
			else if(text[i] == 'c'){
				text[i] = 'z';
			}
			else{
				text[i] -= 3;
			}		
		}
		i++;
	}


	
	char *DecoderToFinder = DTF;
	mkfifo(DecoderToFinder, 0666);
	fd1= open(DecoderToFinder, O_WRONLY);
	write(fd1, text, i+1);
	close(fd1);

	FILE *f = fopen("decoder.txt", "w");
	fprintf(f, "%s", text);
	
	
}