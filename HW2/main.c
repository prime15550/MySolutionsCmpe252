//-----------------------------------------------------
// Title: Homework 2
// Author: Tunç Gürsoy
// ID: 64528127274
// Section: 1
// Assignment: 2
//-----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char **argv) {

    FILE *input = fopen(argv[1], "r");
    char* CountryInput = argv[2];
    FILE *output = fopen(argv[3], "w+");
//
//    FILE *input = fopen("WorldCitiesHw2.csv", "r");
//    char CountryInput[] = "*";
//    FILE *output = fopen("Out1.txt", "w+");

    fprintf(output,"%s","ID,CITY_NAME,CNTRY_NAME,STATUS,FIPS_CNTRY,POP,POP_RANK,POP_CLASS\n");

    int isitall = 1 ; //false
    char line[240];
    char lines[2540][120];
    char linessorted[2540][120];
    char Cities[2540][30];
    for (int i = 0; i < strlen(CountryInput); ++i) {
        if (strcmp(CountryInput, "*") == 0) {
            isitall = 0; //true
        } else {
            if (CountryInput[i] == '*') {
                CountryInput[i] = NULL;
                break;
            }
            CountryInput[i] = toupper(CountryInput[i]);//turn into upper chracter country input
        }
    }
    if (input != NULL) {

        int t = 0;
        while (fgets(line, sizeof line, input) != NULL) { //reads line from input
            if (t == 0) {
                t++;
                continue;
            }
            strcpy(lines[t-1],line);//copy the line in lines array
            char *token = strtok(line, ",");
            token = strtok(NULL, ",");

            char City[strlen(token)];
            for (int j = 0; j < strlen(token); ++j) {
                City[j] = toupper(token[j]);
            }
            for (int i = 0; i < strlen(token); ++i) {
                Cities[t - 1][i] = City[i];
            }
            t++;
        }
        //sort the cities
        char temp[30];
        int count = 2539;
        for (int i = 0; i <= count; i++)
            for (int j = i + 1; j <= count; j++) {
                if (strcmp(Cities[i], Cities[j]) > 0) {
                    strcpy(temp, Cities[i]);
                    strcpy(Cities[i], Cities[j]);
                    strcpy(Cities[j], temp);
                }
            }


    }

    //sort line with help of sorted cities
    for (int k = 0; k < 2540 ; ++k) {
        for (int i = 0; i < 2540; ++i) {
            char temp[120];
            strcpy(temp, lines[i]);
            char *token = strtok(temp, ",");
            token = strtok(NULL, ",");
            for (int q = 0; q < strlen(token); ++q) {
                token[q] = toupper(token[q]);
            }
            if (strcmp(Cities[k], token) == 0) {
                if(k>1)
                {
                    if (strcmp(Cities[k], Cities[k+1]) == 0&&strcmp(Cities[k+2],Cities[k])==0)
                    {
                        for (int w = 0; w < 2540; ++w)
                        {
                            if (w!=i) {
                                char temp2[120];
                                strcpy(temp2, lines[w]);
                                char *tok = strtok(temp2, ",");
                                tok = strtok(NULL, ",");
                                for (int q = 0; q < strlen(token); ++q) {
                                    tok[q] = toupper(tok[q]);
                                }
                                if (strcmp(Cities[k], tok) == 0)
                                {
                                    for (int b = 0; b < 2540; ++b) {
                                        if (w != i) {
                                            if (w != b&&i!=b) {
                                                char temp3[120];
                                                strcpy(temp3, lines[b]);
                                                char *toke = strtok(temp3, ",");
                                                toke = strtok(NULL, ",");
                                                for (int q = 0; q < strlen(token); ++q) {
                                                    toke[q] = toupper(toke[q]);
                                                }
                                                if (strcmp(Cities[k], toke) == 0)
                                                {
                                                    strcpy(linessorted[k], lines[b]);
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                        }


                    }else if (strcmp(Cities[k], Cities[k+1]) == 0)
                    {
                        for (int w = 0; w < 2540; ++w)
                        {
                            if (w!=i)
                            {
                                char temp2[120];
                                strcpy(temp2, lines[w]);
                                char *tok = strtok(temp2, ",");
                                tok = strtok(NULL, ",");
                                for (int q = 0; q < strlen(token); ++q) {
                                    tok[q] = toupper(tok[q]);
                                }
                                if (strcmp(Cities[k], tok) == 0)
                                {
                                    strcpy(linessorted[k], lines[w]);
                                }
                            }
                        }
                    }else
                    {
                        strcpy(linessorted[k], lines[i]);
                    }
                }
                else
                {
                    strcpy(linessorted[k], lines[i]);
                }
            }

        }
    }


    //Country list ;
    char Country[2540][300];
    for (int k = 0; k < 2540 ; ++k) {
        char temp[120] ;
        strcpy(temp,linessorted[k]);
        char *token = strtok(temp, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        strcpy(Country[k],token);


    }





    //Find country with countryinput
    char actual[2540][30];
    int q = 0 ;
    for (int l = 0; l <2540 ; ++l) {


        int isit = 1 ; //false ;
        for (int j = 0; j <strlen(CountryInput) ; ++j)
        {
            Country[l][j] = toupper(Country[l][j]);
            if (Country[l][j]==CountryInput[j])
            {
                if(isit==1) {
                    isit = 1;
                }
            }else
            {
                isit =0 ;
            }
        }
        if (isit==1)
        {
            strcpy(actual[q],Country[l]);
            q++;
        }


    }
    //not repeated countries
    char actualnotrepeated[2540][30];
    int n  = 2540,count= 0 ,isit ;
    for (int i = 0; i < n; ++i)
    {
        isit =1 ;//false
        for (int l = 0; l <n ; ++l) {
            if (strcmp(actual[i],actualnotrepeated[l])== 0)
            {
                isit = 0 ;//true
            }
        }
        if (isit==1)
        {
            strcpy(actualnotrepeated[count],actual[i]) ;
            count++;
        }
    }



    //Printing lines to output file
    if (isitall != 0) {
        for (int i1 = 0; i1 < n; ++i1) {

            isit = 1;
            char temp[120];
            strcpy(temp, linessorted[i1]);
            char *token = strtok(temp, ",");
            token = strtok(NULL, ",");
            token = strtok(NULL, ",");
            for (int j = 0; j < strlen(token); ++j) {
                token[j] = toupper(token[j]);
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j <strlen(actualnotrepeated[i]) ; ++j) {
                    actualnotrepeated[i][j] = toupper(actualnotrepeated[i][j]);
                }
                if (strcmp(token, actualnotrepeated[i]) == 0) {
                    isit = 0;
                }
            }

            if (isit == 0) {
                fprintf(output, "%s", linessorted[i1]);
            }
        }
    }else
    {
        for (int i = 0; i <n ; ++i) {
            fprintf(output, "%s", linessorted[i]);

        }
    }
    return 0;
}










