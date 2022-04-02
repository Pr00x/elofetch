CC=gcc

install:
	sudo $(CC) -O2 elofetch.c -o /usr/bin/elofetch
	mkdir -p "${HOME}/.config/"
	mkdir -p "${HOME}/.config/elofetch/"
	cp /proc/cpuinfo ~/.config/elofetch/cpuinfo
	xdpyinfo | awk '/dimensions:/ { print $2 }' > ~/.config/elofetch/resolution
	lspci | grep VGA | grep -o '\[[^]]*]' | tail -c +2 | head -c -2 > ~/.config/elofetch/gpu
clean:
	sudo rm -f /usr/bin/elofetch
	sudo rm -rf ~/.config/elofetch
