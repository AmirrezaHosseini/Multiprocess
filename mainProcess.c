#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFF 1000

#define FINDER "./OS_Finder"
#define PLACER "./OS_Placer"
#define DECODER "./OS_Decoder"

int main(){


    FILE *f = fopen("input.txt", "r");
	if(f == NULL){
		printf("no such a file");
		return 0;
	}


    int di = 0;
	int fi = 0;
	int pi = 0;
	char c;
    char decoder_text[1000];
	char finder_text[1000];
	char placer_text[1000];


    while((c = getc(f)) != '#'){
		if(c != '\n' && c != ' '){
			decoder_text[di] = c;
			di++;		
		}
	}
    getc(f);
	getc(f);
	getc(f);  // skip ###

    while((c = getc(f)) != EOF){
		placer_text[pi] = c;
		pi++;		
		
	}

    decoder_text[di] = '\0';
	finder_text[fi] = '\0';
	placer_text[pi] = '\0';

    if(fork() == 0){
		char *args[] = {DECODER, NULL};
		execvp(args[0], args);
	}
	if(fork() == 0){
		char *args[] = {FINDER, NULL};
		execvp(args[0], args);
	}
	if(fork() == 0){
		char *args[] = {PLACER, NULL};
		execvp(args[0], args);
	}

    int fd;
	char *MainToDecoder = "MainToDecoder";
	mkfifo(MainToDecoder, 0666);
	fd = open(MainToDecoder, O_WRONLY);
	write(fd, decoder_text, di+1);
	close(fd);
    char *MainToFinder = "MainToFinder";
	mkfifo(MainToFinder, 0666);
	fd = open(MainToFinder, O_WRONLY);
	write(fd, finder_text, fi+1);
	close(fd);
    char *MainToPlacer = "MainToPlacer";
	mkfifo(MainToPlacer, 0666);
	fd = open(MainToPlacer, O_WRONLY);
	write(fd, placer_text, pi+1);
	close(fd);
    char res[2000];
	char *PlacerToMain = "PlacerToMain";
	mkfifo(PlacerToMain, 0666);
	fd = open(PlacerToMain, O_RDONLY);
	read(fd, result, 2000);

    printf("The final result : %s\n", result);


}