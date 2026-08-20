CC = gcc
CSTANDARD = -std=gnu23
CFLAGS = -Wall -Wextra -Wpedantic -Werror

DEBUGFLAGS = -g -Og -00 
DSAN = -fsanitize=address,leak,undefined

RELEASEFLAGS = -O3 -flto=auto -march=native -mtune=native -funroll-loops -fomit-frame-pointer -fno-plt

SRC = main.c
EXE = mcpu

debugsan: $(SRC)
	$(CC) $(CSTANDARD) $(CFLAGS) $(DEBUGFLAGS) $(DSAN) $(SRC) -o $(EXE)

debug: $(SRC)
	$(CC) $(CSTANDARD) $(CFLAGS) $(DEBUGFLAGS) $(SRC) -o $(EXE)

release: $(SRC)
	$(CC) $(CSTANDARD) $(CFLAGS) $(RELEASEFLAGS) $(SRC) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean : rm $(EXE)