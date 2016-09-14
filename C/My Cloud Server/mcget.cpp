#include "client.h"

int main(int argc, char *argv[]){
        if(argc != 5){
                cout << "Incorrect call for mcget" << endl;
                exit(1);}

        unsigned int clientfd, port, key;
        unsigned int get = 1;
        rio_t rio;

        Data_t clientbuf;
        Response_t server;

        char *host = argv[1];
        port = atoi(argv[2]);
        key = atoi(argv[3]);
        char* filename = argv[4];

        clientbuf.key = htonl(key);
        clientbuf.request  = htonl(get);
        clientbuf.filename = filename;

        clientfd = open_clientfd(host,port);
        rio_readinitb(&rio,clientfd);
        rio_writen(clientfd, &clientbuf, sizeof(clientbuf));
        rio_readn(clientfd, &server, sizeof(server));
        close(clientfd);

        return 0;
}

