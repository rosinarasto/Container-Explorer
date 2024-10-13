#ifndef STATIONS_NEOGHBORS_H
#define STATIONS_NEOGHBORS_H

#include "general.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum station_change
{ 
    FAULT,
    NEW,
    WITHOUT_CHANGE
};

/**
 * @brief function set values for new neihbor, if array of neighbors is almost full, function realloc array of neighbors 
 * 
 * @param id of neighbouring container or station
 *  
 * @param distance between neighbouring containers or stations
 *  
 * @param structure, which store inforamtion about neighbors of container or station
 * 
 * @retval true if allocation was successful
 * 
 * @retval false if allocation was unsuccessful
 */
bool add_neighbor(uintmax_t neighbor_id, uintmax_t distance, struct neighbor_items *neighbor);

/**
 * @brief function iterate through containers, for every container initialize neighbors,
 * then in the second loop iterate through ids in paths array and if one of ids matches with container id,
 * function add id_a or id_b (it depends on which id matched with container id) as a neighbor of container,
 * at the end array of neighbors is sorted ascending (according to neighbor id)
 * 
 * @param pointer to structre, which store infomation about containers, paths, stations
 *  
 * @retval true if all calls of function add_neighbor() were successful 
 * 
 * @retval false if one call of function add_neighbor() was unsuccessful
 */
bool find_neighbors(struct struct_array *lists);

/**
 * @brief function set variables to particular value
 * 
 * @param array structures that stores information about stations
 *  
 * @param index of particular station
 *  
 * @param structer that stores information about particular container 
 */
void add_container_in_station(struct station_items stations[], size_t index, struct container_items container);

/**
 * @brief fucntion initialize new station and set variable to starting values
 * 
 * @param array structures that stores information about stations
 *  
 * @param index of particular station
 *  
 * @param structer that stores information about particular container
 * 
 * @retval true if allocation functions were successful
 * 
 * @retval false if allocation functions were unsuccessful
 */
bool station_inicialization(struct station_items stations[], size_t index, struct container_items container);

/**
 * @brief function multiply length of array by 2 a then realloc new memory
 * 
 * @param pointer to structure that stores information about station
 *  
 * @retval true if allocation were successful
 * 
 * @retval false if allocation were unsuccessful
 */
bool realloc_station(struct station_items *station);

/**
 * @brief function iterates through existing stations, if x and y of container match witch x and y of station then container is added to station
 * else at the end of for loop is initialized new station
 * 
 * @param structure that stores information about particular container
 *  
 * @param array structures that stores information about stations
 * 
 * @param quantity of stations
 *  
 * @retval WITHOUT_CHANGE if container was added to existing station
 * 
 * @retval NEW if inicialization of new station was successfull
 * 
 * @retval FAULT if inicializitation of new station was unsuccessful
 */
enum station_change add_station(struct container_items container, struct station_items stations[], size_t length);

/**
 * @brief for every station function initialize structure neighbor_item (set variables to starting values),
 * in second loop is function looking for neighbors of every container that is in station,
 * in third loop for every neighbor of every container is looking for station in which particular neighbor is,
 * this station is added to neighbors of current station, at the end is array of neighbouring stations sorted ascending (according to neighbouring station id)  
 * 
 * @param pointer to structure that contain information about containers, paths and stations
 *   
 * @retval true if all allocations ended successfully 
 * 
 * @retval false if allocations were unsuccessful or function add_neighbor() was unsuccessful
 */
bool find_neighbouring_stations(struct struct_array *lists);

/**
 * @brief function iterate through all containers and every container is added to particular station in add_station()
 * 
 * @param pointer to structure that contain information about containers, paths and stations
 * 
 * @retval true if all allocations were successful and function find_neighbouring_stations() ended successfully
 * 
 * @retval false if one of allocations were unsuccessful or function find_neighbouring_stations() ended unsuccessfully
 */
bool find_stations(struct struct_array *lists);

#endif // STATIONS_NEOGHBORS_H