#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

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
        printf ("Cannot open directory '%s'\n", path);
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