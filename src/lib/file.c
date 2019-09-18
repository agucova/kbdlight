#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "file.h"

int
read_max_brightness(char *path)
{
    FILE *max_brightness_file = fopen (path, "r");
    char max_level[BUFSIZ];
    int max = 0;

    if (max_brightness_file) {
        while (fgets (max_level, BUFSIZ, max_brightness_file) != NULL)
        {
            max = (int)strtol(max_level, (char **)NULL, 10);
        }
    }
    fclose(max_brightness_file);
    return max;
}

int
read_curent_level(char *path)
{
    FILE *brightness_file = fopen (path, "r");
    char current_level[BUFSIZ];
    int level = 0;
    if (brightness_file) {
        while (fgets (current_level, BUFSIZ, brightness_file) != NULL)
        {
            level = atoi(current_level);
        }

    }
    fclose(brightness_file);
    return level;
}

void write_brightness(char *path, int level) {
    FILE *brightness_file = fopen(path, "w");
    if (brightness_file) {
        fprintf (brightness_file, "%d", level);
    }
    fclose(brightness_file);
}