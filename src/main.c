#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>

int
ends_with (const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen (str);
    size_t lensuffix = strlen (suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp (str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int
main (int argc, char *argv[])
{
    char *sufix = "backlight";
    char *sufix_max = "max_brightness";
    char *sufix_brightness = "brightness";
    char *kernel_resources = "/sys/class/leds/";
    char *kbd_backlight_name_dir = NULL;
    char *kbd_backlight_dir_path;
    char *brightness_name_file = NULL;
    char *brightness_file_path = NULL;
    char *max_brightness_name_file = NULL;
    char *max_brightness_file_path = NULL;
    char max[BUFSIZ];
    char level[BUFSIZ];
    struct dirent *dent;
    DIR *dir;
    FILE *max_brightness_file;
    FILE *brightness_file;

    dir = opendir (kernel_resources);
    if (dir == NULL)
    {
        printf ("Cannot open directory '%s'\n", kernel_resources);
        return 1;
    }

    while ((dent = readdir (dir)) != NULL)
    {
        if (ends_with (dent->d_name, sufix))
        {
            kbd_backlight_name_dir = dent->d_name;
        }
    }

    if (kbd_backlight_name_dir)
    {
        kbd_backlight_dir_path = (char *) malloc (1 + strlen (kernel_resources) + strlen (kbd_backlight_name_dir));
        strcpy (kbd_backlight_dir_path, kernel_resources);
        strcat (kbd_backlight_dir_path, kbd_backlight_name_dir);
        printf ("kbd_backlight_dir_path: [%s]\n", kbd_backlight_dir_path);
        dir = opendir (kbd_backlight_dir_path);
        while ((dent = readdir (dir)) != NULL)
        {
            if (strcmp(dent->d_name, sufix_max) == 0)
            {
                max_brightness_name_file = dent->d_name;

            }
            if (strcmp(dent->d_name, sufix_brightness) == 0)
            {
                brightness_name_file = dent->d_name;

            }
        }
        if (max_brightness_name_file) {
            max_brightness_file_path = (char *) malloc (1 + strlen (kbd_backlight_dir_path) + strlen (max_brightness_name_file));
            strcpy (max_brightness_file_path, kbd_backlight_dir_path);
            strcat (max_brightness_file_path, "/");
            strcat (max_brightness_file_path, max_brightness_name_file);
            printf ("max_brightness_file_path: [%s]\n", max_brightness_file_path);
            max_brightness_file = fopen (max_brightness_file_path, "r");

            if (max_brightness_file) {
                while (fgets (max, BUFSIZ, max_brightness_file) != NULL)
                {
                    printf ("max is: %s\n", max);
                }

            }

            if (brightness_name_file) {
                printf ("brightness_name_file: [%s]\n", brightness_name_file);
                brightness_file_path = (char *) malloc (1 + strlen (kbd_backlight_dir_path) + strlen (brightness_name_file));
                strcpy (brightness_file_path, kbd_backlight_dir_path);
                strcat (brightness_file_path, "/");
                strcat (brightness_file_path, brightness_name_file);
                printf ("max_brightness_file_path: [%s]\n", brightness_file_path);
                brightness_file = fopen (brightness_file_path, "r");

                if (brightness_file) {
                    while (fgets (level, BUFSIZ, brightness_file) != NULL)
                    {
                        printf ("level is: %s\n", level);
                    }

                }
            }
        }


        fclose(brightness_file);
        fclose(max_brightness_file);
        free (brightness_file_path);
        free (max_brightness_file_path);
        free (kbd_backlight_dir_path);
    }
    closedir (dir);


    return 0;
}