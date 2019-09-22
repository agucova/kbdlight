#include "dir.h"
#include "text.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *SUFIX = "backlight";
const char *MAX_BRIGHTNESS = "max_brightness";
const char *BRIGHTNESS = "brightness";

char *get_kernel_resources() {
  char *kernel_resources = "/sys/class/leds";
  char *name_dir = NULL;
  struct dirent *dent;
  DIR *dir = opendir(kernel_resources);
  if (dir == NULL) {
    return NULL;
  }
  while ((dent = readdir(dir)) != NULL) {
    if (text_ends_with(dent->d_name, SUFIX)) {
      name_dir = dent->d_name;
      break;
    }
  }
  closedir(dir);

  if (!name_dir) {
    return NULL;
  }

  return concat_path(kernel_resources, name_dir);
}

char *get_max_brightness(char *path) {
  char *max_brightness_file = NULL;
  struct dirent *dent;
  DIR *dir = opendir(path);
  while ((dent = readdir(dir)) != NULL) {
    if (strcmp(dent->d_name, MAX_BRIGHTNESS) == 0)
      max_brightness_file = dent->d_name;
  }
  closedir(dir);
  return concat_path(path, max_brightness_file);
}

char *get_brightness(char *path) {
  char *brightness_file = NULL;
  struct dirent *dent;
  DIR *dir = opendir(path);
  while ((dent = readdir(dir)) != NULL) {
    if (strcmp(dent->d_name, BRIGHTNESS) == 0)
      brightness_file = dent->d_name;
  }
  closedir(dir);
  return concat_path(path, brightness_file);
}
