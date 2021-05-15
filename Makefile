sf: sf.c
	cc sf.c -Wall -Wextra -O3 -o sf

install:
	cp sf /usr/bin

clean:
	rm -f sf
