#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <errno.h>
#include <stdint.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#define BOLD_RED "\x1b[1m\033[31m"
#define BOLD_GREEN "\x1b[1m\033[32m"
#define BOLD_YELLOW "\x1b[1m\033[33m"
#define BOLD_BLUE "\x1b[1m\033[34m"
#define BOLD_MAGENTA "\x1b[1m\033[35m"
#define BOLD_CYAN "\x1b[1m\033[36m"
#define BOLD_WHITE "\x1b[1m\033[37m"
#define BUFF 50
#define PROGRAM_NAME "elofetch"

char hostname[BUFF * 2], gpu[BUFF], bars[BUFF], distro[BUFF], path[BUFF * 2], CPU[BUFF], ram[BUFF], hdd[BUFF], colors[BUFF * 2], time[BUFF], res[15], gpu[BUFF], readStdout[BUFF];

uint8_t blank(const char *str) {
	for(uint8_t i = 0; i < strlen(str); i++)
		if(*(str + i) != ' ')
			return -1;

	return 0;
}

void remove_word(char *str, const char *sub) {
	short int len = strlen(sub);

	if((str = strstr(str, sub)) == NULL)
		return;

	while((str = strstr(str, sub)))
		memmove(str, str + len, strlen(str + len) + 1);
}

char *read_stdout(const char *cmd) {
	FILE *len = popen(cmd, "r");
	int c;
	size_t i = 0;

	while((c = fgetc(len)) != EOF) {
		if(i > 49) {
			pclose(len);
			*(readStdout + 49) = '\0';

			return readStdout;
		}

		*(readStdout + i) = c;
		i++;
	}

	*(readStdout + i) = '\0';
	pclose(len);

	return readStdout;
}

char *hostName() {
	FILE *file = fopen("/etc/hostname", "r");

	if(!file) return "unknown";

	uint8_t i = 0;
	int c;

	while((c = fgetc(file)) != EOF) {
		if(i > 97) {
			hostname[i] = '\0';
			fclose(file);

			return hostname;
		}

		hostname[i] = c;
		i++;
	}

	fclose(file);
	hostname[i] = '\0';

	return hostname;
}

char *generate_bars(short int a, short int b) {
	short int i;

	for(i = 0; i < (a + b + 1); i++)
		*(bars + i) = '-';

	return bars;
}

char *operating_system() {
	FILE *file = fopen("/etc/os-release", "r");

	if(!file) return "GNU/Linux";

	size_t len, n;
	char *line = NULL;

	while(getline(&line, &len, file) != -1)
		if(sscanf(line, "PRETTY_NAME=\"%50[^\"]s", distro) > 0)
			break;

	fclose(file);
	free(line);

	return distro;
}

void cp(const char *location) {
	FILE *cpuinfo = fopen("/proc/cpuinfo", "r");

	if(!cpuinfo) {
		perror(PROGRAM_NAME);
		exit(-1);
	}

	int c;
	size_t i = 0;

	while((c = fgetc(cpuinfo)) != EOF)
		i++;

	fclose(cpuinfo);

	char str[i + 1];
	i = 0;
	FILE *cpuinfo1 = fopen("/proc/cpuinfo", "r");

	if(!cpuinfo1) {
		perror(PROGRAM_NAME);
		exit(-1);
	}

	while((c = fgetc(cpuinfo1)) != EOF) {
		*(str + i) = c;
		i++;
	}

	*(str + i) = '\0';
	fclose(cpuinfo1);
	FILE *cpuinfo2 = fopen(location, "a");
	fprintf(cpuinfo2, "%s", str);
	fclose(cpuinfo2);
}

char *processor(const char *home) {
	uint8_t length = strlen(home) + 26;
	char path[length], directory[length];

	strcpy(path, home);
	strcat(path, "/.config/");

	if(access(path, F_OK) && ENOENT == errno)
		mkdir(path, S_IRWXU);

	strcat(path, "elofetch/");
	strcat(directory, home);
	strcat(directory, "/.config/elofetch/cpuinfo");

	if(access(path, F_OK) && ENOENT == errno) {
		mkdir(path, S_IRWXU);
		cp(directory);
		strcat(path, "cpuinfo");
	}
	else
		strcat(path, "cpuinfo");

	FILE *file = fopen(path, "r");
	uint8_t threads = 0;

	if(!file) {
		cp(path);
		file = fopen(path, "r");
	}

	size_t len, n, i;
	char model[BUFF], *line = NULL, *substr, *rm,
			 *intel[] = { "(R)", "(TM)", " Core", " CPU", },
			 *amd[] = { "(tm)", " processor", " Dual-Core", " Quad-Core", " Six-Core", " Eight-Core" };

	while(getline(&line, &len, file) != -1)
		if(sscanf(line, "model name      : %50[^\n]s", model) > 0)
			threads++;

	fclose(file);

	if(strncasecmp(model, "intel", 5) == 0) {
		rm = strchr(model, '@');

		if(rm)
			*rm = '\0';

		for(i = 0; i < sizeof(intel) / sizeof(*intel); i++)
			remove_word(model, intel[i]);
	}
	else if(strncasecmp(model, "amd", 3)) {
		for(i = 0; i < sizeof(amd) / sizeof(*amd); i++)
			remove_word(model, amd[i]);
	}

	char *line1 = NULL;
	size_t len1;
	float frequency;
	FILE *cpu_freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");

	if(!cpu_freq) {
		snprintf(CPU, BUFF, "%s(%d)", model, threads);
	}
	else {
		if(getline(&line1, &len1, cpu_freq) != -1)
			sscanf(line1, "%f", &frequency);

		frequency = frequency / 1000 / 1000;
		fclose(cpu_freq);
		snprintf(CPU, BUFF, "%s(%d) @ %.2fGHz", model, threads, frequency);
	}
	free(line);
	free(line1);

	return CPU;
}

char *memory() {
	FILE *file = fopen("/proc/meminfo", "r");

	if(!file) return "unknown";

	int used_ram, memtotal, memfree, buffers, cached, shmem, sreclaimable, perc;
	size_t len;
	char *line = NULL;

	while(getline(&line, &len, file) != -1) {
		sscanf(line, "MemTotal: %d", &memtotal);
		sscanf(line, "MemFree: %d", &memfree);
		sscanf(line, "Buffers: %d", &buffers);
		sscanf(line, "Cached: %d", &cached);
		sscanf(line, "Shmem: %d", &shmem);
		sscanf(line, "SReclaimable: %d", &sreclaimable);
	}

	fclose(file);
	free(line);

	used_ram = (memtotal - memfree - buffers - cached + shmem - sreclaimable) / 1024;
	memtotal /= 1024;
	perc = (float)used_ram / (float)memtotal * 100;

	snprintf(ram, BUFF, "%dMiB / %dMiB (%d%%)", used_ram, memtotal, perc);

	return ram;
}

char *storage() {
	struct statvfs fs;

	if(statvfs(".", &fs)) {
		perror(PROGRAM_NAME);
		exit(-1);
	}

	float total = (float)fs.f_blocks * (float)fs.f_frsize / 1024 / 1024 / 1024,
				free = total - (float)fs.f_bsize * (float)fs.f_bfree / 1024 / 1024 / 1024,
				perc = free / total * 100;

	snprintf(hdd, BUFF, "%.1fGiB / %.1fGiB (%.0f%%)", free, total, perc);

	return hdd;
}

char *resolution(const char *home) {
	uint8_t n = strlen(home) + 29;
	memset(path, '\0', n);
	strcat(path, home);
	strcat(path, "/.config/elofetch/resolution");

	FILE *file = fopen(path, "r"),
			 *file1;

	if(!file) {
		file1 = fopen(path, "a");
		const char *stdout = read_stdout("/bin/xdpyinfo | awk '/dimensions:/ { print $2 }'");
		fprintf(file1, "%s", stdout);
		fclose(file1);
	}

	file = fopen(path, "r");
	char *line = NULL;
	size_t len;

	if(getline(&line, &len, file) != -1)
		sscanf(line, "%15s", res);

	fclose(file);
	free(line);
	*(res + 14) = '\0';

	return res;
}

char *GPU(const char *home) {
	DIR *dir = opendir("/proc/driver/nvidia/gpus/");
	struct dirent *directory;
	char path[BUFF * 2];

	if(!dir) {
		strcat(path, home);
		strcat(path, "/.config/elofetch/gpu");

		FILE *gpu_read = fopen(path, "r");
		char cmd[50], *line = NULL;
		size_t len;
		if(!gpu_read) {
			strcpy(cmd, read_stdout("echo $(/bin/grep -oE '\\[.*\\]' <<< \"$(/bin/lspci | /bin/cut -f1 | /bin/grep VGA)\" | /bin/sed 's/\\[//;s/\\]//' | /bin/sed -n -e '1h;2,$H;${g;s/\\n/, /g' -e 'p' -e '}')"));
			FILE *file = fopen(path, "a");
			fprintf(file, "%s", cmd);
			fclose(file);
			FILE *file1 = fopen(path, "r");

			if(!file1) return "unknown";

			if(getline(&line, &len, file1) != -1)
				sscanf(line, "%50[^\n]s", gpu);

			free(line);
			fclose(file1);

			return gpu;
		}

		if(getline(&line, &len, gpu_read) != -1)
			sscanf(line, "%50[^\n]s", gpu);

		free(line);
		fclose(gpu_read);

		return gpu;
	}

	while((directory = readdir(dir)) != NULL) {
		if(strncmp(directory->d_name, ".", 2) == 0 || strncmp(directory->d_name, "..", 3) == 0)
      continue;

		strcpy(path, "/proc/driver/nvidia/gpus/");
		strcat(path, directory->d_name);
		strcat(path, "/information");
	}

	FILE *file = fopen(path, "r");
	size_t len;
	char *line = NULL;

	if(getline(&line, &len, file) != -1)
		sscanf(line, "Model:           %50[^\n]s", gpu);

	return gpu;
}

int packages(const char *path) {
	DIR *dir = opendir(path);

	size_t i = 0;
	struct dirent *directory;

	if(!dir)
		return 0;

	while((directory = readdir(dir)) != NULL && i < 99999999)
		i++;

	closedir(dir);

	return i - 3;
}

char *uptime() {
	struct sysinfo os_info;
	int err = sysinfo(&os_info);
	unsigned int uis = os_info.uptime, days, hours, minutes;

	days = uis / 86400;
	uis %= 86400;
	hours = uis / 3600;
	uis %= 3600;
	minutes = uis / 60;
	uis %= 60;

	if(err) {
		perror(PROGRAM_NAME);
		exit(-1);
	}

	if(days)
		snprintf(time, BUFF, "%u days, %u hours, %u mins", days, hours, minutes);
	else if(!days && hours)
		snprintf(time, BUFF, "%u hours, %u mins", hours, minutes);
	else if(!days && !hours && minutes)
		snprintf(time, BUFF, "%u mins", minutes);
	
	return time;
}

char *colors1() {
	char *clr = colors;

	for(uint8_t i = 0; i < 8; i++) {
		sprintf(clr, "\e[4%hhum   ", i);
		clr += 8;
	}

	snprintf(clr, 5, "\e[0m");

	return colors;
}

char *colors2() {
	char *clr = colors;
	
	for(uint8_t i = 8; i < 16; i++) {
		sprintf(clr, "\e[48;5;%hhum   ", i);
		clr += 12 + (i >= 10 ? 1 : 0);
	}

	snprintf(clr, 5, "\e[0m");

	return colors;
}

static char *pacman() {
	int i = packages("/var/lib/pacman/local/");
	char *pkg = malloc(BUFF / 2);
	snprintf(pkg, BUFF / 2, "%d (pacman)", i);

	return pkg;
}

void elofetch(const char *distro, const char *logo[], const char *COLOR, const char *pkgs, uint8_t n, const char *home) {
	struct utsname uts;

  if(uname(&uts)) {
    perror(PROGRAM_NAME);
    exit(-1);
  }

	const char *user = getenv("USER"),
				*host = hostName(),
				*bars = generate_bars(strlen(user), strlen(host)),
				*kernel = uts.release,
				*architecture = uts.machine,
				*shell = strrchr(getenv("SHELL"), '/') + 1,
				*cpu = processor(home),
				*gpu = GPU(home),
				*terminal = getenv("TERM");

	for(uint8_t i = 0; i < n; i++) {
		if(*(logo + i) == NULL) {
			puts(RESET);
			exit(-1);
		}

		printf("%s%s", COLOR, logo[i]);

		switch(i) {
			case 0:
				printf("%s" RESET "@%s%s", user, COLOR, host);
				break;
			case 1:
				printf(RESET "%s\x0A", bars);
				break;
			case 2:
				printf("%sOS" RESET ": %s %s\x0A", COLOR, distro, architecture);
				break;
			case 3:
				printf("%sKernel" RESET ": %s\x0A", COLOR, kernel);
				break;
			case 4:
				printf("%sUptime" RESET ": %s\x0A", COLOR, uptime());
				break;
			case 5:
				printf("%sPackages" RESET ": %s\x0A", COLOR, pkgs);
				break;
			case 6:
				printf("%sShell" RESET ": %s\x0A", COLOR, shell);
				break;
			case 7:
				printf("%sResolution" RESET ": %s\x0A", COLOR, resolution(home));
				break;
			case 8:
				printf("%sTerminal" RESET ": %s\x0A", COLOR, terminal);
				break;
			case 9:
				printf("%sCPU" RESET ": %s\x0A", COLOR, cpu);
				break;
			case 10:
				if(blank(gpu))
					printf("%sGPU" RESET ": %s\x0A", COLOR, gpu);
				else
					putchar('\x0A');

				break;
			case 11:
				printf("%sRAM" RESET ": %s\x0A", COLOR, memory());
				break;
			case 12:
				printf("%sStorage" RESET ": %s\x0A", COLOR, storage());
				break;
			case 13:
				putchar('\x0A');
				break;
			case 14:
				printf("%s\x0A", colors1());
				break;
			case 15:
				printf("%s\x0A", colors2());
				break;
			default:
				putchar('\x0A');
		}
	}
	puts(RESET);
}

void linux_distro(const char *home) {
	const char *distro = operating_system();
	char *pkgs;

	if(strncasecmp(distro, "arch", 4) == 0) {
		#include "distro/arch.h"

		pkgs = pacman();
		elofetch(distro, arch, BOLD_CYAN, pkgs, 19, home);
	}
	else if(strncasecmp(distro, "parrot", 5) == 0) {
		#include "distro/parrot.h"

		pkgs = pacman();
		elofetch(distro, parrot, BOLD_CYAN, pkgs, 24, home);
	}
	else if(strncasecmp(distro, "debian", 6) == 0) {
		#include "distro/debian.h"

		pkgs = pacman();
		elofetch(distro, debian, BOLD_RED, pkgs, 17, home);
	}
	else if(strncasecmp(distro, "manjaro", 7) == 0) {
		#include "distro/manjaro.h"

		pkgs = pacman();
		elofetch(distro, manjaro, BOLD_GREEN, pkgs, 14, home);
	}
	else if(strncasecmp(distro, "ubuntu", 6) == 0) {
		#include "distro/ubuntu.h"

		pkgs = pacman();
		elofetch(distro, ubuntu, BOLD_RED, pkgs, 20, home);
	}
	else if(strncasecmp(distro, "linux mint", 10) == 0) {
		#include "distro/mint.h"

		pkgs = pacman();
		elofetch(distro, mint, BOLD_GREEN, pkgs, 19, home);
	}
	else if(strncasecmp(distro, "pop!_os", 7) == 0) {
		#include "distro/popos.h"

		pkgs = pacman();
		elofetch(distro, pop_os, BOLD_BLUE, pkgs, 20, home);
	}
	else if(strncasecmp(distro, "kali", 4) == 0) {
		#include "distro/kali.h"

		pkgs = pacman();
		elofetch(distro, kali, BOLD_BLUE, pkgs, 20, home);
	}
}

int main(int argc, const char **argv) {
  const char *home = getenv("HOME");

	if(argv[1] && strncmp(argv[1], "--reconfigure", 14) == 0) {
    	uint8_t len = strlen(home) + 30;
			char cmd[len];
			snprintf(cmd, len, "/bin/rm -rf %s/.config/elofetch/", home);
			system(cmd);
  		puts("Elofetch: successfully reconfigured!");
			return 0;
	}

	linux_distro(home);

	return 0;
}
