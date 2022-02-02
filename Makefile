$(CC) = gcc

# Compiling main file
sniffer:
	$(CC) src/main.c -o sniffer

thread:
	$(CC) src/main.c -o sniffer -pthread

clean:
	rm sniffer

.PHONY: sniffer clean

