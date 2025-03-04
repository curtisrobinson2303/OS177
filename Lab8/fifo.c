// Name: Curtis Robinson
// Date: March 4th 2025
// Title: Lab8 – Page Replacement First in First Out Algorithm
// Description: This file implements the first in first out algorithm described
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

  // FIFO cache variables
  ref_page cache[CACHE_SIZE];
  int fifo_faults = 0;
  int fifo_index = 0; // tracks the oldest page position in FIFO

  char pageCache[100];
  int i;

  // Initialize FIFO, LRU and Second Chance caches and their tracking arrays
  for (i = 0; i < CACHE_SIZE; i++) {
    cache[i].pageno = -1; // FIFO cache initialization
  }

  while (fgets(pageCache, 100, stdin)) {
    int page_num = atoi(pageCache);

    /*
    Page Replacement Implementation Goes Here
    FIFO:
      FIFO (First In First Out): is the simplest page replacement algorithm that
    keeps track of all the pages in the memory in a queue with the oldest page
    at the front of the queue. On a page fault, it replaces the page that has
    been present in memory for the longest time.
    https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-2-fifo/
    */

    // --- FIFO Implementation ---
    bool foundInFIFO = false;
    for (i = 0; i < CACHE_SIZE; i++) {
      if (cache[i].pageno ==
          page_num) { // Check if the page exists in FIFO cache
        foundInFIFO = true;
        break; // Page found, exit loop
      }
    }
    if (foundInFIFO == false) {
      printf("%d\n", page_num);
      // Page fault: insert the new page at the fifo_index and update the index
      // circularly
      cache[fifo_index].pageno = page_num;
      fifo_faults++; // Increment FIFO page fault count
      fifo_index = (fifo_index + 1) %
                   CACHE_SIZE; // Advance FIFO index (wrap-around if needed)
    }
  }

  printf("FIFO Total Page Faults: %d\n", fifo_faults);

  return 0;
}
