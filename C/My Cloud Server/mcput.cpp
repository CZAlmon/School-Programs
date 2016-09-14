#include "client.h"

int main(int argc, char *argv[]){
        if(argc != 5){
                cout << "Incorrect call for mcput" << endl;
                exit(1);}

        unsigned int clientfd, port, key;
        unsigned int put = 0;
	string line;
        rio_t rio;
	char *message;
	int datalen = 0;
	int filebyte_offset = 0;
	int databuf_size = 1;
	size_t filebytes;

	Data_t clientbuf;
	Response_t server;	

        message = (char*)malloc(databuf_size);
	
	char *host = argv[1];
	port = atoi(argv[2]);
	key = atoi(argv[3]);
	char *filename = argv[4];
	line = argv[4];	
	
	line = filename;
	
        clientbuf.key = htonl(key);
        clientbuf.request  = htonl(put);
	for(size_t i = 0; i < line.length();i++)
		clientbuf.filename[i] = line[i];	
	clientbuf.byte = line.length();
	
	while((filebytes = fread(message + filebyte_offset, 1, 1, stdin)) > 0){
		datalen += (int)filebytes;
		int newbuf = databuf_size + (int)filebytes;
		char *temp = (char*)realloc(message, newbuf);
	
		if(temp){
			message = temp;
			filebyte_offset = databuf_size;
			databuf_size = newbuf;
		}
	}
	
	for(int i = 0; i < datalen; i++)
		clientbuf.message[i] = message[i];


	clientbuf.byte = htonl(databuf_size);
	
        clientfd = Open_clientfd(host,port);
        Rio_readinitb(&rio,clientfd);
        Rio_writen(clientfd, &clientbuf, sizeof(clientbuf));
        Rio_readn(clientfd, &server, sizeof(server));
		
	//cout << server.message << endl;
	
	
	Close(clientfd);
	
	free(message);
        return 0;       

}

