#include "arguments.h"
#include "general.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool type_filter(const char *arguments, struct switch_items *switches)
{
    assert(arguments != NULL);
    assert(switches != NULL);

    for (size_t i = 0; i < strlen(arguments); i++) {
        const char *position = strchr((switches->type_chars), arguments[i]);
        if (position == NULL)
            return false;

        switches->waste_types |= ((uint16_t)1 << (position - switches->type_chars));
    }

    return true;
}

bool switch_validation(const char *switch_char, const char *arguments, struct switch_items *switches)
{
    assert(switch_char != NULL);
    assert(arguments != NULL);
    assert(switches != NULL);
    if (switches->collection < S) {
        if (((switches->collection & T) != T) && !strcmp(switch_char, "-t") && type_filter(arguments, switches)) {
            switches->collection |= T;
            return true;
        }

        if (((switches->collection & C) != C) && !strcmp(switch_char, "-c") && string_to_uint(arguments, &(switches->capacity_floor), '-') && string_to_uint(strchr(arguments, '-') + 1, &(switches->capacity_ceiling), '\0')) {
            switches->collection |= C;
            return (switches->capacity_floor <= switches->capacity_ceiling);
        }

        if (((switches->collection & P) != P) && !strcmp(switch_char, "-p") && (!strcmp(arguments, "N") || !strcmp(arguments, "Y"))) {
            switches->collection |= P;
            switches->publicity = (char) arguments[0];
            return true;
        }

        if ((switches->collection == EMPTY) && !strcmp(switch_char, "-g") && string_to_uint(arguments, &(switches->g_source), ',') && string_to_uint(strchr(arguments, ',') + 1, &(switches->g_target), '\0')) {
            switches->collection |= G;
            return true;
        }

    }
 
    return false;
}

bool arguments_validation(int argc, char *argv[], struct switch_items *switches)
{
    assert(argv != NULL);
    int i = 1;

    while (i < (argc - 2)) {

        if (!strcmp(argv[i], "-s") && switches->collection == EMPTY) {
            i--; // switch "-s" cant have arguments, so shift has to be just 1
            switches->collection |= S;
        } else if (i == (argc - 3) || !switch_validation(argv[i], argv[i + 1], switches)) {
            return false;
        }

        i += 2;

    }

    return true;
}

