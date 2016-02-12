#include "easywsclient.hpp"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <time.h>  
using namespace std;

FILE *file;
FILE *serial;


const int BUF_SIZE = 9600;
const int MIN_STRING = 20;
const char *SERVER_URL = "ws://localhost:80";
const char *SERIAL_DEV = "/dev/ttyACM0";
char buff[BUF_SIZE];

struct string_chain {
    int start_point = 0;
    int len = 0;
    bool sent;
    bool saved;
    string_chain *next;
    
    string_chain() {
        sent = false;
        saved = false;
    }
    
    string_chain(const string_chain &prev) {
        string_chain();
        start_point = prev.start_point + prev.len;
    }
};
string_chain ch[BUF_SIZE/MIN_STRING];

static easywsclient::WebSocket::pointer ews = NULL;

void handle_message(const std::string & message) {
    fprintf(serial, message.c_str());
    if (message == "4") {
        printf("that end");
        ews->close();
    }
}

int main() {
    std::cout << "test" << std::endl;
   
    serial = fopen(SERIAL_DEV, "r+");
    
    char fname[20] = "lta_";
    
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (fname, 33, "lta_%F_%H_%M.csv", timeinfo);
    cout << "[" << fname << "]" << endl;
    file = fopen(fname, "a+");
    assert(file);
    ews = easywsclient::WebSocket::from_url(SERVER_URL);
    assert(ews);
   
    int r = 0;
    int i = 0;
    int ost = 0;
    bool q = false;
    while (true) {
        sleep(1);
        int offset = r - ost;
        string str = "";
        if (offset > 0 )
            for(int i = offset; i < r + offset; i++)
                str += buff[i];
        r = fread(buff, 1, BUF_SIZE, serial);
        for (i = 0; i < offset + r; i++) {
            cout << "i " << i << endl;
            str += buff[i];
            if (buff[i] == '\n') {
                cout << " q = TRUE" << endl;
                ost = i;
                q = true;
                break;
            }
        }
        //offset = i;
        cout << "str " << str << endl;
        ews->poll();
        if (q) {
            ews->send(str);
            //fprintf(file, str.c_str());
            q = false;
            str = "";
        }
        str.clear();
        ews->dispatch(handle_message);
    }
    fclose(file);
    delete ews;
    return 0;
}
