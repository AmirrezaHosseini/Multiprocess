#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFF 1000

#define FINDER "./finder"
#define PLACER "./Placer"
#define DECODER "./Decoder"

#define MTD "MainToDecoder"
#define MTP "MainToPlacer"
#define MTF "MainToFinder"
#define PTM "PlacerToMain"



int main(){


    FILE *f = fopen("inputCode.txt", "r");
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


    pid_t process_a;
    pid_t process_b;
    pid_t process_c;

    int status;

    process_a = fork();
    if (process_a > 0) {
        process_b = fork();
        if (process_b > 0) {
            process_c = fork();
        }
    }

    if (process_a == 0) {
        //(decoder)
        char * argv_list[2] = {DECODER, NULL};
        execv(argv_list[0], argv_list);
        
    } else if (process_b == 0) {
        //finder

        char * argv_list[2] = {FINDER, NULL};
        execv(argv_list[0], argv_list);

    } else if (process_c == 0) {
        //(placer)

        char * argv_list[2] = {PLACER, NULL};
        execv(argv_list[0], argv_list);
    } else {
        //parent

        FILE *f = fopen("inputCode.txt", "r");
	    if(f == NULL){
		printf("no such a file");
		return 0;
	    }
		while((c = getc(f)) != '#'){
		if(c != '\n' && c != ' '){
			decoder_text[di] = c;
			di++;		
		}
	    }
	//skip the ###
	    getc(f);
	    getc(f);
	    getc(f);
	//read text for finder	
	    while((c = getc(f)) != '#'){
		  if(c != '\n'){
			finder_text[fi] = c;
			fi++;		
		  } 
	    }
	//skip the ###
	    getc(f);
	    getc(f);
	    getc(f);

	//read text for placer

	    while((c = getc(f)) != EOF){
		   placer_text[pi] = c;
		   pi++;		
		
	    }
    }

    int fl;
	char *MainToDecoder = MTD;

	mkfifo(MainToDecoder, 0666);
	fl = open(MainToDecoder, O_WRONLY);
	write(fl, decoder_text, di+1);
	close(fl);
    char *MainToFinder = MTF;

	mkfifo(MainToFinder, 0666);
	fl = open(MainToFinder, O_WRONLY);
	write(fl, finder_text, fi+1);
	close(fl);
    char *MainToPlacer = MTP;

	mkfifo(MainToPlacer, 0666);
	fl = open(MainToPlacer, O_WRONLY);
	write(fl, placer_text, pi+1);
	close(fl);
    char result[2000];
	char *PlacerToMain = PTM;

	mkfifo(PlacerToMain, 0666);
	fl = open(PlacerToMain, O_RDONLY);
	read(fl, result, 2000);

    printf("The final result : %s\n", result);


}