#include <iostream>
#include <fstream> // file stream
#include <string>
using namespace std;


int main () {
	cout<<"Enter the file you want to read"<<endl;
	string  filename;
	cin>>filename;
	// create and open the stream
	fstream in_stream;
	in_stream.open(filename, fstream::in | fstream::app);

	if(!in_stream.is_open())
	{
		cout<<"Cannot find file "<<filename<<". Ending... "<<endl;
		return 0;
	}
	in_stream.seekg(0, in_stream.end); // move the cursor to end.
	int length = in_stream.tellg();
	in_stream.seekg(0,in_stream.beg); // move back cursor once length is measured.
	cout<<"file length:"<<length<<endl;
	char *buffer = new char[length];
	
	in_stream.read(buffer, length);

	delete buffer;
}

