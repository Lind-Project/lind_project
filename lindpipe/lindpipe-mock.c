#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lfq.h"
#include "cross-platform.h"

#define pipeEOF -1
 

typedef struct {
    char* data;
    int length;
    int index;
    int eof;
    
} LFQueueEntry;

typedef struct {
    struct lfq_ctx ctx;
    LFQueueEntry* CurrEntry;
    
} LindPipe;

LFQueueEntry* LFQEntry_new(char* data, int length) { 
  LFQueueEntry* entry = malloc(sizeof(LFQueueEntry));
  entry->data = malloc(sizeof(char) * length);
  memcpy(entry->data, data, length);
  entry->length = length;
  entry->index = 0;

  return entry;
}

int getEntryRemainder(LFQueueEntry* entry) {
    return entry->length - entry->index;
}


static int
LindPipe_init(LindPipe *self)
{
    lfq_init(&(self->ctx), 1);
    self->CurrEntry = NULL;

    return 0;
}


void LindPipe_seteof(LindPipe *self) {

    /** Create EOF entry **/

    int ret = 0;
   
    if (( ret = lfq_enqueue(&(self->ctx), LFQEntry_new(NULL, pipeEOF))) != 0) {
        printf("lfq_enqueue failed, reason:%s\n", strerror(-ret));
        return;
    }

    return;
}

void updateCurrentEntry(LindPipe *self) {

    while ((self->CurrEntry = (LFQueueEntry*)lfq_dequeue(&(self->ctx))) == 0);

}



static int LindPipe_pipewrite(LindPipe *self, char *data, int datalen) {

    int ret;
    // printf("writing\n");


    

    if (( ret = lfq_enqueue(&(self->ctx), LFQEntry_new(data, datalen))) != 0) {
        printf("lfq_enqueue failed, reason:%s\n", strerror(-ret));
        return -1;
    }

   

    return datalen;

}

static int LindPipe_piperead(LindPipe *self, char* buf, int count) {
   

    int bytes_read = 0;
    int bytes_remaining = 0;

    
    // printf("reading\n");


    while (bytes_read < count) {
        
        /*update entry and check for EOF */
        if (self->CurrEntry == NULL) updateCurrentEntry(self);
        if (self->CurrEntry->length == pipeEOF) break;

        int entry_remainder = getEntryRemainder(self->CurrEntry);
        bytes_remaining = count - bytes_read;

        if (bytes_remaining <= entry_remainder) {
            memcpy(buf + bytes_read, self->CurrEntry->data + self->CurrEntry->index, bytes_remaining);
            self->CurrEntry->index = self->CurrEntry->index + bytes_remaining;
            bytes_read = bytes_read + bytes_remaining;
        }
        else {
            memcpy(buf + bytes_read, self->CurrEntry->data + self->CurrEntry->index, entry_remainder);
            self->CurrEntry->index = self->CurrEntry->length;
            bytes_read = bytes_read + entry_remainder;
        }


        if (self->CurrEntry->index == self->CurrEntry->length){
            free(self->CurrEntry->data);
            free(self->CurrEntry);
            self->CurrEntry = NULL;
        }

    }

    return bytes_read;
}

typedef struct {
    char* buf;
    int size;
    int iterations;
    LindPipe* pipe;
} TestStruct;

TestStruct* init_teststruct(char* buf, int size, int iterations, LindPipe* pipe) {
    TestStruct* temp_struct = (TestStruct*)malloc(sizeof(TestStruct));
    temp_struct->buf = buf;
    temp_struct->size = size;
    temp_struct->iterations = iterations;
    temp_struct->pipe = pipe;

    return temp_struct;
}



void* write_func(void *args){

    TestStruct* writestruct = args;
    char* writebuf = writestruct->buf;
    int WRITE_SIZE = writestruct->size;
    int NUM_WRITES = writestruct->iterations;
    LindPipe* pipe = writestruct->pipe;


    int bytes = 0;



    for (int i = 0; i < NUM_WRITES; i++){
        int writebytes = LindPipe_pipewrite(pipe, writebuf, WRITE_SIZE);
        bytes = bytes + writebytes;
    }

    // printf("wrote %d bytes\n", bytes);

}

void* read_func(void *args){

    TestStruct* readstruct = args;
    char* readbuf = readstruct->buf;
    int READ_SIZE = readstruct->size;
    int NUM_READS = readstruct->iterations;
    LindPipe* pipe = readstruct->pipe;


    int bytes = 0;
    
    for (int i = 0; i < NUM_READS; i++){
        int readbytes = LindPipe_piperead(pipe, readbuf + (i * READ_SIZE), READ_SIZE);
        bytes = bytes + readbytes;
    }
    // printf("Pipe finished reading %d bytes.\n", bytes);
    // printf("%s\n", readbuf);

}



#define BILLION  1000000000.0

int main(int argc, char *argv[]) {

    int i = atoi(argv[1]);
    unsigned long long WRITE_SIZE = 1UL << i;
    unsigned long long NUM_WRITES = 1UL << (30 - i);
    unsigned long long READ_SIZE = 1UL << 17;
    unsigned long long NUM_READS = 1UL << 13;

    char* writebuf = malloc(sizeof(char) * WRITE_SIZE);
    char* readbuf = malloc(sizeof(char) * READ_SIZE * NUM_READS);

    LindPipe* pipe = (LindPipe*)malloc(sizeof(LindPipe));
    LindPipe_init(pipe);

    TestStruct* writestruct = init_teststruct(writebuf, WRITE_SIZE, NUM_WRITES, pipe);
    TestStruct* readstruct = init_teststruct(readbuf, READ_SIZE, NUM_READS, pipe);

    


    pthread_t write_thread;
    pthread_t read_thread; 

    struct timespec start, stop;
    double accum;


    if( clock_gettime(CLOCK_MONOTONIC, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }



    pthread_create(&write_thread, NULL, write_func, writestruct); 
    pthread_create(&read_thread, NULL, read_func, readstruct); 

    pthread_join(write_thread, NULL); 
    pthread_join(read_thread, NULL); 

    if( clock_gettime(CLOCK_MONOTONIC, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }


    accum = ( stop.tv_sec + ((double)stop.tv_nsec / BILLION )) - ( (double)start.tv_sec + (start.tv_nsec / BILLION ));
   
   
            
    printf( "%lf\n", accum );

    free(pipe);
    free(writebuf);
    free(readbuf);
    free(writestruct);
    free(readstruct);

    return( EXIT_SUCCESS );


}
