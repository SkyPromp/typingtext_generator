#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MIN_NUMBER_LENGTH 2
#define MAX_NUMBER_LENGTH 5
#define NUMBERS_RATIO 0.3
#define TOKENS 25

typedef enum text_type{
	WORD,
	NUMBER
} text_type;

size_t getFileLines(char*, size_t*);
int getNumber();
char *getWord();
text_type next();
void outputData(size_t max_word_length, char [][max_word_length], size_t);


int main(){
	srand(time(NULL));
	char *file_name = "words.txt";
	size_t MAX_WORD_LENGTH = 0;
	const size_t FILE_LINES = getFileLines(file_name, &MAX_WORD_LENGTH);
	MAX_WORD_LENGTH++;

	FILE *fptr = fopen(file_name, "r");
	char words[FILE_LINES][MAX_WORD_LENGTH];
	char word[MAX_WORD_LENGTH];
	size_t index = 0;

	while(fgets(word, MAX_WORD_LENGTH, fptr)){ 
		word[strcspn(word, "\n")] = 0; // Remove newline at the end of word
		if (!*word) break;

		strcpy(words[index++], word);
	}

	for(int i = 0; i < TOKENS - 1; i++) {
		outputData(MAX_WORD_LENGTH, words, FILE_LINES);
		putchar(' ');
	}

	outputData(MAX_WORD_LENGTH, words, FILE_LINES);

	fclose(fptr);

	return 0;
}

size_t getFileLines(char* file_name, size_t *max_word_length){
	FILE *fptr = fopen(file_name, "r");
	const size_t MAX_BUFFER_SIZE = 100; // bigger than max word length
	char word[MAX_BUFFER_SIZE]; // overshoot max word length
	size_t index = 0;

	while(fgets(word, MAX_BUFFER_SIZE, fptr)){ 
		size_t word_length = strlen(word);
		if (word_length > *max_word_length) *max_word_length = word_length;

		word[strcspn(word, "\n")] = 0; // Remove newline at the end of word
		if (!*word) break;
		
		index++;
	}

	fclose(fptr);

	return index;
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

void outputData(size_t max_word_length, char words[][max_word_length], size_t words_amount){
	int token = next();

	switch (token){
		case WORD:

			printf("%s", words[rand() % words_amount]);
			break;
		case NUMBER:
			printf("%d", getNumber());
			break;
		default:
			printf("Unexpected type token: %d", token);
	}
}
