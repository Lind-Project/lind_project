#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ENDVAL 100 //program terminates at 100

int main(void)
{
  int pval = 0;

  int parent_to_child[2], child_to_parent[2]; //pipes for communication in each direction
	pid_t pid = 0;

  if (pipe(parent_to_child) < 0)
  {
      perror("Failed to initialize parent to child pipe");
      exit(1);
  }

  if (pipe(child_to_parent) < 0)
  {
      perror("Failed to initialize child to parent pipe");
      exit(1);
  }

  pid = fork();
  if (pid < 0)
  {
    perror("Fork failed\n");
    exit(1);
  }

  //setup pipes for each process
  if (pid == 0)
  {
    // child process, close unnescessary ends
    close(child_to_parent[0]);
    close(parent_to_child[1]);
  }
  else
  {
    // parent process, close unnescessary ends
    close(parent_to_child[0]);
    close(child_to_parent[1]);
  }

  //begin pong-ing
  while (pval < ENDVAL)
  {
    //child
    if (pid == 0)
    {

      int readlen = read(parent_to_child[0], &pval, sizeof(pval));
      if (readlen < 0)
      {
         perror("Child failed to read data");
         exit(1);
      }

      else
      {
         printf("Child received %d\n", pval);

         pval += 1;

         printf("Child sends %d\n", pval);
         if (write(child_to_parent[1], &pval, sizeof(pval)) < 0)
         {
             perror("Child failed to write data");
             exit(1);
         }
      }

    }
    else
    {
      //parent
      pval += 1;

      printf("Parent sending %d\n", pval);
      if (write(parent_to_child[1], &pval, sizeof(pval)) != sizeof(pval))
      {
          perror("Failed to send data to child");
          exit(1);
      }

      // wait for response
      int readlen = read(child_to_parent[0], &pval, sizeof(pval));
      if (readlen < 0)
      {
          perror("Parent failed to read data");
          exit(1);
      }
      else
      {
          printf("Parent received %d\n", pval);
      }
    }
  }

  wait(NULL); //wait for child to terminate

  //close pipe ends and exit child

  close(parent_to_child[1]);
  close(child_to_parent[0]);

  if (pid == 0)
  {
  close(child_to_parent[1]);
  close(parent_to_child[0]);
  exit(0);
  }

  printf("Pipe Pong complete.\nFinal value: %d\n", pval);

  return 0;
}
