#include "blg312e.h"
#include "request.h"
#include "pthread.h"
#include <semaphore.h>

int num_connections = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_slots;
sem_t full_slots;

typedef struct {
    int *buffer;
    int thread_id;
} thread_arg_t;

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// blg312e: Parse the new arguments too
// Burada terminalden girdiğimiz metin parçalanıyor. Bunu değiştireceğiz. Thread sayısını ekleyeceğiz.
void getargs(int *port, int *numthreads, int *buffersize, int argc, char *argv[])
{
    if (argc != 4) {
      fprintf(stderr, "Usage: %s <port> <numthreads> <buffersize>\n", argv[0]);
      exit(1);
    }
    *port = atoi(argv[1]);
    *numthreads = atoi(argv[2]);
    *buffersize = atoi(argv[3]); 
}

void *worker_thread(void *arg) {
    thread_arg_t *thread_arg = (thread_arg_t *)arg;
    int *buffer = thread_arg->buffer;
    int thread_id = thread_arg->thread_id;
    
    while (1) {
        sem_wait(&full_slots);  // Wait for at least one full slot
        pthread_mutex_lock(&mutex);
        int connfd = buffer[--num_connections];
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots); // Signal that one slot is now empty

        // Handle request
        printf("Thread %d handling request from descriptor: %d\n", thread_id, connfd);
        requestHandle(connfd);
        close(connfd);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int listenfd, connfd, port, clientlen, numthreads, buffersize, *buffer;
    struct sockaddr_in clientaddr;

    getargs(&port, &numthreads, &buffersize, argc, argv);
    buffer = (int*)malloc(sizeof(int) * buffersize);
    if (buffer == NULL) {
      perror("malloc");
      exit(1);
    }

    sem_init(&empty_slots, 0, buffersize);  // Initialize semaphore for empty slots
    sem_init(&full_slots, 0, 0);  // Initialize semaphore for full slots

    pthread_t worker_threads[numthreads];
    thread_arg_t thread_args[numthreads];

    // Create worker threads
    for (int i = 0; i < numthreads; i++) {
        thread_args[i].buffer = buffer;
        thread_args[i].thread_id = i;
        if (pthread_create(&worker_threads[i], NULL, worker_thread, &thread_args[i]) != 0) {
            perror("pthread_create");
            free(buffer);
            exit(1);
        }
    }

    listenfd = Open_listenfd(port);
    while (1) {
      clientlen = sizeof(clientaddr);
      connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

      sem_wait(&empty_slots);  // Wait for at least one empty slot
      pthread_mutex_lock(&mutex);
      buffer[num_connections++] = connfd;
      pthread_mutex_unlock(&mutex);
      sem_post(&full_slots);  // Signal that one slot is now full
    }

    free(buffer);
    sem_destroy(&empty_slots);  // Destroy semaphore for empty slots
    sem_destroy(&full_slots);  // Destroy semaphore for full slots
    return 0;
}