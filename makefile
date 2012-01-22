CC = g++
CFLAGS = -Wall -c
PACKAGES = clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3 clanGL-2.3 clanGL1-2.3
LIBS = `pkg-config --cflags --libs $(PACKAGES)`
RM = /bin/rm -f

#Ehhez a sorhoz kell hozzaadni a forrasokbol keszult objectfileok helyet. 
OBJS = src/main.o src/precomp.o src/bomberman.o src/player.o

PROG = bomberman

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROG) -pthread

src/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS) -pthread

all:
	$(PROG)

clean:
	$(RM) $(PROG) $(OBJS)
