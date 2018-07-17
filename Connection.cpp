#include "Connection.h"
#include "wrap.h"
//Constructor: Call parent Thread Constructor 
Connection::Connection(TCPSocket * p_tcpSocket): Thread()
{
    tcpSocket = p_tcpSocket; // Set the TCP socket
    next_connection = NULL; // Set the next pointer to NULL
}
void * Connection::threadMainBody (void * arg)
{
    char file_content[1024];	// A buffer for holding the file name 
    memset (file_content,0,1024);	// Initialize the buffer
    vector <string>file;
    // read from socket the file name to be fetched
    int read_bytes = tcpSocket->readFromSocket(file_content,1023);
    if ( read_bytes > 0) // If read successfully
    {
	// Clean up file name
        //if ( file_content[strlen(file_name)-1] == '\n' || file_name[strlen(file_name)-1] == '\r')
        //        file_name[strlen(file_name)-1] = 0;
        //if ( file_name[strlen(file_name)-1] == '\n' || file_name[strlen(file_name)-1] == '\r')
        //        file_name[strlen(file_name)-1] = 0;
        // FILE * f = fopen(file_name,"r"); // Try to open the file
        // if ( f != NULL)	// If opened
        // {
        // //     fseek (f,0,2);	// Seek to the end of the file  
        // //     long fsize = ftell(f);	// Get current location which represents the size
		// // // Allocate a buffer with the file size to read the content
        // //     char * buffer = (char *) calloc(fsize+1,sizeof(char));
        // //     fseek (f,0,0);  // Seek the beginning of the file
        // //     fread(buffer,1,fsize,f); // Read the whole file into the buffer
        // //     tcpSocket->writeToSocket(buffer,fsize); // Write the buffer to the socket
        // //     free(buffer);	// Free the buffer
        // //     fclose(f);	// Close the file
        stringstream is(file_content);
        string line = "";
        while(getline(is,line,'\n'))
        {
            file.push_back(line);
        }
            Wrap wraper(file);
            wraper.action();


            char * buffer = (char *) calloc(1024,sizeof(char));
            string lines;
            ifstream myfile ("error.err");
            if (myfile.is_open())
            {
                while (myfile.good())
                {
                    getline (myfile,lines);
                    lines+= '\n';
                    strcat(buffer,lines.c_str());
                    cout << lines << endl;
                }
                myfile.close();
            }
            else
            {
                cout << "Unable to open file";

            }
            // strcat(buffer,"output file begin\n");
            buffer+=';';
            ifstream mfile ("output.out");
            if (mfile.is_open())
            {
                while (mfile.good())
                {
                    getline (mfile,lines);
                    lines+= '\n';
                    strcat(buffer,lines.c_str());
                }
                mfile.close();
            }
            else
            {
                cout << "Unable to open file";

            }

            // FILE * f = fopen("error.err","r"); // Try to open the file
            // long fsize = ftell(f);
            // char * buffer = (char *) calloc(fsize+1,sizeof(char));
            // fseek (f,0,0);  // Seek the beginning of the file
            // fread(buffer,1,fsize,f); // Read the whole file into the buffer
            // printf("%s \n", buffer);
             tcpSocket->writeToSocket(buffer,1024); // Write the buffer to the socket
             cout<<"connection terminated"<<endl;
            // free(buffer);	// Free the buffer
            // fclose(f);	// Close the file
    }
    else
    {
        perror("Error With File\n");	// Print an error message
        tcpSocket->writeToSocket("Error\n",6);// Write error to the socket
    }
    // Shutdown the TCP Socket
    tcpSocket->shutDown();
    return NULL;
}
// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){next_connection = connection;}
// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){return next_connection;}
// Destructor: delete the TCP socket if set
Connection::~Connection(){if ( tcpSocket != NULL ) delete (tcpSocket);}
