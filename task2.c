#include <iostream>
using namespace std;

void Math(unsigned long long int countOfSpans, unsigned long long int distan)
{
	unsigned long long int sum = distan * (countOfSpans * (countOfSpans + 1) /2);

	cout << sum << endl;	
}


void convertData(int argc, char* argv[])
{
   if(argc != 3)
   {
     cout << "Error;\n";
 	return;
   }

   
     int n = atoi(argv[1]);
     int k= atoi(argv[2]);
    Math(n, k);
}

int main(int arcg, char* argv[])
{
	convertData(arcg,argv);
	return 0;
}
