CC=gcc

install:
	$(CC) -O2 elofetch.c -o /usr/bin/elofetch
	mkdir -p ~/.config/
	mkdir -p ~/.config/elofetch/
	cp /proc/cpuinfo ~/.config/elofetch/cpuinfo
	xdpyinfo | awk '/dimensions:/ { print $2 }' > ~/.config/elofetch/resolution
	lspci | grep VGA | grep -o '\[[^]]*]' | tail -c +2 | head -c -2 > ~/.config/elofetch/gpu
clean:
	rm -f /usr/bin/elofetch
	rm -rf ~/.config/elofetch
