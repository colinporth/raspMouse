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
  char buttons;
  char dx;
  char dy;
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

int main (int argc, char** argv) {

  cLog::Init ("", LOGINFO3);
  cLog::Log (LOGNOTICE, "mouse");

  int mMouseFd = open ("/dev/input/mouse0", O_RDONLY | O_NONBLOCK);
  int mScreenWidth = 800;
  int mScreenHeight = 480;

  int mMousex = mScreenWidth/2;
  int mMousey = mScreenHeight/2;
  int mMouseButtons = 0;

  while (true) {
    struct sMousePacket mousePacket;
    int bytes = read (mMouseFd, &mousePacket, sizeof(mousePacket));
    if (bytes < (int)sizeof(mousePacket))
      cLog::Log (LOGINFO1, "mouse bytes %d", bytes);
    else if (mousePacket.buttons & 8) {
      mMousex += (mousePacket.buttons & 0x10) ? mousePacket.dx - 256 : mousePacket.dx;
      if (mMousex < 0)
        mMousex = 0;
      else if (mMousex > (int)mScreenWidth)
        mMousex = mScreenWidth;

      mMousey -= (mousePacket.buttons & 0x20) ? mousePacket.dy - 256 : mousePacket.dy;
      if (mMousey < 0)
        mMousey = 0;
      else if (mMousey > (int)mScreenHeight)
        mMousey = mScreenHeight;

      mMouseButtons = mousePacket.buttons & 0x03;
      cLog::Log (LOGINFO1, "mouse %d %d %d %d %d",
                 mousePacket.buttons, mousePacket.dx, mousePacket.dy, mMousex, mMousey);
      }
    else 
      read (mMouseFd, &mousePacket, 1); // Try to sync up again
    }

  return 0;
  }
