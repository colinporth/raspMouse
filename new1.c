int openTouchScreen()
void getTouchScreenDetails(int *screenXmin,int *screenXmax,int *screenYmin,int *screenYmax)
void getTouchSample(int *rawX, int *rawY, int *rawPressure)

/*{{{*/
int openTouchScreen() {

  if ((fd = open("/dev/input/event0", O_RDONLY)) < 0)
    return 1;
 }
/*}}}*/

void getTouchScreenDetails (int *screenXmin,int *screenXmax,int *screenYmin,int *screenYmax) {

  for (i = 0; i < EV_MAX; i++)
    if (test_bit (i, bit[0])) {
      printf ("  Event type %d (%s)\n", i, events<em class="d4pbbc-italic"></em> ? events<em class="d4pbbc-italic"></em> : "?");
      if (!i)
        continue;
      ioctl (fd, EVIOCGBIT(i, KEY_MAX), bit<em class="d4pbbc-italic"></em>);
      for (j = 0; j < KEY_MAX; j++){
        if (test_bit (j, bit<em class="d4pbbc-italic"></em>)) {
          printf ("    Event code %d (%s)\n", j, names<em class="d4pbbc-italic"></em> ? (names<em class="d4pbbc-italic"></em>[j] ? names<em class="d4pbbc-italic"></em>[j] : "?") : "?");
          if (i == EV_ABS) {
            ioctl (fd, EVIOCGABS(j), abs);
            for (k = 0; k < 5; k++)
              if ((k < 3) || abs[k]) {
                printf ("     %s %6d\n", absval[k], abs[k]);
                if (j == 0) {
                  if (absval[k] == "Min  ") 
                    *screenXmin =  abs[k];
                  if (absval[k] == "Max  ") 
                    *screenXmax =  abs[k];
                  }
                if (j == 1) {
                  if (absval[k] == "Min  ") 
                    *screenYmin =  abs[k];
                  if (absval[k] == "Max  ")
                    *screenYmax =  abs[k];
                  }
                }
            }
          }
        }
      }
  }

void getTouchSample (int *rawX, int *rawY, int *rawPressure)

  rb = read(fd,ev,sizeof(struct input_event)*64);
  for (i = 0;  i <  (rb / sizeof(struct input_event)); i++) {
    if (ev<em class="d4pbbc-italic"></em>.type ==  EV_SYN)   
      printf("Event type is %s%s%s = Start of New Event\n",KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT);                 else if (ev<em class="d4pbbc-italic"></em>.type == EV_KEY && ev<em class="d4pbbc-italic"></em>.code == 330 && ev<em class="d4pbbc-italic"></em>.value == 1)                         printf("Event type is %s%s%s & Event code is %sTOUCH(330)%s & Event value is %s1%s = Touch Starting\n", KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT,KYEL,KWHT,KYEL,KWHT$                 else if (ev<em class="d4pbbc-italic"></em>.type == EV_KEY && ev<em class="d4pbbc-italic"></em>.code == 330 && ev<em class="d4pbbc-italic"></em>.value == 0)                         printf("Event type is %s%s%s & Event code is %sTOUCH(330)%s & Event value is %s0%s = Touch Finished\n", KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT,KYEL,KWHT,KYEL,KWHT$                 else if (ev<em class="d4pbbc-italic"></em>.type == EV_ABS && ev<em class="d4pbbc-italic"></em>.code == 0 && ev<em class="d4pbbc-italic"></em>.value > 0){
    printf ("Event type is %s%s%s & Event code is %sX(0)%s & Event value is %s%d%s = Raw X\n", KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT,KYEL,KWHT,KYEL,ev<em class="d4pbbc-italic"></em>.value,KWHT);
    *rawX = ev<em class="d4pbbc-italic"></em>.value;
    }
  else if (ev<em class="d4pbbc-italic"></em>.type == EV_ABS  && ev<em class="d4pbbc-italic"></em>.code == 1 && ev<em class="d4pbbc-italic"></em>.value > 0){
    printf ("Event type is %s%s%s & Event code is %sX(1)%s & Event value is %s%d%s = Raw Y\n", KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT,KYEL,KWHT,KYEL,ev<em class="d4pbbc-italic"></em>.value,KWHT);
    *rawY = ev<em class="d4pbbc-italic"></em>.value;
    }
  else if (ev<em class="d4pbbc-italic"></em>.type == EV_ABS  && ev<em class="d4pbbc-italic"></em>.code == 24 && ev<em class="d4pbbc-italic"></em>.value > 0){
    printf ("Event type is %s%s%s & Event code is %sX(24)%s & Event value is %s%d%s = Pressure\n", KYEL,events[ev<em class="d4pbbc-italic"></em>.type],KWHT,KYEL,KWHT,KYEL,ev<em class="d4pbbc-italic"></em>.value,KWHT);
    *rawPressure = ev<em class="d4pbbc-italic"></em>.value;
    }
  }
