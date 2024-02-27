#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>

const char* FILENAME = "testfiles/mmaptestfile.txt";

size_t getFilesize(const char* filename) {
	struct stat st;
	stat(filename, &st);
	return st.st_size;
}

int main(void) {
	size_t filesize = getFilesize(FILENAME);
	//Open file
	int fd = open(FILENAME, O_RDONLY, 0);
	assert(fd != -1);
	//Execute mmap
	void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
	assert(mmappedData != MAP_FAILED);
	//Write the mmapped data to stdout (= FD #1)
	write(1, mmappedData, filesize);
	//Cleanup
	int rc = munmap(mmappedData, filesize);
	assert(rc == 0);
	close(fd);
}
