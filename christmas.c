#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define COLOR_COUNT 7
const char *colors[] = {
	"\033[31m", // 빨강
	"\033[32m", // 초록
	"\033[33m", // 노랑
	"\033[34m", // 파랑
	"\033[35m", // 보라
	"\033[36m", // 청록
	"\033[37m"  // 흰색
};

const char *ascii_art[] = {
	"___  ___                           _____  _            _       _                          ",
	"|  \\/  |                          /  __ \\| |          (_)     | |                         ",
	"| .  . |  ___  _ __  _ __  _   _  | /  \\/| |__   _ __  _  ___ | |_  _ __ ___    __ _  ___ ",
	"| |\\/| | / _ \\| '__|| '__|| | | | | |    | '_ \\ | '__|| |/ __|| __|| '_ ` _ \\  / _` |/ __|",
	"| |  | ||  __/| |   | |   | |_| | | \\__/\\| | | || |   | |\\__ \\| |_ | | | | | || (_| |\\__ \\",
	"\\_|  |_/ \\___||_|   |_|    \\__, |  \\____/|_| |_||_|   |_||___/ \\__||_| |_| |_| \\__,_||___/ ",
	"                            __/ |                                                         ",
	"                           |___/                                                           "
};

void print_colored_ascii_art()
{
	srand(time(NULL));

	int random = 0;

	for (int i = 0; i < 8; i++) {
		const char* line = ascii_art[i];
		for (int j = 0; line[j] != '\0'; j++) {
			random = rand() % 7;
			printf("%s%c", colors[random], line[j]);
		}
		printf("\n");
	}
	printf("\033[0m"); // 색상 초기화
}

#define REPEAT_SIZE 10
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
void print_christmas_tree(int line)
{
	for (int i = 0; i < REPEAT_SIZE; i++) {
		const char *color = ((line+i) % 2 == 0) ? RED : GREEN;
		printf("%s", color);

		for (int j = 0; j < REPEAT_SIZE - i - 1; j++) {
			printf(" ");
		}
		
		for (int j = 0; j < i + 1; j++) {
			printf("*");
			if (j < i)
					printf(".");
		}
		
		printf("\n");
	}

	for (int i = 0; i < 8; i++) {
		printf(" ");
	}

	printf("\033[38;5;94m***\n");
}

int main()
{
	int line = 0;

	while (1) {
		system("clear");
		print_christmas_tree(line);
		printf("\n\n");
		print_colored_ascii_art();
		usleep(700000);
		line++;
	}

	return 0;
}
