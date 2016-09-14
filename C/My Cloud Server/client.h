#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cctype>
#include <cstdio>
#include <wait.h>
#include <iomanip>
extern "C"{
        #include "csapp.h"
}
#define four_byte_buf_size 4
#define FILE_NAME_SIZE 80
#define Max_files 100

using namespace std;

const int filesize = 100000;
struct Data_t{
	unsigned int key, request;
	char* filename = NULL;
	unsigned int byte;
	char* message = NULL;
	};

struct Response_t{
	int status;
	unsigned int byte;
	char *message = NULL;
	};

#endif
