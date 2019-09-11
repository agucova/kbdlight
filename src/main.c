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
           "  kbdlight [OPTIONS]\n"
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
    int inc = 0, cur = 0;
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

    while ((arg = getopt(argc, argv, "idch")) != -1) {
        switch (arg) {
        case 'i':
            inc = 1;
            break;
        case 'd':
            break;
        case 'c':
            cur = 1;
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
        printf (" your kernel doesn't support beyboard backlight/brightness\n");
        return EXIT_FAILURE;
    }
    
    brightness_file = get_brightness(kernel_resources_dir);

    if (!brightness_file)
    {
        printf (" \"brightness\" file doesn't exists in: %s\n", kernel_resources_dir);
        return EXIT_FAILURE;
    }
    
    current_level = read_curent_level(brightness_file);

    if (cur)
    {
        printf ("%d\n", current_level);
        return EXIT_SUCCESS;
    }

    max_brightness_file = get_max_brightness(kernel_resources_dir);

    if (!max_brightness_file)
    {
        printf (" \"max_brightness\" file doesn't exists in: %s\n", kernel_resources_dir);
        return EXIT_FAILURE;
    }
    free (kernel_resources_dir);
    max_brightness = read_max_brightness(max_brightness_file);
    free (max_brightness_file);

    level = inc ? current_level + 1 : current_level - 1;

    if (level >= 0 && level <= max_brightness) {
        write_brightness(brightness_file, level);
    }
    free (brightness_file);

    return EXIT_SUCCESS;
}