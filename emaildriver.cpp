#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void to_lowercase(char *str);
void crash(const char *message);
char *remove_spaces(const char *str);

int main(int argc, char **argv) {
	if(argc < 7)
		crash("Missing parameters.");

	char email[100];
	char festival[100];
	char *option;
	char quantity[5];

	for(int i = 1; i < argc; ++i) {
		if(argv[i][0] == '-') {
			option = *(argv+i)+1;
			to_lowercase(option);
			continue;
		}
		if(strcmp(option, "email") == 0 || strcmp(option, "e") == 0) {
			to_lowercase(argv[i]);
			if(strcmp(argv[i], "o") == 0 || strcmp(argv[i], "orders") == 0)
				strcpy(email, "orders@peachskinsheets.com");
			else if(strcmp(argv[i], "r") == 0 || strcmp(argv[i], "receipts") == 0)
				strcpy(email, "receipts@peachskinsheets.com");
			else
				crash("Invalid email address!");
		}
		if(strcmp(option, "quantity") == 0 || strcmp(option, "q") == 0)
			strcpy(quantity, argv[i]);
		if(strcmp(option, "festival") == 0 || strcmp(option, "f") == 0) {
			strcat(festival, argv[i]);
			strcat(festival, " ");
		}
	}

	festival[strlen(festival)-1] = '\0';

	char command[500];
	char *filename = remove_spaces(festival);
	sprintf(command, "phantomjs entry.js %s \"%s\" %s >> %s.csv; open -a /Applications/Numbers.app/ %s.csv", email, festival, quantity, filename, filename);
	system(command);

	exit(0);
}

char *remove_spaces(const char *str) {
	char temp[strlen(str)+1];
	memcpy(temp, str, strlen(str)+1);
	for(int k = 0; k < strlen(temp); k++)
		if(temp[k] == ' ')
			memcpy((void*)(temp+k), (void*)(temp+k+1), strlen(temp)-k+1);
	return temp;
}

void to_lowercase(char *str) {
	for(; *str; str++)
		*str = tolower(*str);
}

void crash(const char *message) {
	printf("%s\n", message);
	exit(-1);
}