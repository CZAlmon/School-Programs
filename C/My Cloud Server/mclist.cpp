#include "client.h"

int main(int argc, char *argv[]){
        if(argc != 4){
                cout << "Incorrect call for mclist" << endl;
                exit(1);}

        int clientfd, port;
        unsigned int list = 3;
	unsigned int key;
        rio_t rio;
        char *host = argv[1];
        Data_t clientbuf;
        Response_t server;

        port = atoi(argv[2]);
        key = atoi(argv[3]);

        clientbuf.key = htonl(key);
        clientbuf.request  = htonl(list);

        clientfd = Open_clientfd(host,port);
        Rio_readinitb(&rio,clientfd);
        Rio_writen(clientfd, &clientbuf, sizeof(clientbuf));
        Rio_readn(clientfd, &server, sizeof(server));
 	if(server.message == NULL){
		cout << "No Files" << endl;
	}
	else{
		if(server.status == 0){
			for(size_t i = 0; i < server.byte;i++)
				cout << server.message[i];
		}
	}
	Close(clientfd);
        return 0;
}

