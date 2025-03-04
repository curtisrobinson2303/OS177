// Name: Curtis Robinson
// Date: March 4th 2025
// Title: Lab8 – Page Replacement Second Chance Algorithm
// Description: This file implements the second chance algorithm described
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

  // Second Chance cache variables
  ref_page sc_cache[CACHE_SIZE];
  int sc_ref[CACHE_SIZE]; // array to store reference bits for Second Chance
  int sc_faults = 0;      // counter for Second Chance page faults
  int sc_index = 0;       // clock hand pointer for Second Chance

  char pageCache[100];
  int i;

  // Initialize Second Chance caches and their tracking arrays
  for (i = 0; i < CACHE_SIZE; i++) {
    sc_cache[i].pageno = -1; // Second Chance cache initialization
    sc_ref[i] = 0;           // All Second Chance reference bits are initially 0
  }

  while (fgets(pageCache, 100, stdin)) {
    int page_num = atoi(pageCache);

    /*
    Page Replacement Implementation Goes Here
    Second Chance:
      2nd Chance or Clock: gives every page a second chance in the sense that
    any page that has been the cause of a cache hit is likely going to cause
    further cache hits, and therefore, should not be swapped out in place of a
    newer page that has never caused a cache hit. Similar logic to FIFO may be
    used, but instead of paging the oldest page out immediately, a "reference"
    bit would be checked. If the bit is unset (0), then the page can be removed,
    but if it is set (1), the page should be skipped over while unsetting the
    reference bit (to avoid infinite loops).

    https://www.geeksforgeeks.org/second-chance-or-clock-page-replacement-policy/
    */

    // --- Second Chance Implementation ---
    bool foundInSC = false;
    // Check if the page already exists in the Second Chance cache
    for (i = 0; i < CACHE_SIZE; i++) {
      if (sc_cache[i].pageno ==
          page_num) { // Page is found in Second Chance cache
        foundInSC = true;
        sc_ref[i] = 1; // Set its reference bit since it was recently used
        break;
      }
    }
    if (!foundInSC) {
      // On a miss, search for a victim using the clock algorithm
      // Output page miss
      printf("%d\n", page_num);
      while (true) {
        // If an empty slot is found, use it immediately
        if (sc_cache[sc_index].pageno == -1) {
          sc_cache[sc_index].pageno =
              page_num;         // Place the new page in the empty slot
          sc_ref[sc_index] = 1; // Set reference bit for the new page
          sc_faults++;          // Increment Second Chance page fault count
          sc_index = (sc_index + 1) % CACHE_SIZE; // Advance clock pointer
          break;
        }
        // If the current page has a reference bit of 0, it can be replaced
        if (sc_ref[sc_index] == 0) {
          sc_cache[sc_index].pageno =
              page_num;         // Replace the page at the clock pointer
          sc_ref[sc_index] = 1; // Set reference bit for the new page
          sc_faults++;          // Increment Second Chance page fault count
          sc_index = (sc_index + 1) % CACHE_SIZE; // Advance clock pointer
          break;
        }
        // If the reference bit is set (1), give the page a second chance by
        // clearing the bit
        sc_ref[sc_index] = 0;
        sc_index = (sc_index + 1) %
                   CACHE_SIZE; // Advance clock pointer and check next page
      }
    }
  }

  printf("Second Chance Total Page Faults: %d\n", sc_faults);

  return 0;
}
