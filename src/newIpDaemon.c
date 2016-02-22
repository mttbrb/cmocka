#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

pid_t g_child;

/******************/
/* sighup_handler */
/******************/
void sighup_handler(int unused) {
  system("touch /work/c/cmocka/itworked");
}

/***************/
/* createChild */
/***************/
void createChild() {
  g_child = fork();
  if (g_child < 0) {
    // fork failed
    fprintf(stderr,"error: failed fork\n");
    exit(EXIT_FAILURE);
  } else if (g_child > 0) {
    // parent dies leaving only the child
    exit(EXIT_SUCCESS);
  }
}

/*************/
/* daemonize */
/*************/
int daemonize(void) {

  createChild();

  signal(SIGCHLD, SIG_IGN);
  signal(SIGHUP, sighup_handler);

  createChild();  // not sure why

  umask(0);
  chdir("/");

  for (int fd=sysconf(_SC_OPEN_MAX); fd>0; --fd) close(fd);

  stdin =fopen("/dev/null","r");
  stdout=fopen("/dev/null","w+");
  stderr=fopen("/dev/null","w+");

  return 0;
}

/********/
/* main */
/********/
int main() {

  daemonize();

  while(1) {
    // wait for sighups forever
  }
}
