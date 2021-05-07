#include <stdio.h>
#include <time.h>
#include <inttypes.h>

uint64_t getUptime(){
	#ifdef __FreeBSD__
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
