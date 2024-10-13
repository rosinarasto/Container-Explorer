#include "path.h"

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void free_dijkstra(intmax_t dist[], intmax_t prev[], intmax_t Q[], intmax_t seen[]) {
    free(dist);
    free(prev);
    free(Q);
    free(seen);
}

void print_path(uintmax_t target, intmax_t prev[], size_t length)
{
    assert(prev != NULL);
    size_t i = 0;
    intmax_t u = target - 1;
    intmax_t *result = malloc(length * sizeof(intmax_t));
    if (result == NULL) {
        return;
    }

    if (prev[u] != -1) {

        while (u != -1) {
            result[i] = u + 1;
            i ++;
            u = prev[u];
        }
    
    } else {
        free(result);
        return;
    }

    printf("%ld", result[i - 1]);

    for (size_t j = 2; j < (i + 1); j++) {
        printf("-%ld", result[i - j]);
    }

    free(result);
}

bool not_in_seen(intmax_t seen[], size_t length, intmax_t element) {
    assert(seen != NULL);

    for (size_t i = 0; i < length; i++) {
        if (seen[i] == element) {
            return false;
        }

    }

    return true;
}

intmax_t get_min_dist(intmax_t Q[], intmax_t dist[], intmax_t seen[], size_t length)
{
    assert(Q != NULL);
    assert(dist != NULL);
    assert(seen != NULL);
    size_t min_index = 0;
    intmax_t min_dist = INT_MAX;

    for (size_t i = 0; i < length; i++) {
        if (dist[i] < min_dist && not_in_seen(seen, length, Q[i])) {
            min_dist = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

/*https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm*/
bool dijkstra(uintmax_t source, uintmax_t target, struct station_items stations[], size_t length)
{
    assert(stations != NULL);
    if (source > length || target > length) {
        return false;
    }

    intmax_t *dist = malloc(length * sizeof(intmax_t));
    intmax_t *prev = malloc(length * sizeof(intmax_t));
    intmax_t *Q = malloc(length * sizeof(intmax_t));
    intmax_t *seen = malloc(length * sizeof(intmax_t));
    size_t seen_index = 0;
    if (dist == NULL || prev == NULL || Q == NULL || seen == NULL) {
        return false;
    }

    for (size_t v = 0; v < length; v++) {
        dist[v] = INT_MAX;
        prev[v] = -1;
        Q[v] = v;
        seen[v] = -1;
    }

    dist[source - 1] = 0;
    uintmax_t u;
    intmax_t alt;

    while (seen_index < length) {
        u = get_min_dist(Q, dist, seen, length);
        if (u == (target - 1)) {
            print_path(target, prev, length);
            printf(" %ld\n", dist[u]);
            free_dijkstra(dist, prev, Q, seen);
            return true;
        }
        seen[seen_index] = u;
        seen_index++;
    
        for (size_t v = 0; v < stations[u].neighbors.length; v++) {
            if (v == 0 || stations[u].neighbors.ids[v] != stations[u].neighbors.ids[v - 1]) {
                alt = dist[u] + stations[u].neighbors.distance[v];
                if (alt < dist[stations[u].neighbors.ids[v] - 1]) {
                    dist[stations[u].neighbors.ids[v] - 1] = alt;
                    prev[stations[u].neighbors.ids[v] - 1] = u;
                }
            }
        }
    }

    free_dijkstra(dist, prev, Q, seen);
    return false;
}

void find_shortest_path(uintmax_t source, uintmax_t target, struct station_items stations[], size_t length)
{
    assert(stations != NULL);

    if (source == target) {
        printf("%ju 0\n", source);
        return;
    }

    if (!dijkstra(source, target, stations, length)) {
        printf("No path between specified sites\n");
    }
    
    return;
}