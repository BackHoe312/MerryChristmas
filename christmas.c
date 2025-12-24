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

#define DIGIT_H 5
const char *DIGITS[10][DIGIT_H] = {
	{"███", "█ █", "█ █", "█ █", "███"}, // 0
	{" ██", "  █", "  █", "  █", " ███"}, // 1
	{"███", "  █", "███", "█  ", "███"}, // 2
	{"███", "  █", "███", "  █", "███"}, // 3
	{"█ █", "█ █", "███", "  █", "  █"}, // 4
	{"███", "█  ", "███", "  █", "███"}, // 5
	{"███", "█  ", "███", "█ █", "███"}, // 6
	{"███", "  █", "  █", "  █", "  █"}, // 7
	{"███", "█ █", "███", "█ █", "███"}, // 8
	{"███", "█ █", "███", "  █", "███"}  // 9
};

const char *COLON_ON[DIGIT_H] = {
	"   ",
	" █ ",
	"   ",
	" █ ",
	"   "
};

const char *COLON_OFF[DIGIT_H] = {
	"   ",
	"   ",
	"   ",
	"   ",
	"   "
};

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
	printf(RESET);
}

#define LABEL_COLOR "\033[37m"
void print_digital_countdown()
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	struct tm xmas = *t;
	xmas.tm_mon = 11;
	xmas.tm_mday = 25;
	xmas.tm_hour = 0;
	xmas.tm_min = 0;
	xmas.tm_sec = 0;

	time_t xt = mktime(&xmas);
	if (difftime(xt, now) < 0) {
		xmas.tm_year++;
		xt = mktime(&xmas);
	}

	int diff = (int)difftime(xt, now);

	int d = diff / 86400;
	int h = (diff % 86400) / 3600;
	int m = (diff % 3600) / 60;
	int s = diff % 60;

	int nums[8] = {
		d / 10, d % 10,
		h / 10, h % 10,
		m / 10, m % 10,
		s / 10, s % 10
	};

	int blink = (s % 2 == 0);
	const char **colon = blink ? COLON_ON : COLON_OFF;

	printf(RED);
	for (int row = 0; row < DIGIT_H; row++) {
		for (int i = 0; i < 8; i++) {
			printf("%s  ", DIGITS[nums[i]][row]);
			if (i == 1 || i == 3 || i == 5)
				printf("%s  ", colon[row]);
		}
		printf("\n");
	}
	printf(RESET);

	printf("%s   DD             HH             MM             SS%s\n", LABEL_COLOR, RESET);

}

int main()
{
	int line = 0;

	while (1) {
//		system("clear");
		printf("\033[H");

		printf("\n\n\n");
		print_christmas_tree(line);
		printf("\n\n");
		print_colored_ascii_art();
		printf("\n\n");
		print_digital_countdown();

		fflush(stdout);
		usleep(1000000);
		line++;
	}

	return 0;
}
