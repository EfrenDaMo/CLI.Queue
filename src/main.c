#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h> // Windows functions
#elif __linux__
#include <unistd.h>  // Linux functions
#endif

// Colors for printing
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Draws interface
void interface(int time, int people);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("error: Too few arguments for use (use -h for help)\n");
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("usage: queue <operation> [...] \n");
        printf("operations: \n");
        printf("    queue {-h --help}\n");
        printf("    queue {-e --exec} <options>\n");
        printf("use 'queue {-h --help}' with an operation for available options");

        return 2;
    }

    if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--exec") == 0) {
        if (argc < 3) {
            printf("error: Too few arguments for use of -e (use -h for help)\n");

            return 1;
        }

        if (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--help") == 0) {
            printf("usage: queue -e <time> <people> \n");
            printf("    <time>: Determines how long the queue will last. (in minutes)\n");
            printf("    <people>: Determines how many people will be in the queue.\n");

            return 2;
        } else {
            int time = atoi(argv[2]);
            int people = atoi(argv[3]);

            interface(time, people);
        }
    }

    return 0;
}

void interface(int time, int people) {
    int timer_seconds = time * 60;
    int time_per_person = timer_seconds/people;
    people++;

    do {
        int hours = timer_seconds / 3600;
        int minutes = (timer_seconds % 3600) / 60;
        int seconds = timer_seconds % 60;

        system("clear");
        printf("\r    %02d:%02d:%02d \n", hours, minutes, seconds);
        printf(" _____________ \n");
        printf(" | " ANSI_COLOR_YELLOW "The Queue" ANSI_COLOR_RESET " | \n");
        printf(" |___________| \n");
        printf("_____ \x1b[36m O \x1b[0m ___________________________\n");
        printf("    |_____|     \n");
        printf("      ");
        if (timer_seconds % time_per_person == 0) {
            people--;
        }
        for(int i = 0; i < people; i++) {
            if (i + 1 == people) {
                printf(ANSI_COLOR_RED     " O "     ANSI_COLOR_RESET);
            } else {
                printf(" O ");
            }
        } 
        printf("\n_____________________________________\n");
        fflush(stdout);

        clock_t stop = clock() + CLOCKS_PER_SEC;

        while (clock() < stop) { }

        // Decrement seconds as another second has elapsed
        timer_seconds--;
    } while(timer_seconds > -1);
}
