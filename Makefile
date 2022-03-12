CC=gcc

install:
	$(CC) -O2 elofetch.c -o /usr/bin/elofetch
	mkdir -p ~/.config/
	mkdir -p ~/.config/elofetch/
	cp /proc/cpuinfo ~/.config/elofetch/cpuinfo
	xdpyinfo | awk '/dimensions:/ { print $2 }' > ~/.config/elofetch/resolution
clean:
	rm -f /usr/bin/elofetch
	rm -rf ~/.config/elofetch
