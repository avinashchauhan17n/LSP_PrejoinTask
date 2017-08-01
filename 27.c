/* Write a program that	has a global counter that increments	every	1	second	and	the	
counter	resets	every	time	there	is	a	SIGINT	signal.	SIGQUIT	and	SIGTERM	should	be	ignored.	
Remember	to	manage	critical	regions	in	the	main	loop */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

int counter = 0;

void sigintHandler(int sig); // handler function for signal
int main(void) {
  sigset_t sigmask;
  struct sigaction action;
  
  printf("Pid=%d\n", getpid());

  /* Handle SIGINT */
  action.sa_handler = sigintHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;
  sigaction(SIGINT, &action, NULL);
  
  /* IGNORE SIGQUIT */
  action.sa_handler = SIG_IGN;
  sigaction(SIGQUIT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);
  
  sigemptyset(&sigmask);
  sigaddset(&sigmask, SIGINT);
  while(1) {
    sleep(1);
    printf("Counting = %d\n", counter);
    /* Blocking state */
    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    counter++;
    sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
  }
  return EXIT_SUCCESS;
}

void sigintHandler(int sig) {
  counter = 0;
}
