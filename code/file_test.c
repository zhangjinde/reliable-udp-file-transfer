#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_SIZE 60000

void error(const char *);

int main()
{
  FILE * pFile;
  long lSize;
  int chunks;
  int final_chunk;
  size_t result;

  pFile = fopen("data1M.bin" , "rb" );
  if (pFile==NULL) {fputs("File error\n",stderr); exit(1);}

  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  printf("File Size: %ld\n", lSize);
  chunks = ceil(lSize/(float)DATA_SIZE);
  // allocate memory to contain the whole file:
  char **buffer = (char**) malloc (chunks*sizeof(char*));
  int count = 0;

  /// reading from file
  for(count = 0; count < chunks - 1;count++)
    {
      buffer[count] = (char*) malloc (DATA_SIZE * sizeof(char));
      result = fread (buffer[count], 1, DATA_SIZE, pFile);
    } 
  printf("No of chunks : %d\n", chunks);
  printf("Max file size : %ld\n", lSize);
  printf("Memory read : %d\n", (chunks - 1) * DATA_SIZE);
  printf("Memory left to read : %ld\n", lSize - (chunks-1) * DATA_SIZE);
  printf("count value  : %d\n", count);
  
  
  /// remaining memory chunk lSize - chunks*data_size
  final_chunk = lSize - (chunks-1) * DATA_SIZE;
  
  buffer[count] = (char*) malloc (final_chunk * sizeof(char));
  result = fread (buffer[count], 1, final_chunk, pFile);
  printf("File Size read: %lu, count : %d\n", result, count);


  fclose (pFile);


  return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
