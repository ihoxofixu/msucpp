#ifndef CNTFS_HPP
#define CNTFS_HPP


#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;


class CNTFS{
private:
	string MFT_name, MFT_reserved;
	int capacity_bytes;
	vector<bool> blocks;
public:
	string inttostr(const int x);


  int strtoint(const string x);


	void replacefile(string oldfilename, string newfilename);


	CNTFS( const int capacity=1024, const string filename="$MFT");


  bool such_file_exist(const string filename);


  bool makefile(const string filename);


  bool deletefile(const string filename);


	bool renamefile(const string oldfilename, const string newfilename);


	void listfiles();


	int getfilelength(const string filename);


  int get_free_byte_pos();


	bool writefile(const string filename, const string data, int shift=0);


	string readfile(const string filename, int datasize, int shift=0);

};

#endif
