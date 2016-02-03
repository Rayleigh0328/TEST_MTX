
/*

Call the program by:
	gen s p f
	s: size of matrix
	p: prob of 1s
	f: file name

*/

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

#include<vector>

using namespace std;

int main(int argc, char** argv)
{
	char default_name[] = "rand.mtx";

	cout << "Begin generate random matrix" << endl;

	cout << argc << endl;
	for (int i=0;i<argc;++i)
		cout << argv[i]<< endl;

	int size;
	if (argc > 1) 
		sscanf(argv[1], "%d", &size); 
	else 
		size = 10000;
	
	cout << "Matrix size: " << size << " * " << size << endl;

	double p;
	if (argc > 2)
		sscanf(argv[2], "%lf", &p); 
	else
		p = 0.01;
	cout << "Non-zero element probability: " << p << endl;
	
	char* file_name;
	if (argc > 3)
		file_name = argv[3];
	else 
		file_name = default_name;
	cout << "Output to file: " << file_name << endl;
	
	srand(time(NULL));

	ofstream fout;
	fout.open(file_name);

	vector<pair<int, int> > tmp;
	tmp.clear();

	for (int i=0;i<size;++i)
		for (int j=0;j<size;++j)
		{
			double r = rand();
			if (r < p * RAND_MAX) 
				tmp.push_back(pair<int, int>(i+1, j+1));
		}
	fout << size << " " << size << " " << tmp.size() << endl;
	for (int i=0;i<tmp.size();++i)
		fout << tmp[i].first << " " << tmp[i].second << endl;

	fout.close();

	return 0;
}
