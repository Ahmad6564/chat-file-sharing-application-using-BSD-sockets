#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>

#define PORT 8080
#define IP "127.0.0.1"
#define BUF_SIZ 1024

using namespace std;

void* handle_recv(void* conn) {
    long sockfd = (long)conn;
    int filefd;
    char buf[BUF_SIZ];
    char data[BUF_SIZ];
    char cli_name[BUF_SIZ];
    int n, read_len, file_read_len;

    while (true) {
        memset(&buf, 0, sizeof(buf));
        memset(&cli_name, 0, sizeof(cli_name));

        // first receive the name of the client or server
        n = recv(sockfd, (char*)&cli_name, sizeof(cli_name), 0);

        // verify that name or data was received
        if (n == 0 || strlen(cli_name) == 0) {
            cout << "server went offline" << endl;
            exit(1);
        }

        // now receive the actual data
        n = recv(sockfd, (char*)&buf, sizeof(buf), 0);

        // verify that the data was received
        if (n == 0 || strlen(buf) == 0) {
            cout << "server went offline" << endl;
            exit(1);
        }

        // recv file from the server
        if (strcmp(buf, "file") == 0) {
            read_len = read(sockfd, buf, BUF_SIZ);
            strcpy(data, buf);

            // create file
            filefd = open(data, O_WRONLY | O_CREAT | O_EXCL, 0700);

            if (!filefd) {
                perror("file open error: ");
                continue;
            }

            printf("[%s]: incoming file (file: %s)\n", cli_name, data);

            // file save
            while (true) {
                memset(&buf, 0, BUF_SIZ);
                file_read_len = read(sockfd, buf, BUF_SIZ);
                write(filefd, buf, file_read_len);

                // when less than 1024, means last packet of the file
                if (file_read_len < 1024) {
                    printf("[%s]: file received (file: %s)\n", cli_name, data);
                    break;
                }
            }

            close(filefd);
            continue;
        }

        // normal message
        printf("[%s]: %s\n", cli_name, buf);
    }
}

int main() {
    intptr_t sockfd;
    int filefd;
    char buf[BUF_SIZ];
    int file_name_len, read_len;
    struct sockaddr_in serv_addr;

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket creation failed");
        close(sockfd);
        exit(1);
    }

    // populate address struct
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(PORT);

    // connect to the server socket
    if ((connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) == -1) {
        perror("failed to connect");
        close(sockfd);
        exit(1);
    }

    pthread_t th;
    pthread_create(&th, NULL, handle_recv, (void*)sockfd);

    while (true) {
        string data;
        getline(cin, data);

        if (data == "close") {
            printf("exiting\n");
            break;
        }

        memset(&buf, 0, BUF_SIZ);
        strcpy(buf, data.c_str());

        // file transfer
        if (data == "file") {
            // tell the server that a file is being sent
            send(sockfd, &buf, strlen(buf), 0);
            memset(&buf, 0, BUF_SIZ);

            // get the file name from the client to send
            printf("> write file name to send: ");
            scanf("%s", buf);

            // tell server the file name
            send(sockfd, &buf, strlen(buf), 0);

            // load the file as readonly
            filefd = open(buf, O_RDONLY);

            if (!filefd) {
                perror("error");
                continue;
            }

            // send the entire file
            while (true) {
                memset(&buf, 0, BUF_SIZ);

                // read file into the buffer
                read_len = read(filefd, buf, BUF_SIZ);

                // send file to the server
                send(sockfd, &buf, read_len, 0);

                // reached the end of file
                if (read_len == 0) {
                    printf("> file was sent\n");
                    break;
                }
            }

            continue;
        }

        // normal chat
        send(sockfd, &buf, strlen(buf), 0);
    }

    close(sockfd);
    return 0;
}
