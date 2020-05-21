#include <stdlib.h>
#include <stdio.h>


void answer(int n , int k )
{
    int Answer = int((n + k) / (k + 1));
    printf("%d\n", Answer);
}



void convertData(int argc, char* argv[])
{
   if(argc != 3)
   {
       printf("Error input:\n");
 	return;
   }

   
     int n = atoi(argv[1]);
     int k= atoi(argv[2]);

    answer(n, k);
}



int main(int arcg, char* argv[])
{
	convertData(arcg,argv);
	return 0;
}

