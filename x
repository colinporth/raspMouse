CXX      := arm-linux-gnueabihf-g++
STRIP    := arm-linux-gnueabihf-strip

SRC       =  mouse.cpp ../shared/cLog.cpp

CFLAGS   += -std=c++0x -O3 -fPIC \
	    -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \

INCLUDES += -I ../DVB/include \
	    -I /SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/include \

LDFLAGS  += -L /SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/lib/arm-linux-gnueabihf \
	    -l pthread

OBJS     += $(filter %.o,$(SRC:.cpp=.o))

all:    mouse

%.o:    %.cpp ../shared/decoders/cTransportStream.h x
	@rm -f $@
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

mouse:      $(OBJS)
	$(CXX) $(LDFLAGS) -o mouse $(OBJS)
	$(STRIP) mouse

clean:
	@rm -f *.o
	@rm -f mouse
