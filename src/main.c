#include <dirent.h>
#include <getopt.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"  // Functions for finding the kernel path
#include "file.h" // Functions that handle the changes.
#include "text.h"

void usage() {
  printf("Usage:\n"
         "  kbdlight [OPTIONS]\n"
         "\n"
         "Options:\n"
         "  -i          Increase keyboard brightness\n"
         "  -d          Decrease keyboard brightness\n"
         "  -c          Display current brightness\n"
         "  -h          Display help (this menu)\n"
         "\n");
}

int main(int argc, char *argv[]) {
  // Define variables
  int arg;
  int inc = 0, cur = 0;
  char *kernel_resources_dir = NULL;
  char *brightness_file = NULL;
  char *max_brightness_file = NULL;
  int max_brightness = 0;
  int current_level = 0;
  int level;

  if (argc < 2) {
    usage();
    return EXIT_FAILURE;
  }
  // Process options
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

  if (!kernel_resources_dir) {
    printf("Error: your kernel doesn't support keyboard backlight control.\n");
    return EXIT_FAILURE;
  }

  brightness_file = get_brightness(kernel_resources_dir);

  if (!brightness_file) {
    printf("Error: the \"brightness\" file doesn't exist in: %s\n",
           kernel_resources_dir);
    return EXIT_FAILURE;
  }

  current_level = read_curent_level(brightness_file);

  if (cur) {
    printf("%d\n", current_level);
    return EXIT_SUCCESS;
  }

  max_brightness_file = get_max_brightness(kernel_resources_dir);

  if (!max_brightness_file) {
    printf("Error: the \"max_brightness\" file doesn't exist in: %s\n",
           kernel_resources_dir);
    return EXIT_FAILURE;
  }
  free(kernel_resources_dir);
  max_brightness = read_max_brightness(max_brightness_file);

  if (!max_brightness) {
    printf("Error while trying to get the value from (garbage values): %s\n",
           max_brightness_file);
    return EXIT_FAILURE;
  }

  free(max_brightness_file);

  level = inc ? current_level + 1 : current_level - 1;

  if (level >= 0 && level <= max_brightness) {
    write_brightness(brightness_file, level);
  }
  free(brightness_file);

  return EXIT_SUCCESS;
}
