// mouse.cpp
//{{{  includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <thread>
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/poll.h>

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "../shared/cLog.h"
//}}}

//{{{
struct sMousePacket {
  uint8_t buttons;
  int8_t dx;
  int8_t dy;
  uint8_t n;
  };
//}}}
//{{{
void miliSleep (int milisec) {
  struct timespec req = { 0 };
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep (&req, (struct timespec *)NULL);
  }
//}}}

uint8_t mousedev_imps_seq[] = { 0xf3, 200, 0xf3, 100, 0xf3, 80 };
uint8_t mousedev_imex_seq[] = { 0xf3, 200, 0xf3, 200, 0xf3, 80 };

int main (int argc, char** argv) {

  cLog::Init ("", LOGINFO3);
  cLog::Log (LOGNOTICE, "mouse");

  int mScreenWidth = 800;
  int mScreenHeight = 480;

  int mMouseButtons = 0;
  int mMousex = mScreenWidth/2;
  int mMousey = mScreenHeight/2;

  int mMouseFd = open ("/dev/input/mouse0", O_RDWR);
  int bytes = write (mMouseFd, mousedev_imps_seq, sizeof(mousedev_imex_seq));

  while (true) {
    struct sMousePacket mousePacket;
    int bytes = read (mMouseFd, &mousePacket, sizeof(mousePacket));

    if (bytes < (int)sizeof(mousePacket))
      cLog::Log (LOGINFO1, "mouse bytes %d", bytes);

    else if (mousePacket.buttons & 8) {
      mMousex += mousePacket.dx;
      if (mMousex < 0)
        mMousex = 0;
      else if (mMousex > (int)mScreenWidth)
        mMousex = mScreenWidth;

      mMousey -= mousePacket.dy;
      if (mMousey < 0)
        mMousey = 0;
      else if (mMousey > (int)mScreenHeight)
        mMousey = mScreenHeight;

      mMouseButtons = mousePacket.buttons & 0x03;
      cLog::Log (LOGINFO1, "mouse %x %x %x - %d %d",
                 mousePacket.buttons, mousePacket.dx, mousePacket.dy, mMousex, mMousey);
      }

    else {
      read (mMouseFd, &mousePacket, 1); // Try to sync up again
      cLog::Log (LOGINFO1, "resysnc");
      }
    }

  return 0;
  }
