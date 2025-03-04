// Name: Curtis Robinson
// Date: March 4th 2025
// Title: Lab8 – Page Replacement Least Recently Used Algorithm
// Description: This file implements the Least Recently Used algorithm described
// below.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int pageno;
} ref_page;

int main(int argc, char *argv[]) {
  int CACHE_SIZE = atoi(argv[1]);

  // LRU cache variables
  ref_page lru_cache[CACHE_SIZE];
  int lru_faults = 0;
  int lru_time[CACHE_SIZE]; // stores the "last used" time for each page in the
                            // LRU cache
  int time_counter = 0;     // global counter for LRU time stamps

  char pageCache[100];
  int i;

  // Initialize FIFO, LRU and Second Chance caches and their tracking arrays
  for (i = 0; i < CACHE_SIZE; i++) {
    lru_cache[i].pageno = -1; // LRU cache initialization
    lru_time[i] = 0;          // LRU usage time is initially 0
  }

  while (fgets(pageCache, 100, stdin)) {
    int page_num = atoi(pageCache);

    /*
    Page Replacement Implementation Goes Here
    LRU:
      LRU (Least Recently Used): replaces the page that was last used (hit or
    miss) at the earliest point in time. You may need to implement a counter
    that increments each time a new page request is made to store in the
    ref_page struct.
    https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/
    */

    // --- LRU Implementation ---
    time_counter++; // Increment the global time counter for each page request

    bool foundInLRU = false;
    // Check if the page is already in the LRU cache
    for (i = 0; i < CACHE_SIZE; i++) {
      if (lru_cache[i].pageno == page_num) {
        foundInLRU = true;
        // Update the "last used" time since we have a cache hit
        lru_time[i] = time_counter;
        break;
      }
    }
    if (foundInLRU == false) {
      printf("%d\n", page_num);
      // Cache miss for LRU: first, check if there's an empty slot
      int emptyIndex = -1;
      for (i = 0; i < CACHE_SIZE; i++) {
        if (lru_cache[i].pageno == -1) {
          emptyIndex = i;
          break;
        }
      }
      if (emptyIndex != -1) {
        // Use the empty slot for the new page
        lru_cache[emptyIndex].pageno = page_num;
        lru_time[emptyIndex] = time_counter; // Record its access time
      } else {
        // No empty slot: find the least recently used page in the LRU cache
        int lru_index = 0;
        int min_time = lru_time[0];
        for (i = 1; i < CACHE_SIZE; i++) {
          if (lru_time[i] < min_time) {
            min_time = lru_time[i];
            lru_index = i;
          }
        }
        // Replace the LRU page with the new page
        lru_cache[lru_index].pageno = page_num;
        lru_time[lru_index] =
            time_counter; // Update the last used time for this slot
      }
      lru_faults++; // Increment LRU page fault count
    }
  }

  printf("LRU Total Page Faults: %d\n", lru_faults);

  return 0;
}
