///-----------------------------------------------------
/// @Title: Term Project_Main_Part
/// @Author: Tunç Gürsoy
/// @ID: 64528127274
/// @Section: 1
/// @Assignment: 3
///-----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#define maxLineLength 256
/**
 *@note: When we run the code code gives this warning "tree.c: In function 'print':
 * tree.c:124:17: warning: function returns address" but this warning is not effecting the result
 * @author Tunç Gürsoy
 * @date 01.06.2020
 *
 *@update: Solved
 * @author: Tunç Gürsoy
 * @date 10.06.2020
 * */
void readArgument();

int main(int argc, char **argv) {
    size_of_tree = 0 ;//Size of tree equalize 0

    /* <Comment 1>
    * In this part we get given arguments and opens Input and Output Files
    *File names::
    * input: This file for read normal input file
    * output: This file for write result of requested operation (print)
    * BonusInput:  This file for read bonus input file
    * BonusOutput:  This file for write bonus input file requested operations (print,Print_Level,Count)
    */
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    FILE *BonusInput = NULL;
    FILE *BonusOutput = NULL;
    if (argv[3] != NULL) {
        BonusInput = fopen(argv[3], "r");
        BonusOutput = fopen(argv[4], "w");
    }

    /*<Comment_2>
     * lines will take normal input lines
     * lines will take Bonus input lines
     * line is for reading normal input line by line
     * line1 is for reading bonus Input line by line
     * lineCount is line count of input file
     * lineCount1 is line count of BonusInputFile
     */
    char** lines;
    char** lines1;
    char line[maxLineLength];
    char line1[maxLineLength];
    int lineCount = 0;
    int lineCount1 = 0;


    /*<Comment_3>
     * In this part if input is empty program close and returns 404
     * if input is not empty reads input line by line put in lines array
     * */
    if (input != NULL) {
        while (fgets(line, sizeof line, input) != NULL) {
            lineCount++;

        }
        fclose(input);
        int i;
        input = fopen(argv[1], "r");
        lines = malloc(sizeof(char*)*lineCount);
     for ( i = 0; i <lineCount ; ++i) {
         lines[i] = malloc(maxLineLength* sizeof(char));
     }
     i = 0;
     int j= 0  ;
     while (fgets(line, sizeof line, input) != NULL) {
         for ( j = 0; j <maxLineLength ; ++j) {
             lines[i][j] = line[j];
         }
         i++;

        }
    } else {
        return 404; //Input File is Empty ;
    }




    int i = 0;
    for ( i = 0; i < lineCount; ++i) {


        char currentLine[maxLineLength];//gets current line in lines array
        strcpy(currentLine, lines[i]);
        char argument[5][maxLineLength] ;//for gets arguments like "Print","[1]"
        int j = 0;
        for ( j = 0; j <5 ; ++j) {
            int k = 0;
            for ( k = 0; k <maxLineLength ; ++k) {
               argument[j][k]='\000';
            }
        }
        //gets currentLine and puts in argumet array
        readArgument(currentLine,argument);
        char temp[120];//For argument operations
        strcpy(temp,argument[0]);
        if (strcmp(temp, "INSERT") == 0) {
            strcpy(temp,argument[1]);
            char name[120];
            char Parentname[120];
            int Parentid;
            char *namep = strtok(temp,"[");//for get rid of "[","]","\n" if two argument unified or separate
            namep = strtok(temp,"\n");
            strcpy(name,namep);
            strcpy(temp,argument[2]);

            if (strcmp(temp,"\n")==0||strcmp(temp,"\000")==0)
            {

                setroot(name,lineCount);
                continue;
            }
            char *temp1 = strtok(temp,"]");//For get rid of "[","]"
            temp1 = strtok(temp,"[");
            if(strcmp(temp1,"ROOT")==0)
            {
                setroot(name,lineCount);
                continue;
            }
            temp1 = strtok(NULL,"[");
            char temp2[150];//For get rid of "[","]" if first operation is not successful
            if (temp1!=NULL) {
                strcpy(temp2, temp1);
                temp1 = strtok(temp,"[");
                strcmp(temp,temp1);
                strcpy(Parentname,temp);

            }
            if (temp1==NULL)
            {
                strcpy(Parentname,temp);
                strcpy(temp,argument[3]);
                temp1 = strtok(temp,"]");
                temp1 = strtok(temp,"[");
                if (temp1==NULL)
                {
                    temp1 = strtok(NULL, "[");
                }
                char p[15];//For change string to integer
                strcpy(p,temp1);
                Parentid = atoi(p);
            } else if(strcmp(temp2,"ROOT")==0)
            {
                //for set root
                setroot(name,lineCount);
                continue;
            } else
                {
                Parentid = atoi(temp2);
                }
                //addChild to given parent parameter with given name
                addChild(Parentname,Parentid,name);



        }
        else if(strcmp(temp, "DELETE") == 0)
        {
            char name[150];
            int id ;
            strcpy(temp,argument[1]);
            char *temp1 = strtok(temp,"]");//for get rid of "[","]","\n"
            temp1 = strtok(temp,"[");
            temp1 = strtok(NULL,"[");
            char temp2[150];//For get rid of "[","]" if first operation is not successful
            if (temp1!=NULL) {
                strcpy(temp2, temp1);
                temp1 = strtok(temp,"[");
                strcmp(temp,temp1);
                strcpy(name,temp);

            }
            if (temp1==NULL)
            {
                strcpy(name,temp);
                strcpy(temp,argument[2]);
                temp1 = strtok(temp,"]");
                temp1 = strtok(temp,"[");
                if (temp1==NULL)
                {
                    temp1 = strtok(NULL, "[");
                }
                char p[15];//For change string to integer
                strcpy(p,temp1);
                id = atoi(p);
            } else
            {
                id = atoi(temp2);
            }
            //deletes node equal to given  paramaters
            delete(name,id);

        }else if (strcmp(temp, "PRINT") == 0)
        {
            char name[150];
            int id ;
            strcpy(temp,argument[1]);
            char *temp1 = strtok(temp,"]");//for get rid of "[","]","\n" for name
            temp1 = strtok(temp,"[");
            temp1 = strtok(NULL,"[");
            char temp2[150];//For get rid of "[","]" if first operation is not successful
            if (temp1!=NULL) {
                strcpy(temp2, temp1);
                temp1 = strtok(temp,"[");
                strcmp(temp,temp1);
                strcpy(name,temp);

            }
            if (temp1==NULL)
            {
                strcpy(name,temp);
                strcpy(temp,argument[2]);
                temp1 = strtok(temp,"]");
                temp1 = strtok(temp,"[");
                if (temp1==NULL)
                {
                    temp1 = strtok(NULL, "[");
                }
                char p[15];//For change string to integer
                strcpy(p,temp1);
                id = atoi(p);
            } else
            {
                id = atoi(temp2);
            }
            char *pString = malloc(sizeof(char)*150000) ;
            fprintf(output,"%s",print(name,id,pString));
        }
    }
    /**
     * @attention After this line  to @line 496 for bonus input I will put standart inputs to bonus part because i
     * do not know will you give  standart argument  or not so I add to code
     * */
    // free input's array
    int l = 0;
    for ( l = 0; l <lineCount ; ++l) {
            free(lines[l]);
    }
    /*<Comment_4>
     * In this part if BonusInput is empty program close and returns 404
     * if input is not empty reads BonusInput line by line put in lines array
     * */
    if (BonusInput != NULL) {
        while (fgets(line, sizeof line1, BonusInput) != NULL) {
            lineCount1++;

        }
        fclose(BonusInput);
        input = fopen(argv[3], "r");
        lines1 = malloc(sizeof(char*)*lineCount1);
        for ( i = 0; i <lineCount1 ; ++i) {
            lines1[i] = malloc(maxLineLength* sizeof(char));
        }
        i = 0;
        int j= 0  ;
        while (fgets(line1, sizeof line1, BonusInput) != NULL) {
            for ( j = 0; j <maxLineLength ; ++j) {
                lines1[i][j] = line1[j];
            }
            i++;

        }
    } else {
        return 404; //Input File is Empty ;
    }

    if (BonusInput!=NULL) {
        for ( i = 0; i < lineCount1; ++i) {

            char currentLine[120];//gets current line in lines array
            strcpy(currentLine, lines1[i]);
            char argument[5][maxLineLength];;//for gets arguments like "Move","[2]"
            //gets currentLine and puts in argumet array
            readArgument(currentLine, argument);
            char temp[120];//for argument operations
            strcpy(temp, argument[0]);
            if (strcmp(temp, "INSERT") == 0) {
                strcpy(temp, argument[1]);
                char name[120];
                char Parentname[120];
                int Parentid;
                char *namep = strtok(temp, "[");
                namep = strtok(temp, "\n");
                strcpy(name, namep);

                strcpy(temp, argument[2]);
                if (strcmp(temp, "\000") == 0||strcmp(temp,"\n")) {
                    //set root
                    setroot(name,lineCount1);
                    continue;
                }
                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(Parentname, temp);

                }
                if (temp1 == NULL) {
                    strcpy(Parentname, temp);
                    strcpy(temp, argument[3]);
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    Parentid = atoi(p);
                } else if (strcmp(temp2, "ROOT") == 0) {
                    setroot(name,lineCount1);
                    continue;
                } else {
                    Parentid = atoi(temp2);
                }
                addChild(Parentname, Parentid, name);


            } else if (strcmp(temp, "DELETE") == 0) {
                char name[150];
                int id;
                strcpy(temp, argument[1]);
                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(name, temp);

                }
                if (temp1 == NULL) {
                    strcpy(name, temp);
                    strcpy(temp, argument[2]);
                    temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    id = atoi(p);
                } else if (strcmp(temp2, "ROOT") == 0) {
                    setroot(name,lineCount1);
                    continue;
                } else {
                    id = atoi(temp2);
                }
                delete(name, id);

            } else if (strcmp(temp, "PRINT") == 0) {
                char name[150];
                int id;
                strcpy(temp, argument[1]);
                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(name, temp);

                }
                if (temp1 == NULL) {
                    strcpy(name, temp);
                    strcpy(temp, argument[2]);
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    id = atoi(p);
                }  else {
                    id = atoi(temp2);
                }
                char *pString;
                fprintf(BonusInput, "%s", print(name, id,pString));
            }else if (strcmp(temp, "MOVE") == 0)
            {
                int s = 1 ;
                char name[150];
                int id;
                strcpy(temp, argument[s]);
                s++;
                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(name, temp);

                }
                if (temp1 == NULL) {
                    strcpy(name, temp);
                    strcpy(temp, argument[s]);
                    s++;
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    id = atoi(p);
                }  else {
                    id = atoi(temp2);
                }


                char name1[150];
                int id1;
                strcpy(temp, argument[s]);
                s++;
                temp1 = strtok(temp, "]");
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(name1, temp);

                }
                if (temp1 == NULL) {
                    strcpy(name1, temp);
                    strcpy(temp, argument[s]);
                    s++;
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    id1 = atoi(p);
                } else {
                    id1 = atoi(temp2);
                }

                move(name,id,name1,id1);


            }else if (strcmp(temp, "COUNT") == 0)
            {
                strcpy(temp, argument[1]);
                char name[120];
                char Parentname[120];
                int Parentid;
                char *namep = strtok(temp, "[");
                namep = strtok(temp, "\n");
                strcpy(name, namep);

                strcpy(temp, argument[2]);

                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(Parentname, temp);

                }
                if (temp1 == NULL) {
                    strcpy(Parentname, temp);
                    strcpy(temp, argument[3]);
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    Parentid = atoi(p);
                }  else {
                    Parentid = atoi(temp2);
                }
                fprintf(BonusOutput,"%d\n",count(name,Parentname,Parentid));
            }else if (strcmp(temp, "PRINT_LEVEL") == 0)
            {
                char name[150];
                int id;
                strcpy(temp, argument[1]);
                char *temp1 = strtok(temp, "]");//for get rid of "[","]","\n"
                temp1 = strtok(temp, "[");
                temp1 = strtok(NULL, "[");
                char temp2[150];//For get rid of "[","]" if first operation is not successful
                if (temp1 != NULL) {
                    strcpy(temp2, temp1);
                    temp1 = strtok(temp, "[");
                    strcmp(temp, temp1);
                    strcpy(name, temp);

                }
                if (temp1 == NULL) {
                    strcpy(name, temp);
                    strcpy(temp, argument[2]);
                    temp1 = strtok(temp, "]");
                    temp1 = strtok(temp, "[");
                    if (temp1 == NULL) {
                        temp1 = strtok(NULL, "[");
                    }
                    char p[15];//for Change string to Integer
                    strcpy(p, temp1);
                    id = atoi(p);
                }  else {
                    id = atoi(temp2);
                }
                PRINT_LEVEL(name,id,BonusOutput);
            }
        }
    }
    // free bonus input arrays
    for ( l = 0; l <lineCount1 ; ++l) {
        free(lines1[l]);
    }
    //Close files
    fclose(input);
    fclose(output);

    if(BonusInput!=NULL&&BonusOutput!=NULL)
    {
        fclose(BonusInput);
        fclose(BonusOutput);
    }

}
/**
 * @def This  method is for trim given s  line  input s and h
 * @details  trims the s and equalize h
 * */
void trim ( char *s)
{
    int i;

    while (isspace (*s)) s++;   // skip left side white spaces
    for (i = strlen (s) - 1; (isspace (s[i])); i--) ;   // skip right side white spaces
    s[i + 1] = '\0';


}
/**
 * @def this method for reading arguments and gets input line and puts in temp given temp array
 * @details make use trim method to cut unneccesary part beginning and ending of given input line
 * and use token to get unneccary part between argument @noteStarts This I did not see there are no tab press between
 * arguments so I won't do trim i can but i won't because it cause extra work.@noteEnds
 * */
void readArgument(char* input,char temp[5][maxLineLength])
{


    trim(input);


    char *token = strtok(input," ");
    char chartemp[50];

    if (token==NULL)
    {
        strcpy(temp[0], "Pass");
        return;
    } else
        {
            strcpy(chartemp,token);

        }



    strcpy(temp[0] , chartemp);
    int i = 1 ;
    while (token!=NULL)
    {
        token = strtok(NULL," ");
        if(token!=NULL&&strcmp(token,"\t")!=0) {
            strcpy(chartemp, token);
            strcpy(temp[i] , chartemp);
            i++;
        }
    }
    free(token);
}
