#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>
#include <getopt.h>

#include "text.h"
#include "dir.h"

void
usage()
{
    printf("Usage:\n"
           "  kdblight [OPTIONS]\n"
           "\n"
           "Options:\n"
           "  -i          Increase brightness\n"
           "  -d          Decrease brightness\n"
           "  -c          Current brightness\n"
           "  -h          Display help (this menu)\n"
           "\n");

}

int
main (int argc, char *argv[])
{
    char *sufix = "backlight";
    char *sufix_max = "max_brightness";
    char *sufix_brightness = "brightness";
    char *kernel_resources = "/sys/class/leds/";
    int arg;
    int inc = 0, dec = 0;
    char *kbd_backlight_name_dir = NULL;
    char *kbd_backlight_dir_path;    
    char *brightness_name_file = NULL;
    char *brightness_file_path = NULL;
    char *max_brightness_name_file = NULL;
    char *max_brightness_file_path = NULL;
    char max_level[BUFSIZ];
    char current_level[BUFSIZ];
    int max;
    int level;
    int set_level;
    struct dirent *dent;
    DIR *dir;
    FILE *max_brightness_file;
    FILE *brightness_file;

    if (argc < 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    while ((arg = getopt(argc, argv, "idh")) != -1) {
        switch (arg) {
        case 'i':
            printf ("option i\n");
            inc = 1;
            break;
        case 'd':
            printf ("option d\n");
            dec = 1;
            break;
        case '?':
        case 'h':
        default:
            usage();
            return EXIT_FAILURE;
        }
    }

    printf ("inc: %d\n", inc);
    printf ("dec: %d\n", dec);
    kbd_backlight_name_dir = retrieve_kbdb_dir(kernel_resources);
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
                while (fgets (max_level, BUFSIZ, max_brightness_file) != NULL)
                {
                    printf ("max_level is: %s\n", max_level);
                    max = atoi(max_level);
                }

            }
            fclose(max_brightness_file);

            if (brightness_name_file) {
                printf ("brightness_name_file: [%s]\n", brightness_name_file);
                brightness_file_path = (char *) malloc (1 + strlen (kbd_backlight_dir_path) + strlen (brightness_name_file));
                strcpy (brightness_file_path, kbd_backlight_dir_path);
                strcat (brightness_file_path, "/");
                strcat (brightness_file_path, brightness_name_file);
                printf ("brightness_file_path: [%s]\n", brightness_file_path);
                brightness_file = fopen (brightness_file_path, "w+");

                if (brightness_file) {
                    while (fgets (current_level, BUFSIZ, brightness_file) != NULL)
                    {
                        printf ("level is: %s\n", current_level);
                        level = atoi(current_level);
                    }

                }
                printf ("level: %d\n", level);
                printf ("max: %d\n", max);

                if (inc) {
                    set_level = level + 1;
                } else {
                    set_level = level - 1;
                }

                if (set_level >= 0 && set_level <= max) {
                    printf ("Writting %d\n", set_level);
                    fprintf (brightness_file, "%d", set_level);
                }



                fclose(brightness_file);
            }
        }

        free (brightness_file_path);
        free (max_brightness_file_path);
        free (kbd_backlight_dir_path);
        closedir (dir);
    }

    return EXIT_SUCCESS;
}