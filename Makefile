sf: sf.c uptime.h
	cc sf.c -Wextra -O3 -o sf

install:
	cp sf /usr/bin
