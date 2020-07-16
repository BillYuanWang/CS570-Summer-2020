/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h> 
#include "count.h"

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (A-Z a-z, case sensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from A - Z a - z:
      alphabetfreq[0]: the frequency of 'A'
      alphabetfreq[1]: the frequency of 'B'
         ... ...
      alphabetfreq[25]:the frequency of 'Z'
      alphabetfreq[26]:the frequency of 'a'
         ...  ...
      alphabetfreq[51]:the frequency of 'z'
  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (A-Z a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     A -> 200
     B -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetfreqtoresult(FILE *fp, long charfreq[], int size)
{
	for(int i = 0; i < size/2; i++)   // print upper case letter frequency
	  {
	  	fprintf(fp, "%c -> %d\n", (char)(i+65), charfreq[i]);
	  }

       	for(int i = size/2; i < size; i++)  // print lower case letter frequency
	  {
	  	fprintf(fp, "%c -> %d\n", (char)(i+65 + 6), charfreq[i]);  
	  }
}

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
   // TO-DO: please fill your code here ...
   // Step 1: Open the file in "path" as read only mode.
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
            // Step 2.1: Check if    alphabet char
            if (isalpha(buff))
            {
               // Step 2.2: Check which alphabet char
               if (islower(buff))
               {
               (*(alphabetfreq+(int)buff-71))++;
               }
               else
               {
               (*(alphabetfreq+(int)buff-65))++;
               }
            }
         // Step 2.3: Add count number if Y to "charfreq[]"
         } while (buff != EOF);

         fclose(fp);  // after count, close the file
      }
   }
   // Step 3: Write result to the "filetowrite"
   fp = fopen(filetowrite,"w");
   alphabetfreqtoresult(fp, alphabetfreq, ALPHABETSIZE);
   fclose(fp);
}
