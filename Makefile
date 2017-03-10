CFLAGS   += -D STANDALONE -D __STDC_CONSTANT_MACROS -D __STDC_LIMIT_MACROS -D TARGET_POSIX -D _LINUX \
	    -D PIC -D _REENTRANT -D _LARGEFILE64_SOURCE -D _FILE_OFFSET_BITS=64 \
	    -D HAVE_LIBOPENMAX=2 -D OMX -D OMX_SKIP64BIT -D USE_EXTERNAL_OMX -D HAVE_LIBBCM_HOST \
	    -D USE_EXTERNAL_LIBBCM_HOST -D USE_VCHIQ_ARM \
	    -U _FORTIFY_SOURCE \
	    -g -O2 -Wall -Wno-psabi -Wno-deprecated-declarations -fPIC -ftree-vectorize -pipe

LDFLAGS  += -lpthread -lrt -lm  \

INCLUDES += -I$(SDKSTAGE)/usr/local/include

OBJS = mouse.o ../shared/cLog.o evtest.o

all: mouse

%.o: %.c
	@rm -f $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cpp
	@rm -f $@
	$(CXX) $(CFLAGS) $(INCLUDES) -std=c++0x -c $< -o $@

mouse: $(OBJS)  $(LIB)
	$(CXX) -o $@ -Wl,--whole-archive $(OBJS) $(LDFLAGS) -Wl,--no-whole-archive -rdynamic

.PHONY: clean rebuild

rebuild:
	make clean && make

clean:
	@rm -f *.o
	@rm -f ../shared/*.o
	@rm -f mouse
