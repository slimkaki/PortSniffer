$(CC) = gcc

# Compiling main file
sniffer:
	$(CC) src/main.c -o sniffer

clean:
	rm sniffer