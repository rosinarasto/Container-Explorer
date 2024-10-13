#ifndef FILTER_PRINT_H
#define FILTER_PRINT_H

#include "general.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief function is looking for switches, which has to be aplicate on particular container and then tests if container items are compatible with them
 * 
 * @param structure, which store infomation about switches read when starting the program
 *  
 * @param structure, which store information about particular container 
 *  
 * @retval true if container items are compatible with all valid switches
 * 
 * @retval false if container items arent compatible with any of valid switches
 */
bool filter_item(struct switch_items switches, struct container_items item);

/**
 * @brief function print all parts of container address, which where in input file
 * 
 * @param structure, which store information about particular container
 */
void print_address(struct container_items item);

/**
 * @brief function iterate through neighbors and print unique one
 * 
 * @param quantity of neigbors
 *  
 * @param array, which contain container neigbors
 */
void print_neighbors(size_t length, uintmax_t neighbors[]);

/**
 * @brief function iterate through containers and print container items, which are compatible with filter
 * 
 * @param structure, which store inforamtion about containers, paths and stations
 *  
 * @param structure, which store information about switches read when starting the program
 */
void filter_and_print(struct struct_array lists, struct switch_items switches);

/**
 * @brief function iterate through all possible_waste_type and print particular waste type if match was found 
 * 
 * @param number, which represent set of all waste_types that contain particular station
 * 
 * @param string, which contain all types of waste that are in particular station 
 */
void print_waste_type(uint16_t waste_types, const char *type_chars);

/**
 * @brief function iterate through all neighboring stations, print are unique neighboring stations
 * 
 * @param quantity of neighboring stations
 *  
 * @param array, which contain all neighboring stations 
 */
void print_neighboring_stations(size_t length, uintmax_t neighbors[]);

/**
 * @brief function iterate through all stations and print wanted information about every station
 *  
 * @param structure, which store inforamtion about containers, paths and stations
 */
void print_stations(struct struct_array lists);

#endif // FILTER_PRINT_H