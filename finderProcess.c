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
#define FTP "FinderToPlacer"





int main()
{
	//Maintodecoder read


	char text[1000];
	int fd1;
	char *MainToFinder = MTF;

	mkfifo(MainToFinder, 0666);
	fd1 = open(MainToFinder, O_RDONLY);
	read(fd1, text, 1000);
		
	//read from decoder


	char decode[1000];
	char *DecoderToFinder = DTF;
	mkfifo(DecoderToFinder, 0666);
	fd1 = open(DecoderToFinder, O_RDONLY);
	read(fd1, decode, 1000);
	
	char words[1000];
	int wi = 0;
	int i = 0;
	int l = 0;
	int r = 0;
	int index = 0;
	int len = 0;
	


	while(text[i] != '\0'){
		l = i;
		index = 0;
		len = 0;
		while(text[i] != ' '){
			i++;
		}
		r = i;
		i++;
		for(int j = l; j < r; j++){
			index *= 10;
			index += (text[j] - '0');
		}	
		l = i;		
		while(text[i] != '$'){
			i++;
		}
		r = i;
		i++;
		for(int j = l; j < r; j++){
			len *= 10;
			len += (text[j] - '0');
		}	
		
		for(int j = index; j < index + len; j++){
			
			words[wi] = decode[j];
			wi++;
		}
		words[wi] = ' ';
		wi++;
	}


	words[wi] = '\0';

	char *FinderToPlacer = FTP;

	mkfifo(FinderToPlacer, 0666);

	fd1 = open(FinderToPlacer, O_WRONLY);
	write(fd1, words, wi+1);
	close(fd1);

	// write to file
	FILE *f = fopen("finder.txt", "w");
	fprintf(f, "%s", words);
	
}