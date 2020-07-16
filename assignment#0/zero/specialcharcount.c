/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */


#include <stdio.h> 
#include "count.h"

// We use the similar code as displayspecialcharfreq
// only add a file pointer as the extra argument and
// replace printf with fprintf
void specialcharfreqtoresult(FILE *fp, long charfreq[], int size)
{	
	for(int i = 0; i < size; i++)
	  {
	  	switch(i)
	  	{
	  		case 0:
	  			fprintf(fp, ", -> %d\n", charfreq[i]);
	  			break;
	  		case 1:
	  			fprintf(fp, ". -> %d\n", charfreq[i]);
	  			break;
	  		case 2:
	  			fprintf(fp, ": -> %d\n", charfreq[i]);
	  			break;
	  		case 3:
	  			fprintf(fp, "; -> %d\n", charfreq[i]);
	  			break;
	  		case 4:
	  			fprintf(fp, "! -> %d\n", charfreq[i]);
	  			break;
	  	}	  	
	  }
}

void specialcharcount(char *path, char *filetowrite, long charfreq[])
{

  	// TO-DO: please fill your code here ...
    // Step 1: Open all the files ending with .txt in "path" as read only mode.
    DIR* dir;  // this is a pointer to path
    struct dirent* sd;  // this is a pointer to file (d_name and d_ino)

    dir = opendir(path);  // get path from argument

    if (dir == NULL)  // check if the path exists
    {
      printf("Error! Unable to open directory.\n");
      exit(1);
    }


    char filetoread[256];
    FILE *fp;
    while ((sd=readdir(dir)) != NULL)  // go through the path directory until the end
    {
      if (strstr(sd->d_name,".txt") != NULL)  // get all *.txt files out
      {
        strcpy(filetoread,path);
        strcat(filetoread,"/");
        strcat(filetoread,sd->d_name);
        
        char buff;
        fp = fopen(filetoread,"r");  // open the txt file

        // Step 2: get char one by one 
        do
        {
          buff = fgetc(fp);
          // Step 2.1: Check if    special char
          // Step 2.2: Check which special char
          // Step 2.3: Add count number if Y to "charfreq[]"
          if (buff == ',') (*(charfreq+0))++;
          if (buff == '.') (*(charfreq+1))++;
          if (buff == ':') (*(charfreq+2))++;
          if (buff == ';') (*(charfreq+3))++;
          if (buff == '!') (*(charfreq+4))++;
        } while (buff != EOF);

        fclose(fp);  // after count, close the file
      }
    }
    // Step 3: Write result to the "filetowrite"
    fp = fopen(filetowrite,"w");
		specialcharfreqtoresult(fp, charfreq, SPECIALCHARSIZE);
    fclose(fp);
}
/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'

  
  Output: a new file named as filetowrite with the frequency of the above special characters written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/

