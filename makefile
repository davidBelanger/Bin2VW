CC = clang
#The -Ofast might not work with older versions of gcc; in that case, use -O2
CFLAGS = -lm -O2 -march=native -Wall -funroll-loops 
# -Wno-unused-result

all: bin2vw

bin2vw : bin2vw.c
	$(CC) bin2vw.c -o bin2vw $(CFLAGS)

clean:
	rm -rf bin2vw
