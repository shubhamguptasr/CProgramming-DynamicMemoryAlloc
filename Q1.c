#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strcat(const char *const str1, const char *const str2);


int main()
{
    char str1[50];
    char str2[50];

    printf("Please enter your 1st string: ");
    scanf("%s",str1);

    printf("Please enter your 2nd string: ");
    scanf("%s",str2);

    printf("The concatenating result is: %s ", my_strcat(str1,str2));

    return 0;
}

char *my_strcat(const char *const str1, const char *const str2){

    int str1Len = strlen(str1); //string lengths
    int str2Len = strlen(str2);
    int i,j;

    char *concatString;
    concatString = (char*)malloc((str1Len+str2Len+1)*sizeof(char)); //memory allocation

    for(i=0;i<str1Len;i++){  //loop  for the first string
        concatString[i]=str1[i]; //stores to concatString
    }

    for(j=0;j<str2Len;j++){ //loop for the second string
        concatString[j+str1Len] = str2[j]; //stores to concatstring starting at offset
    }

    return concatString;
    free(concatString);
}
