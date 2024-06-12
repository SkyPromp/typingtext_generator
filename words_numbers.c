#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define WORDS_AMOUNT 145 // make dynamic by using index
#define MAX_WORD_LENGTH 100
#define MIN_NUMBER_LENGTH 2
#define MAX_NUMBER_LENGTH 5
#define NUMBERS_RATIO 0.3
#define TOKENS 25

typedef enum text_type{
	WORD,
	NUMBER
} text_type;

int getNumber();
char *getWord();
text_type next();
void outputData(char [][MAX_WORD_LENGTH]);


int main(){
	srand(time(NULL));
	FILE *fptr = fopen("words.txt", "r");
	char words[WORDS_AMOUNT][MAX_WORD_LENGTH];
	char word[MAX_WORD_LENGTH];
	size_t index = 0;

	while(fgets(word, MAX_WORD_LENGTH, fptr)){ 
		word[strcspn(word, "\n")] = 0; // Remove newline at the end of word
		if (!*word) break;

		strcpy(words[index++], word);
	}

	for(int i = 0; i < TOKENS - 1; i++) {
		outputData(words);
		putchar(' ');
	}

	outputData(words);

	fclose(fptr);

	return 0;
}

int getNumber(){
	const int digits = rand() % ((MAX_NUMBER_LENGTH + 1 - MIN_NUMBER_LENGTH)) + MIN_NUMBER_LENGTH;

	if (digits == 1) return (rand() % 10);

	int number = rand() % 9 + 1; // First number not 0
	
	for(int i = 1; i < digits; i++) {
		number *= 10;
		int r = rand() % 10; 
		number += r;
	}

	return number;
}

char *getWord(){
	return "hoi";
}

text_type next(){
	const int percent = RAND_MAX * NUMBERS_RATIO;
	int value = rand();

	if (value > percent) return WORD;

	return NUMBER;
}

void outputData(char words[][MAX_WORD_LENGTH]){
	int token = next();

	switch (token){
		case WORD:

			printf("%s", words[rand() % WORDS_AMOUNT]);
			break;
		case NUMBER:
			printf("%d", getNumber());
			break;
		default:
			printf("Unexpected type token: %d", token);
	}
}
