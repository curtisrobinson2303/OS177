# The 'all' target depends on the three executables
all: fifo lru sec_chance

# Build the FIFO executable from fifo.c
fifo: fifo.c
	@gcc -o fifo fifo.c

# Build the LRU executable from lru.c
lru: lru.c
	@gcc -o lru lru.c

# Build the Second Chance executable from sec_chance.c
sec_chance: sec_chance.c
	@gcc -o sec_chance sec_chance.c

# Clean up the compiled executables and any .out files
clean:
	@rm -f fifo lru sec_chance *.out
