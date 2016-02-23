#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

static pid_t g_child;
static pid_t g_monitored_child;

void sighupHandler(int unused);
void createChild();
void childProcess();
void createMonitoredChild();
void monitoredChild();
void daemonize();

/******************/
/* sighup_handler */
/******************/
void sighupHandler(int unused) {
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
  } else if (!g_child) {
    daemonize();
    childProcess();
  }
}

/***********************/
/* void childProcess() */
/***********************/
void childProcess() {
  int status;
  while(1) {
    createMonitoredChild();
    wait(&status);
    // child died
  }
}

/************************/
/* createMonitoredChild */
/************************/
void createMonitoredChild() {
  g_monitored_child = fork();
  if (g_monitored_child < 0) {
    // fork failed
    exit(EXIT_FAILURE);
  } else if (!g_monitored_child) {
    monitoredChild();
  }
}

/*******************/
/* monitored_child */
/*******************/
void monitoredChild() {
  signal(SIGCHLD, SIG_IGN);
  signal(SIGHUP,  sighupHandler);
  while(1) {
    // wait forever for HUP
    sleep(60 * 60);
  }
}

/*************/
/* daemonize */
/*************/
void daemonize() {

  signal(SIGCHLD, SIG_IGN);
  signal(SIGHUP,  SIG_IGN);

  umask(0);
  chdir("/");

  for (int fd=sysconf(_SC_OPEN_MAX); fd>0; --fd) close(fd);

  stdin =fopen("/dev/null","r");
  stdout=fopen("/dev/null","w+");
  stderr=fopen("/dev/null","w+");

}

/***************/
/* signalChild */
/***************/
void signalChild() {
  kill(g_monitored_child,SIGHUP);
}

/********/
/* main */
/********/
int main() {

  createChild();
  printf("waiting for 30\n");
  sleep(30);
  printf("signaling\n");
  signalChild();
  printf("waiting for 120\n");
  sleep(120);
  printf("cleaning up\n");
  kill(g_child,SIGTERM);
  kill(g_monitored_child,SIGTERM);
  return 0;
}
