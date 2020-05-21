#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h> 
#include <string>
#define ERROR_FILE_OPEN -3


FILE* input = NULL;
int number = 0;
int countOfFiels = 0;
char* DIRPATH;

struct FielInfo {
    int fsize;
    int foffset;

    FielInfo(int s, int f)
    {
        fsize = s;
        foffset = f;
    }
};
void readFiel(int foffset, int fsize, int nextFoffset, int nextFsize, char* filePath);
void createDir(char* D);
std::string ExtractFileName(const std::string& fullPath);
char* concatenation(char *first,const char *second);
char* correctInput(char* path);
void openFile(char* fileName);
void readHeadOfHsFiel();
char* readNameFiel(FILE* fpint,int startPath, int foffsetNextFiel);
void readFentryTable(char* filePath);



int main(int argc, char** argv)
{

    DIRPATH = correctInput(argv[2]);
    openFile(argv[1]);
    readHeadOfHsFiel();
    readFentryTable(argv[1]);
    return 0;
}


void createDir(char* D)
{
mkdir(D, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

std::string ExtractFileName(const std::string& fullPath)
{
  const size_t lastSlashIndex = fullPath.find_last_of("/");
  return fullPath.substr(0,lastSlashIndex + 1);
}


char* concatenation(char *first,const char *second)
{
	char* nameFile = new char[strlen(first) + strlen(second) + 1];
	nameFile[0] ='\0';
	strcat(nameFile, first);
	strcat(nameFile, second);
	return nameFile;
}

char* correctInput(char* path)
{
	
	int lenght;
	lenght = strlen(path);
	if(path[lenght] != '/')
	{
        	char* newPath = new char[lenght + 2];
		strcat(newPath,path);
		strcat(newPath,"/");
		return newPath;
	}
	else
	return path;	
}

void readFiel(int foffset, int fsize, int nextFoffset, int nextFsize, char* filePath);
void openFile(char* fileName)
{
    input = fopen(fileName, "rb");
    if (input == NULL) {
        printf("Error opening file");
        exit(ERROR_FILE_OPEN);
    }
}
void readHeadOfHsFiel()
{
    fread(&number, 2, 1, input);
    fread(&countOfFiels, 2, 1, input);

}

char* readNameFiel(FILE* fpint,int startPath, int foffsetNextFiel)
{
    int size = foffsetNextFiel - startPath;
    char c;
    char* data = (char*)malloc(size * sizeof(char));
    
    fread(data, size, 1, fpint);
    
    if(ExtractFileName(data).length()==0 )
     {
	return data;
     }
     else 
	{
          createDir(concatenation(DIRPATH,ExtractFileName(data).c_str()));
	 return data;
	}

}

void readFentryTable(char* filePath)
{
    std::vector<FielInfo> Files;
    int fsize =0;
    int foffset = 0;

    int countFiel = 0;
    for (int i = 0; i < countOfFiels; ++i)
    {
        fread(&fsize, 3, 1, input);
        fread(&foffset, 4, 1, input);
        Files.push_back(FielInfo(fsize, foffset));
    }
    fseek(input, 0, SEEK_END);
    for (int i = 0; i < Files.size(); i++)
    {
        if (i + 1 == Files.size())
        {
            readFiel(Files[i].foffset, Files[i].fsize, ftell(input), 0,filePath);
        }
        else
        {
            readFiel(Files[i].foffset, Files[i].fsize, Files[i + 1].foffset, Files[i + 1].fsize,filePath);
        }
        
    }



}



void readFiel(int foffset, int fsize, int nextFoffset, int nextFsize,char* fileName)
{
    FILE* readFiel = NULL;
    readFiel = fopen(fileName, "rb");
    int startFiel = foffset;
    int endFiel = foffset + fsize;
    char* data = (char*)malloc(fsize * sizeof(char));;
    
    if (fseek(readFiel, startFiel, SEEK_SET)) {
        std::cout << "\nError " << fsize;
        
    }
    fread(data, fsize, 1, readFiel);
   
    char* outFile = concatenation(DIRPATH,readNameFiel(readFiel, endFiel, nextFoffset));
    FILE* output = NULL;
    output = fopen(outFile, "wb");
    if (output == NULL) {
        printf("Error opening file!!!");
        exit(ERROR_FILE_OPEN);
    }

  
    fwrite(data, fsize, 1, output);
    fclose(readFiel);
    fclose(output);
   delete [] outFile;

}




