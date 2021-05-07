#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#ifdef __linux__
	#include <sys/sysinfo.h>
	struct sysinfo system;
	sysinfo(&system);
#endif
#include <string.h>
#include <pwd.h>

/* help links:
 * https://www.tutorialspoint.com/unix_system_calls/sysinfo.htm
 */

char *getOS(){
	int i = 0, pos = 7;
	char buff[70], *res = malloc (sizeof (char) * 255);
	FILE *osr;
	if(!(osr = fopen("/etc/os-release", "r"))) { return "Unable to find OS"; }

	fgets(buff, 70, (FILE*)osr);
	fclose(osr);

	while (i < 63 && buff[pos + i - 1] != '\"') {
		res[i] = buff[pos + i - 1];
		i++;
	} res[i] = '\0';
	
	return res;
}

const char *getUserName() {
  	uid_t uid = geteuid();
  	struct passwd *pw = getpwuid(uid);

  	if(pw) { return pw->pw_name; }
	return "";
}

char *getSecondToken(char str[], const char delim[]) {
	strtok(str, delim);
	return strtok(NULL, delim);
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

	printf("\033[1m\033[36m%s@\033[1m\033[37m%s\n", getUserName(),name.nodename);
	printf("\033[1m\033[36mos\t\033[0;37m%s\n", getOS());
	printf("\033[1m\033[36mkernel\t\033[0;37m%s\n", name.release);
	printf("\033[1m\033[36mshell\t\033[0;37m%s\n", getenv("SHELL"));
	printf("\033[1m\033[36muptime\t\033[0;37m%dh %dm\n", system.uptime/60/60, system.uptime/60 % 60);
	printf("\033[1m\033[36mmemory\t\033[0;37m%s\033[0m\n", getRam());

	return 0;
}
