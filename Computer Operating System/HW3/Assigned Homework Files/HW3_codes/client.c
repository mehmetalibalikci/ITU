/*
 * client.c: A very, very primitive HTTP client.
 * 
 * To run, try: 
 *      client www.cs.wisc.edu 80 / /anotherfile.html
 *
 * Sends multiple HTTP requests to the specified HTTP server.
 * Prints out the HTTP responses.
 *
 * blg312e: For testing your server, you will want to modify this client.  
 * For example:
 * 
 * You may want to make this multi-threaded so that you can 
 * send many requests simultaneously to the server.
 *
 * You may also want to be able to request different URIs; 
 * you may want to get more URIs from the command line 
 * or read the list from a file. 
 *
 * When we test your server, we will be using modifications to this client.
 *
 */

#include "blg312e.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


# define MAXBUF 100
# define MAXURIS 100

/*
 * Send an HTTP request for the specified file 
 */
void clientSend(int fd, char *filename)
{
    char buf[MAXLINE];
    char hostname[MAXLINE];

    Gethostname(hostname, MAXLINE);

    /* Form and send the HTTP request */
    sprintf(buf, "GET %s HTTP/1.1\n", filename);
    sprintf(buf, "%sHost: %s\n\r\n", buf, hostname);
    Rio_writen(fd, buf, strlen(buf));
}

/*
 * Read the HTTP response and print it out
 */
void clientPrint(int fd)
{
    rio_t rio;
    char buf[MAXBUF];  
    int length = 0;
    int n;

    Rio_readinitb(&rio, fd);

    /* Read and display the HTTP Header */
    n = Rio_readlineb(&rio, buf, MAXBUF);
    while (strcmp(buf, "\r\n") && (n > 0)) {
        printf("Header: %s", buf);
        n = Rio_readlineb(&rio, buf, MAXBUF);

        /* If you want to look for certain HTTP tags... */
        if (sscanf(buf, "Content-Length: %d ", &length) == 1) {
            printf("Length = %d\n", length);
        }
    }

    /* Read and display the HTTP Body */
    n = Rio_readlineb(&rio, buf, MAXBUF);
    while (n > 0) {
        printf("%s", buf);
        n = Rio_readlineb(&rio, buf, MAXBUF);
    }
}

typedef struct {
    char *host;
    int port;
    char *filename;
} client_arg_t;

void *clientThread(void *arg) {
    client_arg_t *client_arg = (client_arg_t *)arg;
    int clientfd;

    /* Open a single connection to the specified host and port */
    clientfd = Open_clientfd(client_arg->host, client_arg->port);

    clientSend(clientfd, client_arg->filename);
    clientPrint(clientfd);

    Close(clientfd);
    free(client_arg);  // Free the allocated memory for this argument
    return NULL;
}

void readURIsFromFile(const char *filename, char **uris, int *num_uris) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    char line[MAXLINE];
    *num_uris = 0;
    while (fgets(line, sizeof(line), file) && *num_uris < MAXURIS) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        uris[*num_uris] = strdup(line);
        (*num_uris)++;
    }
    fclose(file);
}

int main(int argc, char *argv[])
{
    char *host;
    int port;
    int num_files = 0;
    char *uris[MAXURIS];

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <host> <port> <filename1> [<filename2> ...]\n", argv[0]);
        fprintf(stderr, "Or: %s <host> <port> -f <uri_list_file>\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    port = atoi(argv[2]);

    if (strcmp(argv[3], "-f") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Usage: %s <host> <port> -f <uri_list_file>\n", argv[0]);
            exit(1);
        }
        readURIsFromFile(argv[4], uris, &num_files);
    } else {
        num_files = argc - 3;
        for (int i = 0; i < num_files; i++) {
            uris[i] = argv[i + 3];
        }
    }

    pthread_t threads[num_files];

    for (int i = 0; i < num_files; i++) {
        client_arg_t *arg = malloc(sizeof(client_arg_t));
        if (arg == NULL) {
            perror("malloc");
            exit(1);
        }
        arg->host = host;
        arg->port = port;
        arg->filename = uris[i];

        if (pthread_create(&threads[i], NULL, clientThread, arg) != 0) {
            perror("pthread_create");
            free(arg);
            exit(1);
        }
    }

    for (int i = 0; i < num_files; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
