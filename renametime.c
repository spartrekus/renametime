


#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>




///////////////////////////////
///////////////////////////////
///////////////////////////////
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}





/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}







//////////////////
void ncp( char *filetarget,  char *  filesource )
{
  // fread
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "wb");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) {
                freader = 0 ; 
            }
            n = fread(  buffer, sizeof(char), 1 , fp);
            m = fwrite( buffer, sizeof(char), 1,  fp2);
        }
        fclose(fp2);
        fclose(fp);
      }
}










/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strampersand2txt(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == '&' ) 
	{
          ptr[j++]=':';
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strtxt2tex(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {

        if ( str[i] == '{' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='{';
	}

        else if ( str[i] == '^' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='^';
	}

        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}

        else if ( str[i] == '>' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='e';
          ptr[j++]='n';
          ptr[j++]='s';
          ptr[j++]='u';
          ptr[j++]='r';
          ptr[j++]='e';
          ptr[j++]='m';
          ptr[j++]='a';
          ptr[j++]='t';
          ptr[j++]='h';
          ptr[j++]='{';
          ptr[j++]='>';
          ptr[j++]='}';
          //ptr[j++]=' ';
	}

        else if ( str[i] == '<' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='e';
          ptr[j++]='n';
          ptr[j++]='s';
          ptr[j++]='u';
          ptr[j++]='r';
          ptr[j++]='e';
          ptr[j++]='m';
          ptr[j++]='a';
          ptr[j++]='t';
          ptr[j++]='h';
          ptr[j++]='{';
          ptr[j++]='<';
          ptr[j++]='}';
          //ptr[j++]=' ';
	}


        else if ( str[i] == '}' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='}';
	}
        else if ( str[i] == '_' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='_';
	}
        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}
        else if ( str[i] == '#' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='#';
	}

        else if ( str[i] == '&' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='&';
	}

        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}

        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}



/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strtext2tex(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == '&' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='&';
	}
        else if ( str[i] == '_' ) 
	{
          ptr[j++]=' ';
	}
        else if ( str[i] == '%' ) 
	{
          ptr[j++]='\\';
          ptr[j++]='%';
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}




/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strcsv2tex(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == ';' ) 
	{
          ptr[j++]=' ';
          ptr[j++]='&';
          ptr[j++]=' ';
	}
        else if ( str[i] == 9 ) 
	{
          ptr[j++]=' ';
          ptr[j++]='&';
          ptr[j++]=' ';
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}












char *fbasewithoutfilename(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '/');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}





char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}
///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{

    char targetfile[PATH_MAX];
    char cmdi[PATH_MAX];
    char charo[PATH_MAX];
    FILE *fpout;
    int filecounter = 1;


    int i ; 
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
          {
	      printf( "---------\n" );
	      printf( "Argument %d/%d: %s\n", i, argc-1 ,  argv[ i ] );
	      if ( fexist( argv[ i ] ) == 1 )
              {
	        printf( "==> Processing (File Found): %d/%d: %s\n", i, argc-1 ,  argv[ i ] );
                strncpy(  targetfile, strtimestamp() , PATH_MAX );
                snprintf( charo, 50 , "F%d-", filecounter++);
                strncat(  targetfile , charo , PATH_MAX - strlen( targetfile ) -1 );
                strncat(  targetfile , argv[ i ] , PATH_MAX - strlen( targetfile ) -1 );

                strncpy( cmdi, " mv " , PATH_MAX );
                strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
                strncat( cmdi , argv[ i ] , PATH_MAX - strlen( cmdi ) -1 );
                strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
                strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
                strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
                strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
                printf( "CMD: %s\n", cmdi );
                system( cmdi );
             }
          }
    }

    return 0;
}



