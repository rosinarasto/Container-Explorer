#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "general.h"

/**
 * @brief for loop iterate through characters in "arguments" and
 * looking for match with character from "possible_arguments"
 * 
 * @param argument, which come right after "-t" switch 
 * 
 * @param pointer to switch_item structure, where are stored information about switches and their arguments
 * 
 * @retval true if all characters from arguments are in "possible_arguments" and
 * waste_type was successfully copied into "switches.waste_type"
 * 
 * @retval false if all characters from arguments are not in "possible_arguments" or
 * waste_type was not successfully copied into "switches.waste_type"
 * 
 * bool type_filter(const char *arguments, struct switch_items *switches);
 */

/**
 * @brief function checks if switch is not duplicated (bit comparison, "(switches->collection & T) != T"),
 * check if switch has right form and check if arguments are valid
 * 
 * @param particular switch ("-t", "-c", "-g")
 *  
 * @param argument, which come right after particular switch
 *  
 * @param pointer to switch_item structure, where are stored information about switches and their arguments
 * 
 * @retval true if switch and its arguments are valid
 * 
 * @retval false if switch or its arguments are not valid
 * 
 * bool switch_validation(const char *switch_char, const char *arguments, struct switch_items *switches);
 */

/**
 * @brief while loop is going through all "main" arguments which were read when starting the program and
 * deciding if these "main" arguments are valid or not
 * 
 * @param quantity of arguments
 * 
 * @param "main" arguments, which were read when starting the program 
 *
 * @param pointer to switch_item structure, where are stored information about switches and their arguments
 *  
 * @retval true if all switches and their arguments are valid
 * 
 * @retval false if switch or arguments are not valid or when switch have to have, but dont have argument
 */
bool arguments_validation(int argc, char *argv[], struct switch_items *switches);

#endif // ARGUMENTS_H