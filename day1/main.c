#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define START_POSITION 50

void parse(const char* str, char* dir, int* digit) {
    *dir = str[0];
    *digit = atoi(str+1);
}

void part1(char **lines, int count) {
    int start = START_POSITION;
    int passwd = 0;
    for (int i = 0; i < count; i++) {
        char dir;
        int digit;
        int prev = start;
        parse(lines[i], &dir, &digit);
        if (dir == 'R') {
            start = (start + digit) % 100;
        } else {
            start = ((start - digit) % 100 + 100) % 100;
        }
        // printf("line %d: %c %d (%d -> %d)\n", i, dir, digit, prev, start);
        // one loop is completed
        if (start == 0) {passwd++;}
    }
    printf("password is: %d\n", passwd);

}

void part2() {}

int main(void) {

    FILE *file;
    file = fopen("input1", "r");
    if (!file) {
        printf("Error opening input1 file\n");
        return 1;
    }

    // count lines
    int count = 0;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }
    fclose(file);

    // alloc char pointer
    char **lines = (char**)malloc(count * sizeof(char*));
    file = fopen("input1", "r");
    if (!file) {
        printf("Error opening input1 file\n");
        return 1;
    }
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < count) {
        // remove newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        lines[i] = (char*)malloc((len + 1) * sizeof(char));
        strcpy(lines[i], buffer);
        i++;
    }
    fclose(file);

    // part1
    part1(lines, count);

    // part2
    part2();

    free(lines);
    return 0;
}
