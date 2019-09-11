#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
text_ends_with (const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen (str);
    size_t lensuffix = strlen (suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp (str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char
*kbd_backlight_concat_path(char *resources, char *path)
{
    char *kbd_backlight_dir_path = (char *) malloc (1 + strlen (resources) + strlen (path));
    sprintf(kbd_backlight_dir_path, "%s/%s", resources, path);
    return kbd_backlight_dir_path;
}