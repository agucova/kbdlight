#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>
#include <getopt.h>

#include "text.h"
#include "dir.h"
#include "file.h"

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
    int arg;
    int inc = 0;
    char *kernel_resources_dir = NULL;
    char *brightness_file = NULL;
    char *max_brightness_file = NULL;
    int max_brightness = 0;
    int current_level = 0;
    int level;

    if (argc < 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    while ((arg = getopt(argc, argv, "idh")) != -1) {
        switch (arg) {
        case 'i':
            inc = 1;
            break;
        case 'd':
            break;
        case '?':
        case 'h':
        default:
            usage();
            return EXIT_FAILURE;
        }
    }

    kernel_resources_dir = get_kernel_resources();   
    if (!kernel_resources_dir)
    {
        printf ("Error: your kernel doesn't support beyboard backlight/brightness\n");
        return EXIT_FAILURE;
    }
    
    max_brightness_file = get_max_brightness(kernel_resources_dir);

    if (!max_brightness_file)
    {
        printf ("Error: \"max_brightness\" file doesn't exists in: %s\n", kernel_resources_dir);
        return EXIT_FAILURE;
    }

    max_brightness = read_max_brightness(max_brightness_file);
    free (max_brightness_file);

    brightness_file = get_brightness(kernel_resources_dir);

    if (!brightness_file)
    {
        printf ("Error: \"brightness\" file doesn't exists in: %s\n", kernel_resources_dir);
        return EXIT_FAILURE;
    }
    free (kernel_resources_dir);
    current_level = read_curent_level(brightness_file);

    level = inc ? current_level + 1 : current_level - 1;

    if (level >= 0 && level <= max_brightness) {
        write_brightness(brightness_file, level);
    }
    free (brightness_file);

    return EXIT_SUCCESS;
}