#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "dir.h"
#include "text.h"

char 
*retrieve_kbdb_dir(char *path)
{
    char *sufix = "backlight";
    char *name_dir = NULL;
    struct dirent *dent;
    DIR *dir;
    dir = opendir (path);
    if (dir == NULL)
    {
        return NULL;
    }
    while ((dent = readdir (dir)) != NULL)
    {
        if (text_ends_with (dent->d_name, sufix))
        {
            name_dir = dent->d_name;
    
        }
    }
    closedir(dir);
    return name_dir;
}

char
*max_brightness_dir_file(char *path)
{
    char *max_brightness_file = NULL;
    char *sufix_max = "max_brightness";
    struct dirent *dent;
    DIR *dir;
    dir = opendir (path);
    while ((dent = readdir (dir)) != NULL)
    {
        if (strcmp(dent->d_name, sufix_max) == 0)
            max_brightness_file = dent->d_name;
    }
    closedir (dir);
    return max_brightness_file;
}

char
*brightness_dir_file(char *path)
{
    char *brightness_file = NULL;
    char *sufix_brightness = "brightness";
    struct dirent *dent;
    DIR *dir;
    dir = opendir (path);
    while ((dent = readdir (dir)) != NULL)
    {
        if (strcmp(dent->d_name, sufix_brightness) == 0)
            brightness_file = dent->d_name;
    }
    closedir (dir);
    return brightness_file;
}

int
max_brightness_value(char *path)
{
    FILE *max_brightness_file = fopen (path, "r");
    char max_level[BUFSIZ];
    int max = 0;

    if (max_brightness_file) {
        while (fgets (max_level, BUFSIZ, max_brightness_file) != NULL)
        {
            printf ("max_level is: %s", max_level);
            max = atoi(max_level);
        }

    }
    fclose(max_brightness_file);
    return max;
}

int
level_brightness_value(char *path)
{
    FILE *brightness_file = fopen (path, "r");
    char current_level[BUFSIZ];
    int level = 0;
    if (brightness_file) {
        while (fgets (current_level, BUFSIZ, brightness_file) != NULL)
        {
            printf ("level is: %s\n", current_level);
            level = atoi(current_level);
        }

    }
    fclose(brightness_file);
    return level;
}