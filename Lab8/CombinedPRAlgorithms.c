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

  // LRU cache variables
  ref_page lru_cache[CACHE_SIZE];
  int lru_faults = 0;
  int lru_time[CACHE_SIZE]; // stores the "last used" time for each page in the
                            // LRU cache
  int time_counter = 0;     // global counter for LRU time stamps

  // Second Chance cache variables
  ref_page sc_cache[CACHE_SIZE];
  int sc_ref[CACHE_SIZE]; // array to store reference bits for Second Chance
  int sc_faults = 0;      // counter for Second Chance page faults
  int sc_index = 0;       // clock hand pointer for Second Chance

  char pageCache[100];
  int i;

  // Initialize FIFO, LRU and Second Chance caches and their tracking arrays
  for (i = 0; i < CACHE_SIZE; i++) {
    cache[i].pageno = -1;     // FIFO cache initialization
    lru_cache[i].pageno = -1; // LRU cache initialization
    lru_time[i] = 0;          // LRU usage time is initially 0
    sc_cache[i].pageno = -1;  // Second Chance cache initialization
    sc_ref[i] = 0; // All Second Chance reference bits are initially 0
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

  // Print the final page fault counts for all algorithms
  printf("FIFO Total Page Faults: %d\n", fifo_faults);
  printf("LRU Total Page Faults: %d\n", lru_faults);
  printf("Second Chance Total Page Faults: %d\n", sc_faults);

  return 0;
}
