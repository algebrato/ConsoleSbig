VERSION 	= 0
PATHLEVEL	= 0
SUBLEVEL	= 0
EXTRAVERSION 	= 
###############################################################################
ESEGUIBILE	:= ConsoleSbig
OBJ		:= src/ConsoleSbig.o src/csbigcam.o src/csbigimg.o src/getImage.o
CC		:= g++ 
FLAGS 		:= -O2 -g -std=c++11 -Wall
LIBS		:= -L /usr/local/lib -L /data/fits/cfitsio/lib/ -lm -lsbigudrv -lcfitsio -lm -lpthread
INCS		:= -I /usr/include/libusb-1.0/ -I /usr/include/libusb-1.0/ -I /data/fits/cfitsio 

src/%.o : src/%.cpp
	$(CC) ${LIBS} ${FLAGS} ${INCS} -c $< -o $@

${ESEGUIBILE}: ${OBJ}
	$(CC) ${LIBS} ${FLAGS} ${INCS} -o $@ $^	


.PHONY: clean

clean:
	rm -rf ${ESEGUIBILE} src/*.x src/*.out src/*.o
