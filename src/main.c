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
    char *kernel_resources = "/sys/class/leds/";
    int arg;
    int inc = 0, dec = 0;
    char *kbd_backlight_name_dir = NULL;
    char *kbd_backlight_dir_path;    
    char *brightness_name_file = NULL;
    char *brightness_file_path = NULL;
    char *max_brightness_name_file = NULL;
    char *max_brightness_file_path = NULL;
    char current_level[BUFSIZ];
    int max = 0;
    int level = 0;
    int set_level;
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
    if (!kbd_backlight_name_dir)
    {
        printf ("Error: your kernel doesn't support beyboard backlight/brightness\n");
        return EXIT_FAILURE;
    }

    kbd_backlight_dir_path = (char *) malloc (1 + strlen (kernel_resources) + strlen (kbd_backlight_name_dir));
    sprintf(kbd_backlight_dir_path, "%s%s", kernel_resources, kbd_backlight_name_dir);
    printf ("kbd_backlight_dir_path: [%s]\n", kbd_backlight_dir_path);

    max_brightness_name_file = max_brightness_dir_file(kbd_backlight_dir_path);
    if (!max_brightness_name_file)
    {
        printf ("Error: \"max_brightness\" file doesn't exists in: %s\n", kbd_backlight_dir_path);
        return EXIT_FAILURE;
    }
    max_brightness_file_path = (char *) malloc (1 + strlen (kbd_backlight_dir_path) + strlen (max_brightness_name_file));
    sprintf(max_brightness_file_path, "%s/%s", kbd_backlight_dir_path, max_brightness_name_file);
    printf ("max_brightness_file_path: [%s]\n", max_brightness_file_path);

    max = max_brightness_value(max_brightness_file_path);
    free (max_brightness_file_path);

    brightness_name_file = brightness_dir_file(kbd_backlight_dir_path);

    if (!brightness_name_file)
    {
        printf ("Error: \"brightness\" file doesn't exists in: %s\n", kbd_backlight_dir_path);
        return EXIT_FAILURE;
    }

    printf ("brightness_name_file: [%s]\n", brightness_name_file);
    brightness_file_path = (char *) malloc (1 + strlen (kbd_backlight_dir_path) + strlen (brightness_name_file));
    sprintf(brightness_file_path, "%s/%s", kbd_backlight_dir_path, brightness_name_file);
    printf ("brightness_file_path: [%s]\n", brightness_file_path);

    level = level_brightness_value(brightness_file_path);

    printf ("level: %d\n", level);
    printf ("max: %d\n", max);

    set_level = inc ? level + 1 : level - 1;

    if (set_level >= 0 && set_level <= max) {
        printf ("Writting: %d\n", set_level);
        brightness_file = fopen(brightness_file_path, "w");
        if (brightness_file) {
            fprintf (brightness_file, "%d", set_level);
        }
        fclose(brightness_file);
    }
    free (kbd_backlight_dir_path);
    free (brightness_file_path);


    return EXIT_SUCCESS;
}