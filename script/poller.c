//--------------------------------------------------------------------
// File information

// Name          : poller
// Purpose       : Sample design for GNSS-SDR-SIM Polling Utility
// License       : BSD3 
// Revision      : 0.1.220301
// Author        : smk (sudhanshumohan781@gmail.com)

//--------------------------------------------------------------------
// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h> 
#include <unistd.h>
#include <string.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event))
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16))

//--------------------------------------------------------------------
// Main Funtion

int main( int argc, char **argv ) {
  int fd;
  int wd;
  char buffer[BUF_LEN];
  printf("Starting up Program\n");

  fd = inotify_init();

  if( fd < 0) {
    perror( "inotify_init" );
  }

  wd = inotify_add_watch( fd, "/home/smk/tmp/", IN_MODIFY | IN_CREATE | IN_DELETE);

  printf("Starting up Watcher\n");
  int cnt = 0, maxCnt = 100;
  printf("Event will be watched for %d updates\n",maxCnt);


  // always true
  while(1) {
    int length, i = 0;
    length = read(fd, buffer, BUF_LEN);
    if(length < 0) {
      perror("read");
    }

    while (i < length) {
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
      if( event-> len) {
        if(event->mask & IN_CREATE) {
            printf("The file %s was created.\n",event->name);
          }
        else if(event->mask & IN_DELETE) {
            printf("The file %s was deleted.\n",event->name);
          }
        else if(event->mask & IN_MODIFY) {

            if(strcmp(event->name,"gps_ephemeris.xml") == 0) {
              // This should trigger xml -> rinex convertor
              printf("Calling xml to rinex convertor==============>\n");
              // -- we fork a process --> 
              // -simc ( xml, location,frequency sample )
              // ----> watcher runn... 
            }
            printf("The file %s was modified.\n",event->name);
          }
        }
      i += EVENT_SIZE + event->len;

    }
    cnt++;
    if(cnt > maxCnt) break;
  }


  ( void ) inotify_rm_watch(fd, wd);
  ( void ) close(fd);

  exit ( 0 );

}

//--------------------------------------------------------------------
// EOF
