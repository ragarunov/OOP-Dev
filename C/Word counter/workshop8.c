/*
Workshop #8

Ronen Agarunov
Student I.D #: 029490158

A program that counts the number of words in a string
*/

#include <stdio.h>
#include <string.h>

void wordCount (char str[], int word) {

	int i;
	int length;

	length = strlen(str);

	for (i = 0; i < length; i++) {

		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r') {

			word++;

			while (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r') {

				i++;

			}
		
		}

	}

	printf("Word Count 	: %d", word);
	
}

int main (void) {

	char str[101];
	int word = 0;

	printf("Word Counter\n");
	printf("============\n");
	printf("Text to be analyzed : ");
	gets_s(str,101);
	wordCount(str, word);

	return 0;
	
}