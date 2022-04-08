/*
* --------------------------------------------------------------------
* @file    poller
* @brief   Sample design for GNSS-SDR-SIM Polling Utility
* @author  smk (smk@it.ca)
* @version 0.1.20220319
* @license BSD3
* @bugs    No know bugs
* --------------------------------------------------------------------
*/
/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event))
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16))

/* Main Funtion */

int main( int argc, char **argv ) {
  int fd;
  int wd;
  char buffer[BUF_LEN];
  printf("Starting up Program...\n");

  fd = inotify_init();

  if( fd < 0) {
    perror( "inotify_init" );
  }

  printf("Starting up Watcher...\n");
  wd = inotify_add_watch( fd, "/home/gnss-pc1/tmp/", IN_MODIFY | IN_CREATE | IN_DELETE);

  int cnt = 0, maxCnt = 100;
  printf("Event will be watched for %d updates.\n",maxCnt);
  pid_t tmp = 0;

  /* keep watching forever until keyboard interrupt */
  int eofix = 0; 
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
            // printf("The file %s was created.\n",event->name);
          }
        else if(event->mask & IN_DELETE) {
            // printf("The file %s was deleted.\n",event->name);
          }
        else if(event->mask & IN_MODIFY) {
                
            if(strcmp(event->name,"gps_ephemeris.xml") == 0) {
              /* 
               * This should trigger xml -> rinex convertor
               */
              /* wait for 2 sec for file to appear completely */
              if(eofix == 0) {
                  eofix = 1;
                  break;
              } else {
                  eofix = 0;
              }

              sleep(2);
              if (tmp)
                kill(tmp, SIGKILL);
              printf("Calling xml to rinex convertor...\n");
              /* fork a child process */ 
              pid_t pid=fork();
              tmp = pid;
              if(pid == 0) {
              /*
               * Decided to move the further execution to bash worker
               * script as way to easily change parameters of other
               * programs without recompiling poller again and again.
               */
                  static char *argv[]={"/home/gnss-pc1/bin/worker",NULL};
                  execv("/home/gnss-pc1/bin/worker",argv);
                
                  exit(127);
              /* watcher rerun... */
              } else {
                  /*
                   * After detection of gps_ephemeris.xml convertor is
                   * triggered. Script should ideally give some time to
                   * gps-sdr-sim to process xml before starting watcher
                   * again.
                   */
                  int sleep_time = 10;
                  printf("Starting Sleep for %d seconds.\n",sleep_time);
                  sleep(sleep_time);
                  printf("Waking up.\n");
              }
              
            }
            // printf("The file %s was modified.\n",event->name); 
          }
        }
      i += EVENT_SIZE + event->len;

    }
    /* 
    cnt++;
    if(cnt > maxCnt) break;
     */
  }

  ( void ) inotify_rm_watch(fd, wd);
  ( void ) close(fd);

  exit ( 0 );

}

/* ---------------------------------------------------------------- */
/* EOF */
