#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


#define MTP "MainToPlacer"
#define MTF "MainToFinder"
#define DTF "DecoderToFinder"
#define FTP "FinderToPlacer"
#define PTM "PlacerToMain"



int main()
{
	

	char text[1000];
	int fd;
	char *MainToPlacer = MTP;
	mkfifo(MainToPlacer, 0666);
	fd = open(MainToPlacer, O_RDONLY);
	read(fd, text, 1000);
	
	

	char words[1000];
	char *FinderToPlacer = FTP;
	mkfifo(FinderToPlacer, 0666);
	fd = open(FinderToPlacer, O_RDONLY);
	read(fd, words, 1000);
	


	char answer[2000];
	int n = 0;	
	int j = 0;
	for(int i = 0; text[i] != '\0'; i++){
		
		if(text[i] == '$'){
			while(words[j] != ' '){
				answer[n] = words[j];
				n++;
				j++;
			}
			j++;
		}
		else{
			answer[n] = text[i];
			n++;
		}
	}
	
	answer[n] = '\0';
	
	// send result to Main


	char *PlacerToMain = PTM;
	mkfifo(PlacerToMain, 0666);
	fd = open(PlacerToMain, O_WRONLY);
	write(fd, answer, n+1);
	close(fd);

	// file

	FILE *f = fopen("placer.txt", "w");
	fprintf(f, "%s", answer);

}