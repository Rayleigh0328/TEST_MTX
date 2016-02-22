#include<cstdio>
#include<iostream>
#include<fstream>
#include<cstring>
#include<set>

#include "position.h"

using namespace std;

extern void convert(char* file_name, int& height, int& width, set<position>& ps);
extern void output_pbm(char* file_name, int height, int width, set<position>& ps);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cerr << "not enough arguments" << endl;
		return -1;
	}

	int height, width;
	set<position> ps;

	for (int i=1;i<argc;++i)
	{
		convert(argv[i], height, width, ps);
		output_pbm(argv[i], height, width, ps);
	}
}

void output_pbm(char* file_name, int height, int width, set<position>& ps)
{
	// change file extension from mtx to pbm
	char* pos = strrchr(file_name, '.');
	*(pos+1) = 'p';
	*(pos+2) = 'b';
	*(pos+3) = 'm';

	FILE *fp = fopen(file_name, "w");
	fprintf(fp, "P4\n");
	fprintf(fp, "%d %d\n", width, height);


	char data;
	for (int i=0;i<height;++i)
		for (int j=0;j<width;++j)
		{
			int num = i*width + j;
			if (num % 8 == 0)
			{
				if (num > 0) fputc(data, fp);
					//fout << data;
				data = 0;
			}

			if (ps.find(position(i,j))!=ps.end()) data += 1 << (7 - num % 8);
		}
	fputc(data, fp);
	fclose(fp);
	//fout << data << endl;
}

void convert(char* file_name, int &height, int &width, set<position>& ps)
{
	FILE *fp;
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		cerr << "Error when open file" << file_name << endl;
		return ;
	}

	const int buf_size = 1 << 10;
	char* buf = new char [buf_size];

	// process MatrixMarket header
	fscanf(fp, "%*s %*s %s", buf);
	if (strcmp(buf, "coordinate") != 0)
	{
		cerr << file_name<< "is not COO format" << endl;
		return;
	}
	fgets(buf, buf_size, fp);
	
	// process comment
	char c = fgetc(fp);
	while (c == '%')
	{
		fgets(buf,buf_size,fp);
		c = fgetc(fp);
	}
	ungetc(c, fp);

	// process matrix info
	int nz;
	fscanf(fp, "%d %d %d", &height, &width, &nz);

	// process data
	ps.clear();
	int row, col;
	for (int i=0;i<nz;++i)
	{
		fscanf(fp, "%d %d", &row, &col);
		fgets(buf, buf_size, fp);
		ps.insert(position(row-1,col-1));
	}	

	fclose(fp);
}


