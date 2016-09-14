#include "client.h"

//Global variable for List of Filenames and Number of Files;
char fileList[Max_files][FILE_NAME_SIZE];
unsigned int numFiles = 0;
//Byte_size is bounded to fileList. Size of each file indexed same as fileList. SET IN NETWORK ORDER.
vector<int> byte_size;


int main(int argc, char *argv[]){
	
    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    unsigned int secretKey;		
    fstream infile;
 
    if (argc != 3) {
		fprintf(stderr, "usage: %s <port> <secret key>\n", argv[0]);
		exit(0);
    }
    port = atoi(argv[1]);
    secretKey = atoi(argv[2]);
	
    listenfd = Open_listenfd(port);
	
    while (1) {

		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	
		Data_t Client_buf;
		Response_t Server_buf;
		unsigned int client_secret_key;
		unsigned int client_request_type;
		unsigned int client_data_length;
		char* client_filename = NULL;
		char *message = new char[filesize];	
		
		
		int client_status = -1;

		rio_t rio;
		Rio_readinitb(&rio, connfd);
		Rio_readn(connfd, &Client_buf, sizeof(Client_buf));
				

		client_secret_key = ntohl(Client_buf.key);
		client_request_type = ntohl(Client_buf.request);
		
		
		// Check Clients Secret key
		if(client_secret_key == secretKey){
			
			if(client_request_type == 0){
				client_data_length = Client_buf.byte;
				client_filename = Client_buf.filename;
				strcpy(fileList[Max_files], client_filename);
				strcpy(message, Client_buf.message);
				numFiles++;
				
				infile.open(client_filename);
				for(size_t i = 0; i < Client_buf.byte; i++)
					infile << message[i]; 
				infile.close();
				
				byte_size.push_back(client_data_length);
				client_status = 0;
				
				Server_buf.status = htonl(client_status);
				
				//SET SERVER MESSAGE BACK TO CLIENT
			
				cout << "Secret Key = " << client_secret_key << endl;
				cout << "Request Type = put" << endl;
				cout << "Filename = " << client_filename;
				
			}
			else if(client_request_type == 1){
				//int size;
				char * temp = NULL;
				client_status = -1;
				//bool flag = false;
				unsigned number_of_bytes;
				client_filename = Client_buf.filename;
				string line;
				
				ifstream outfile;
				outfile.open(client_filename);
				if(outfile.is_open()){
					
					while(getline(outfile,line)){
					for(size_t i = 0; i < line.length(); i++)
						temp[i] = line[i]; 			//GET FILE DATA
					}
				outfile.close();
				client_status = 0;					
				number_of_bytes = htonl(sizeof(temp));
										
				}
				else{
					client_status = -1;
				}
								
				//SET SERVER MESSAGE BACK TO CLIENT
				
				//Message
				if(client_status == 0){
					Server_buf.status = htonl(client_status);
					Server_buf.byte = number_of_bytes;
					Server_buf.message = temp;
				}
				else{
					Server_buf.status = htonl(client_status);
					Server_buf.byte = 0;
					Server_buf.message = NULL;
				}
				
				
				cout << "Secret Key = " << client_secret_key << endl;
				cout << "Request Type = get" << endl;
				cout << "Filename = " << client_filename;
				temp = NULL;
				delete []temp;
			}
			else if(client_request_type == 2){
				
				client_filename = Client_buf.filename;
				client_status = -1;
				
				bool flag = false;
				
				//FIND FILENAME IN FILELIST. IF NOT FOUND SET -1 and RETURN NOTHING
				for(unsigned int i = 0; i < numFiles; i++){
					
					if(client_filename == fileList[i]){
						flag = true;
					}
				}
				
				//IF FOUND REMOVE THAT BYTE FROM VECTOR AND REMOVE NAME FROM FILELIST
				if(flag){
					for(unsigned int i = 0; i < numFiles; i++){
						if(fileList[i] == client_filename){
							byte_size.erase(byte_size.begin()+i);								//remove from vector
							memmove(fileList[i], fileList[i+1], numFiles * FILE_NAME_SIZE);		//remove from fileList
							numFiles--;
							client_status = 0;
						}
					}
				}
				else{
					client_status = -1;
				}


				Server_buf.status = htonl(client_status);
				
				
				cout << "Secret Key = " << client_secret_key << endl;
				cout << "Request Type = del" << endl;
				cout << "Filename = " << client_filename;
			}
			else if(client_request_type == 3){
				char * temp = NULL;				
				client_status = 0;
				//char * temp_no_files = "No Files To Display";
				//if(numFiles == 0){
				//	strcat(temp, temp_no_files);
				//}
				//else{
					for (size_t i = 0; i < numFiles; i++){
						strcat(temp, fileList[i]);
				//	}
				}
				Server_buf.status = client_status;
				Server_buf.byte = sizeof(temp);
				Server_buf.message = temp;
		
				cout << "Secret Key = " << client_secret_key << endl;
				cout << "Request Type = list" << endl;
				cout << "Filename = " << client_filename;
				
				temp = NULL;
				delete [] temp;
			}
			if(client_status == 0){
                        	cout << "Client Operation Status = success" << endl;
                		}
                	else{
                        	cout << "Client Operation Status = error" << endl;
                		}
                	cout << "------------------------------------" << endl;

			//Write to Client
			
			
			Rio_writen(connfd, &Server_buf, sizeof(Server_buf));
		        Close(connfd);			
		
                	client_filename = NULL;
                	delete client_filename;
                	message = NULL;
                	delete message;
		}
		else{
		cout << "Incorrect Secret key" << endl;
		}
	}
	return 0;
}














