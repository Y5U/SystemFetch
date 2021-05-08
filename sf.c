#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <inttypes.h>

/* help links:
 * https://www.tutorialspoint.com/unix_system_calls/sysinfo.htm
 */

uint64_t getUptime(){
        #ifdef __FreeBSD__
		#include <time.h>
                struct timespec time_spec;

                if (clock_gettime(CLOCK_UPTIME_PRECISE, &time_spec) != 0)
                	return 0;

		uint64_t uptime = time_spec.tv_sec;

		return uptime;
	#elif __linux__
		#include <sys/sysinfo.h>
        	struct sysinfo sys;

		sysinfo(&sys);
		
		return sys.uptime;
	#endif
}

char *getSecondToken(char str[], const char delim[]) {
	strtok(str, delim);
	return strtok(NULL, delim);
}

void remove_all_chars(char* str, char c) {
	char *pr = str, *pw = str;
	while (*pr) {
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

char *getOS(){
	char buff[70], *res = malloc (sizeof (char) * 255);
	FILE *osr;
	if(!(osr = fopen("/etc/os-release", "r"))) { return "Unable to find OS"; }

	fgets(buff, 70, (FILE*)osr);
	fclose(osr);

	res = getSecondToken(buff, "=");
	remove_all_chars(res, '\"');
	remove_all_chars(res, '\n');
	
	return res;
}

char *getRam(){
  	FILE *meminfo;
	if(!(meminfo = fopen("/proc/meminfo", "r"))) { return "Unable to get memory stats"; }
	char buff[255], buff2[255], *res = malloc (sizeof (char) * 255);

	fgets(buff, 255, (FILE*)meminfo);
	fgets(buff2, 255, (FILE*)meminfo);
	fgets(buff2, 255, (FILE*)meminfo);
	fclose(meminfo);
	int total = atoi(getSecondToken(buff, " ")) / 1024;
	int free = atoi(getSecondToken(buff2, " ")) / 1024;
	sprintf(res, "%dM / %dM", total - free, total);
	return res;
}

int main(){
	struct utsname name;
	uname(&name);
	
	printf("\033[1m\033[36m%s@\033[1m\033[37m%s\n", getenv("USER"),name.nodename);
	printf("\033[1m\033[36mos\t\033[0;37m%s\n", getOS());
	printf("\033[1m\033[36mkernel\t\033[0;37m%s\n", name.release);
	printf("\033[1m\033[36mshell\t\033[0;37m%s\n", getenv("SHELL"));
	printf("\033[1m\033[36mterm\t\033[0;37m%s\n", getenv("TERM"));
	printf("\033[1m\033[36muptime\t\033[0;37m%"PRIu64"h %"PRIu64"m\n", getUptime()/60/60, getUptime()/60 % 60);
	printf("\033[1m\033[36mmemory\t\033[0;37m%s\033[0m\n", getRam());

	return 0;
}
