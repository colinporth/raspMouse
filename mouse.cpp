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

#include <linux/input.h>

#include "../shared/cLog.h"

extern "C" {
  int evTest (int argc, char **argv);
  }
//}}}

//{{{
struct sMousePacket {
  uint8_t flags;
  int8_t dx;
  int8_t dy;
  int8_t ext;
  };
//}}}

int main (int argc, char** argv) {

  cLog::Init ("", LOGINFO3);
  cLog::Log (LOGNOTICE, "mouse");

  evTest (argc, argv);

  int mScreenWidth = 800;
  int mScreenHeight = 480;

  int mMouseButtons = 0;
  int mMousex = mScreenWidth/2;
  int mMousey = mScreenHeight/2;
  int mScroll = 0;

  //int mMouseFd = open ("/dev/input/mouse0", O_RDWR);
  auto mMouseFd = open ("/dev/input/mice", O_RDWR);

  const uint8_t kIntelliMouse[] = { 0xf3, 200, 0xf3, 100, 0xf3, 80 };
  auto bytes = write (mMouseFd, kIntelliMouse, sizeof(kIntelliMouse));

  while (true) {
    struct sMousePacket mousePacket;
    auto bytes = read (mMouseFd, &mousePacket, sizeof(mousePacket));
    if (bytes < (int)sizeof(mousePacket)) {
      if ((bytes == 1) && (mousePacket.flags == 0xfa))
        cLog::Log (LOGINFO1, "mouse initial sync ok");
      else
        cLog::Log (LOGINFO1, "mouse bytes %d %x", bytes, mousePacket.flags);
      }

    else if (mousePacket.flags & 8) {
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

      mMouseButtons = mousePacket.flags & 0x03;
      mScroll += mousePacket.ext;

      cLog::Log (LOGINFO, "mouse %x %x %x %x  %d:%d %d",
                 mousePacket.flags, mousePacket.dx, mousePacket.dy, mousePacket.ext,
                 mMousex, mMousey, mScroll);
      }

    else {
      read (mMouseFd, &mousePacket, 1);
      cLog::Log (LOGINFO2, "resysnc");
      }
    }

  return 0;
  }
