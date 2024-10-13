#ifndef FILES_H
#define FILES_H

#include <stdbool.h>
#include <stdlib.h>

#include "general.h"

/**
 * @brief function checks if id column is in file, if id exist, has valid format (it means that id is number below UINT_MAX) and if isnt duplicated
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if id exists (not NULL, not empty), is valid uint value and isnt duplicated
 * 
 * @retval false if id doesnt exist (NULL, empty), is duplicated or function "string_to_uint" was unsuccessful 
 * 
 * bool id_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief fucntion checks if x column and y column are in file, if x and y exist and if exist then check and convert their format in function "string_to_double" 
 *
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if x and y exist (not NULL, not empty) and have correct format (it means they are correct doubles)
 * 
 * @retval false if x or y doesnt exist (NULL, empty) or if x or y or both of them dont have correct format (string cant be convert to double)
 * 
 * bool conatiner_x_y_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief function checks if waste_type column is in file then for loop iterate through "possible_waste_type" and if "waste_type" match witch "possible_waste_type" then
 * break for loop (it means that if match was found, "i" has to be lower than 6) and 
 * at the end function check if "waste_type" is empty and if function "copy_string" ended successfully  
 *
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if "waste_type" exists (not NULL, not empty), "waste_type" is one of valid strings from "possible_waste_type"
 * 
 * @retval false if "waste_type" doesnt exist (NULL, empty) or "waste_type" isnt one of valid strings from "possible_waste_type"
 * 
 * bool waste_type_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief function checks if capcity column is in file, if capacity exists, then is checked if has right format and is converted from string to uint
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if capacity exists (not NULL, not empty), has correct format and was successfully converted in "string_to_uint"
 * 
 * @retval flase if capacity doesnt exist (NULL, empty), hasnt correct format of conversion was unsuccessful
 * 
 * bool capacity_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief function checks if name column, street column and number column is in file, if string were successfully copied into new variables,
 * if number is empty [(information will be used in printing result), (name, street and number are optional)] and if nonempty number has right format and was successfully converted into uint
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if "name", "street" and "number" arent NULL, if function "copy_string" was successful and number is empty or has right format and was converted to uint
 * 
 * @retval false if "name", "street" or "number" are NULL, if function "copy_string" was unsuccessful or number is not empty and hasnt right format or wasnt converted successfully
 * 
 * bool address_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief function checks if publicity column is in file and then if publicity has correct format
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if publicity exists (not NULL, not empty), and if has correct format
 * 
 * @retval false if publicity doesnt exist (NULL, empty) or hasnt correct format
 * 
 * bool publicity_parse(struct struct_array *lists, size_t index);
 */

/**
 * @brief function checks if all rows of container file are valid
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @retval true if every row of container file is valid and allocation function was successful
 * 
 * @retval false if one or more rows of container file arent valid or allocation fuction was unsuccessful
 * 
 * bool container_file_parse(struct struct_array *lists);
 */

/**
 * @brief function checks if ids columns and distance column are in path file, if id_a and id_b are not the same,
 * if ids and distance have correct format and was successfully converted into uint and if ids are in container file  
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if ids and distance exist (not NULL, not empty), if ids arent the same, if ids and distance have correct format and was successfully converted into uint and if ids are in container file
 * 
 * @retval false if ids or distance dont exist (NULL, empty), if ids are same, if ids or distacne have wrong format or werent successfully converted into uint or ids arent in container file
 *
 * bool id_distance_parse(struct struct_array *lists, size_t index); 
 */

/**
 * @brief function checks if all rows of path file are valid
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if allocation function was successful and every row from path file is valid
 * 
 * @retval false if allocation function was unsuccessful or one or rows from path file isnt valid
 * 
 * bool path_file_parse(struct struct_array *lists);
 */

/**
 * @brief fucntion checks if data were initialized in init_data_source and if container and path file are valid
 * 
 * @param pointer to "struct_array" structure, which contain conatainers, paths and stations
 *  
 * @param index of paritucular row
 *  
 * @retval true if init_data_source was successful and if cotainer and path file are valid
 *  
 * @retval false if init_data_source was unsuccessful or if container or path file are not valid
 */
bool file_parse(char *argv[], int argc, struct struct_array *lists);

#endif // FILES_H