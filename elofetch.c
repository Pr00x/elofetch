#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

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

#define BUFF 100

#ifdef __linux__
	#include<unistd.h>
	#include<sys/utsname.h>
	#include<sys/sysinfo.h>
	#include<sys/stat.h>
	#include<sys/statvfs.h>
	#include<dirent.h>
	#include<errno.h>
	#define PROGRAM_NAME "elofetch"
	#define OS 1
#elif _WIN32
	#include<windows.h>
	#define OS 2
#else
	#define OS 0
#endif

int blank(const char *str) {
	size_t i;

	for(i = 0; i < strlen(str); i++)
		if(!isspace(*(str + i)))
			return -1;

	return 0;
}

void remove_word(char *str, const char *sub) {
	size_t len = strlen(sub);

	if((str = strstr(str, sub)) == NULL)
		return;

	while((str = strstr(str, sub)))
		memmove(str, str + len, strlen(str + len) + 1);
}

static char *read_stdout(const char *cmd) {
	FILE *len = popen(cmd, "r");
	char *str;
	str = malloc(BUFF / 2);
	char c;
	size_t i = 0;

	while((c = fgetc(len)) != EOF) {
		if(i > 49) {
			pclose(len);
			*(str + i) = '\0';

			return str;
		}

		*(str + i) = c;
		i++;
	}

	*(str + i) = '\0';

	pclose(len);

	return str;
}

static char *hostname() {
	FILE *file = fopen("/etc/hostname", "r");
	char *hostname;

	if(!file) {
		hostname = "unknown";

		return hostname;
	}

	size_t i = 0;
	int c;

	hostname = malloc(BUFF);

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
	hostname = realloc(hostname, i + 1);
	hostname[i] = '\0';

	return hostname;
}

static char *generate_bars(size_t a, size_t b) {
	size_t i;
	char *str;
	str = malloc(BUFF);

	for(i = 0; i < (a + b + 1); i++) {
		if(i == a + b) {
			str = realloc(str, i + 1);
			*(str + i) = '\0';

			return str;
		}

		*(str + i) = '-';
	}

	return str;
}

static char *operating_system() {
	FILE *file = fopen("/etc/os-release", "r");
	char *distro;

	if(!file) {
		distro = "Linux";

		return distro;
	}

	size_t len, n;
	char *pretty_name, *line;

	pretty_name = malloc(BUFF);
	line = NULL;

	while(getline(&line, &len, file) != -1)
		if(sscanf(line, "PRETTY_NAME=\"%50[^\"]s", pretty_name) > 0)
			break;

	fclose(file);
	n = strlen(pretty_name) + 1;
	distro = malloc(n);
	snprintf(distro, n, "%s", pretty_name);
	free(line);
	free(pretty_name);

	return distro;
}

void cp(const char *location) {
	FILE *cpuinfo = fopen("/proc/cpuinfo", "r");

	if(!cpuinfo) {
		perror("elofetch");
		exit(-1);
	}

	int c;
	size_t i = 0;

	while((c = fgetc(cpuinfo)) != EOF)
		i++;

	fclose(cpuinfo);

	char *str = malloc(i + 1);
	i = 0;
	FILE *cpuinfo1 = fopen("/proc/cpuinfo", "r");

	if(!cpuinfo1) {
		perror("elofetch");
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
	free(str);
	fclose(cpuinfo2);
}

static char *processor() {
	char *CPU, *path, *directory;
	const char *home = getenv("HOME");
	size_t length = strlen(home) + 26;

	path = malloc(length); // ~/.config/elofetch/cpuinfo
	directory = malloc(length);
	memset(path, '\0', length);
	memset(directory, '\0', length);
	strcpy(path, home);
	strcat(path, "/.config/");

	if(access(path, F_OK) != 0)
		if(ENOENT == errno)
			mkdir(path, S_IRWXU);

	strcat(path, "elofetch/");
	strcat(directory, home);
	strcat(directory, "/.config/elofetch/cpuinfo");

	if(access(path, F_OK) != 0) {
		if(ENOENT == errno) {
			mkdir(path, S_IRWXU);
			cp(directory);
			strcat(path, "cpuinfo");
		}
	}
	else
		strcat(path, "cpuinfo");

	FILE *file = fopen(path, "r");
	int threads = 0;

	if(!file) {
		cp(path);
		file = fopen(path, "r");
	}

	free(directory);

	size_t len, n, i;
	char *model, *line, *substr, *rm,
			 *intel[] = { "(R)", "(TM)", " Core", " CPU", },
			 *amd[] = { "(tm)", " processor", " Dual-Core", " Quad-Core", " Six-Core", " Eight-Core" };

	model = malloc(BUFF);
	line = NULL;

	while(getline(&line, &len, file) != -1)
		if(sscanf(line, "model name      : %50[^\n]s", model) > 0)
			threads++;

	fclose(file);
	n = strlen(model) + 1;
	CPU = malloc(n);

	if(strncasecmp(model, "Intel", 5) == 0) {
		rm = strchr(model, '@');

		if(rm != NULL)
			*rm = '\0';

		for(i = 0; i < sizeof(intel) / sizeof(*intel); i++)
			remove_word(model, intel[i]);
	}
	else if(strncasecmp(model, "AMD", 3) == 0) {
		for(i = 0; i < sizeof(amd) / sizeof(*amd); i++)
			remove_word(model, amd[i]);
	}

	char *line1 = NULL;
	size_t len1;
	float frequency;
	FILE *cpu_freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");

	if(!cpu_freq) {
		snprintf(CPU, n, "%s(%d)", model, threads);
	}
	else {
		if(getline(&line1, &len1, cpu_freq) != -1)
			sscanf(line1, "%f", &frequency);

		frequency = frequency / 1000 / 1000;
		fclose(cpu_freq);
		snprintf(CPU, n, "%s(%d) @ %.2fGHz", model, threads, frequency);
	}
	free(path);
	free(line);
	free(model);
	free(line1);

	return CPU;
}

static char *memory() {
	char *ram;
	FILE *file = fopen("/proc/meminfo", "r");

	if(!file) {
		ram = "unknown";

		return ram;
	}

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

	ram = malloc(BUFF);
	snprintf(ram, BUFF, "%dMiB / %dMiB (%d%%)", used_ram, memtotal, perc);

	return ram;
}

static char *storage() {
	struct statvfs fs;
	char *hdd;

	if(statvfs(".", &fs)) {
		perror(PROGRAM_NAME);

		return "unknown";
	}

	float total = (float)fs.f_blocks * (float)fs.f_frsize / 1024 / 1024 / 1024,
				free = total - (float)fs.f_bsize * (float)fs.f_bfree / 1024 / 1024 / 1024,
				perc = free / total * 100;


	hdd  = malloc(BUFF / 2);
	snprintf(hdd, BUFF / 2, "%.1fGiB / %.1fGiB (%.0f%%)", free, total, perc);

	return hdd;
}

static char *resolution(const char *home) {
	size_t n = strlen(home) + 29;
	char *path = malloc(n);
	const char *output;
	memset(path, '\0', n);
	strcat(path, home);
	strcat(path, "/.config/elofetch/resolution");

	FILE *file = fopen(path, "r"),
			 *file1;

	if(!file) {
		file1 = fopen(path, "a");
		output = read_stdout("/bin/xdpyinfo | awk '/dimensions:/ { print $2 }'");
		fprintf(file1, "%s", output);
		fclose(file1);
	}

	file = fopen(path, "r");
	free(path);

	char *res = malloc(26),
			 *line = NULL;
	size_t len;

	if(getline(&line, &len, file) != -1)
		sscanf(line, "%25s", res);

	fclose(file);
	free(line);

	*(res + strlen(res)) = '\0';

	return res;
}

static char *GPU(const char *home) {
	DIR *dir = opendir("/proc/driver/nvidia/gpus/");
	struct dirent *directory;
	char *path = malloc(BUFF),
			 *gpu = malloc(BUFF);
	memset(path, '\0', BUFF / 2);

	if(!dir) {
		strcat(path, home);
		strcat(path, "/.config/elofetch/gpu");

		FILE *gpu_read = fopen(path, "r");
		char *cmd,
				 *line = NULL;
		size_t len;
		if(!gpu_read) {
			cmd = strdup(read_stdout("echo $(/bin/grep -oE '\\[.*\\]' <<< \"$(/bin/lspci | /bin/cut -f1 | /bin/grep VGA)\" | /bin/sed 's/\\[//;s/\\]//' | /bin/sed -n -e '1h;2,$H;${g;s/\\n/, /g' -e 'p' -e '}')"));
			FILE *file = fopen(path, "a");

			fprintf(file, "%s", cmd);
			fclose(file);
			free(cmd);

			FILE *file1 = fopen(path, "r");

			free(path);

			if(!file1)
				return "   ";

			if(getline(&line, &len, file1) != -1)
				sscanf(line, "%60[^\n]s", gpu);

			free(line);
			fclose(file1);

			return gpu;
		}

		if(getline(&line, &len, gpu_read) != -1)
			sscanf(line, "%60[^\n]s", gpu);

		free(path);
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

	if(getline(&line, &len, file) != -1) {
		sscanf(line, "Model:           %60[^\n]s", gpu);
	}

	return gpu;
}

int packages(const char *path) {
	DIR *dir = opendir(path);

	size_t i = 0;
	struct dirent *directory;

	if(!dir)
		return 0;

	while((directory = readdir(dir)) != NULL)
		i++;

	closedir(dir);

	return i - 3;
}

static char *uptime() {
	struct sysinfo os_info;
	int err = sysinfo(&os_info);
	char *time = malloc(BUFF / 2);
	unsigned int uis = os_info.uptime, days, hours, minutes;

	days = uis / 86400;
	uis %= 86400;
	hours = uis / 3600;
	uis %= 3600;
	minutes = uis / 60;
	uis %= 60;

	if(err) {
		perror("elofetch");
		exit(1);
	}

	if(days)
		snprintf(time, BUFF / 2, "%u days, %u hours, %u mins", days, hours, minutes);
	else if(!days && hours)
		snprintf(time, BUFF / 2, "%u hours, %u mins", hours, minutes);
	else if(!days && !hours && minutes)
		snprintf(time, BUFF / 2, "%u mins", minutes);
	return time;
}

static char *colors1() {
	char *colors = malloc(BUFF),
			 *clr = colors;
	size_t i;

	for(i = 0; i < 8; i++) {
		sprintf(clr, "\e[4%zum   ", i);
		clr += 8;
	}

	snprintf(clr, 5, "\e[0m");

	return colors;
}

static char *colors2() {
	char *colors = malloc(BUFF),
			 *clr = colors;
	size_t i;

	for(i = 8; i < 16; i++) {
		sprintf(clr, "\e[48;5;%zum   ", i);
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

void elofetch(const char *distro, const char *logo[], const char *COLOR, const char *pkgs, int n, const char *home) {
	struct utsname uts;

  if(uname(&uts)) {
    perror(PROGRAM_NAME);

    exit(-1);
  }

	const char *user = getenv("USER");
  const char *host = hostname();
	const char *bars = generate_bars(strlen(user), strlen(host));
  const char *kernel = uts.release;
  const char *architecture = uts.machine;
  const char *shell = strrchr(getenv("SHELL"), '/') + 1;
	const char *cpu = processor();
	const char *gpu = GPU(home);
  const char *terminal = getenv("TERM");
	size_t i;

	for(i = 0; i < n; i++) {
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
	char *distro = operating_system();
	char *pkgs;

	if(strncmp(distro, "Arch", 4) == 0) {
		#include"distro/arch.h"

		pkgs = pacman();
		elofetch(distro, arch, BOLD_CYAN, pkgs, 19, home);
	}
	else if(strncmp(distro, "Parrot", 5) == 0) {
		#include"distro/parrot.h"

		pkgs = pacman();
		elofetch(distro, parrot, BOLD_CYAN, pkgs, 24, home);
	}
	else if(strncmp(distro, "Debian", 6) == 0) {
		#include"distro/debian.h"

		pkgs = pacman();
		elofetch(distro, debian, BOLD_RED, pkgs, 17, home);
	}
	else if(strncmp(distro, "Manjaro", 7) == 0) {
		#include"distro/manjaro.h"

		pkgs = pacman();
		elofetch(distro, manjaro, BOLD_GREEN, pkgs, 14, home);
	}
	else if(strncmp(distro, "Ubuntu", 6) == 0) {
		#include"distro/ubuntu.h"

		pkgs = pacman();
		elofetch(distro, ubuntu, BOLD_RED, pkgs, 20, home);
	}
	else if(strncmp(distro, "Linux Mint", 10) == 0) {
		#include"distro/mint.h"

		pkgs = pacman();
		elofetch(distro, mint, BOLD_GREEN, pkgs, 19, home);
	}
	else if(strncasecmp(distro, "Pop!_OS", 7) == 0) {
		#include"distro/popos.h"

		pkgs = pacman();
		elofetch(distro, pop_os, BOLD_BLUE, pkgs, 20, home);
	}
	else if(strncmp(distro, "Kali", 4) == 0) {
		#include"distro/kali.h"

		pkgs = pacman();
		elofetch(distro, kali, BOLD_BLUE, pkgs, 20, home);
	}
}

void windows() {
	// Coming Soon
}

int main(int argc, const char *argv[]) {
  const char *home = getenv("HOME");
	char *cmd;

	if(argv[1])
		if(strncmp(argv[1], "--reconfigure", 14) == 0) {
    	cmd = malloc(strlen(home) + 32);
  		strcpy(cmd, "/bin/rm -rf ");
  		*(cmd + 12) = '\0';
			strcat(cmd, home);
    	strcat(cmd, "/.config/elofetch/");
			system(cmd);
			free(cmd);
  }

	switch(OS) {
		case 1:
			linux_distro(home);
			break;
		case 2:
			windows();
			break;
		default:
			return -1;
	}

	return 0;
}
