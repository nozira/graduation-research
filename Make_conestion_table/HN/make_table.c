#include <stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "HN_ID.txt";
  char s[100];

  fp = fopen( fname, "r" );
  if( fp == NULL ){
    printf( "%sファイルが開けません¥n", fname );
    return -1;
  }

  printf( "¥n-- fgets() --¥n" );
  while( fgets( s, 100, fp ) != NULL ){
    printf( "%s", s );
  }

  fclose( fp );
  return 0;
}