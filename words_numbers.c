#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum text_type{
	WORD,
	NUMBER
} text_type;

typedef struct format_data{
	char FILE_NAME[255];
	int MIN_NUMBER_LENGTH;
	int MAX_NUMBER_LENGTH;
	float NUMBERS_RATIO;
	int TOKENS;
} format_data;

void logData(format_data*);
size_t getFileLines(char*, size_t*);
int getNumber(int, int);
char *getWord();
text_type next(float);
void outputData(size_t max_word_length, char [][max_word_length], size_t, format_data*);


int main(int argc, char *argv[]){
	format_data *data;
	data = (format_data *)malloc(sizeof(format_data));
	
	strcpy(data->FILE_NAME, "words.txt");
	data->MIN_NUMBER_LENGTH = 2;
	data->MAX_NUMBER_LENGTH = 5;
	data->NUMBERS_RATIO = 0.3;
	data->TOKENS = 25;

	int TOKENS = 25;
	if(argc == 2) strcpy(data->FILE_NAME, argv[1]);
	if(argc == 5){
		data->MIN_NUMBER_LENGTH = atoi(argv[1]);
		data->MAX_NUMBER_LENGTH = atoi(argv[2]);
		data->NUMBERS_RATIO = atof(argv[3]);
		data->TOKENS = atoi(argv[4]);
	}
	if(argc == 6){
		strcpy(data->FILE_NAME, argv[1]);
		data->MIN_NUMBER_LENGTH = atoi(argv[2]);
		data->MAX_NUMBER_LENGTH = atoi(argv[3]);
		data->NUMBERS_RATIO = atof(argv[4]);
		data->TOKENS = atoi(argv[5]);
	}

	srand(time(NULL));
	size_t MAX_WORD_LENGTH = 0;
	const size_t FILE_LINES = getFileLines(data->FILE_NAME, &MAX_WORD_LENGTH);
	MAX_WORD_LENGTH++;

	FILE *fptr = fopen(data->FILE_NAME, "r");
	char words[FILE_LINES][MAX_WORD_LENGTH];
	char word[MAX_WORD_LENGTH];
	size_t index = 0;

	while(fgets(word, MAX_WORD_LENGTH, fptr)){ 
		word[strcspn(word, "\n")] = 0; // Remove newline at the end of word
		if (!*word) break;

		strcpy(words[index++], word);
	}

	for(int i = 0; i < data->TOKENS - 1; i++) {
		outputData(MAX_WORD_LENGTH, words, FILE_LINES, data);
		putchar(' ');
	}

	outputData(MAX_WORD_LENGTH, words, FILE_LINES, data);

	fclose(fptr);

	return 0;
}

void logData(format_data *data){
	printf("\n%s\n", data->FILE_NAME);
	printf("%d\n", data->MIN_NUMBER_LENGTH);
	printf("%d\n", data->MAX_NUMBER_LENGTH);
	printf("%f\n", data->NUMBERS_RATIO);
	printf("%d\n", data->TOKENS);
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

int getNumber(int MIN_NUMBER_LENGTH, int MAX_NUMBER_LENGTH){
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

text_type next(float NUMBERS_RATIO){
	const int percent = RAND_MAX * NUMBERS_RATIO;
	int value = rand();

	if (value > percent) return WORD;

	return NUMBER;
}

void outputData(size_t max_word_length, char words[][max_word_length], size_t words_amount, format_data *data){
	int token = next(data->NUMBERS_RATIO);

	switch (token){
		case WORD:

			printf("%s", words[rand() % words_amount]);
			break;
		case NUMBER:
			printf("%d", getNumber(data->MIN_NUMBER_LENGTH, data->MAX_NUMBER_LENGTH));
			break;
		default:
			printf("Unexpected type token: %d", token);
	}
}
