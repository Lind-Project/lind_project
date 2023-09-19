#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DEVICE_PATH "/var/test" // Defining the path for the device to be created
#define MODE S_IFCHR | 0666     // Setting the mode as character device and setting the permissions as rw for all

int main() {

  // Create a special (character type) file at DEVICE_PATH. The file is a character device with rw permissions.
  // The third parameter, dev, is ignored in this case since we are creating a character device.
  if (mknod(DEVICE_PATH, MODE, 0) == -1) {
    perror("mknod");  // Print error message if mknod fails
    exit(EXIT_FAILURE);
  }

  printf("Test char device created successfully.\n"); // Successfully created the device
  fflush(stdout);

  // Remove the link to the special file, effectively deleting it
  if (unlink(DEVICE_PATH) == -1) {
    perror("unlink"); // Print error message if unlink fails
    exit(EXIT_FAILURE);
  }

  printf("Unlinked test char device.\n"); // Successfully removed the device
  fflush(stdout);

  return 0;
}
