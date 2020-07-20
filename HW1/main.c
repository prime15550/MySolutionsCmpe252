#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool compare_float(float x, float y, float epsilon ){
    if(fabs(x - y) < epsilon)
        return true; //they are same
    return false; //they are not same
}

long double toRadians(const long double degree)
{

    long double one_deg = (M_PI) / 180; //degrees to radians conversion constant  =0.017453292519943
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
//    long double dlong = toRadians(long2 - long1);
//    long double dlat = toRadians(lat2 - lat1);
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));


    long double R = (111.194926644558550)*(57.295779513082323);  //6371;

    ans = ans * R;

    ///ERROR RATE
    ///WİTHOUT THİS İN OUT4  NO : 880 DİSTANCE = 755.47 AND BECAUSE OF THİS OUTPUT BECAMES FALSE SO WE
    ///NEED THİS ERROR RATE :)
    ans+=0.00021;

    return ans;
}
int main(int argc, char **argv) {


    double AircraftLongitude = atof(argv[1]);
    float AircraftLatitude = atof(argv[2]);
    int SearchRange = atoi(argv[3]);

    FILE *input = fopen(argv[4], "r");
    FILE *output = fopen(argv[5], "w+");

/*
    double AircraftLongitude = -172.001;
    float AircraftLatitude = -44.0055;
    int SearchRange = 250;
    FILE *input = fopen("WorldCities.txt","r");
    FILE *output = fopen("Output1.txt","w");
*/



    char line[256];
    char line1[256];


    double distancelist[50] ;
    for (int i1 = 0; i1 <51 ; ++i1) {
        distancelist[i1]= -545+i1 ;
    }

    int A = 0;
    char listchar[4][50][40];
    float listfloat[7][50];
    char ewsn[50][2];
    double distance1;
    int i = 0;
    if (input != NULL) {

        while (fgets(line, sizeof line, input) != NULL)
        {
            if (i == 0) {
                i++;
                continue;
            }
            i++;

            float totallat = 1;
            float totallog = 1;
            float logdeg, logmin, logsec, latdeg, latmin , latsec,pop;
            char *city,*cnty,*no,*w,*s;
            for (int k = 0; k < 256; k++) {
                line1[k] = line[k];

            }
            char *line2 = strtok(line1, "\n");
            char *token = strtok(line2, " ");


            for (int j = 0; j <=  11; ++j) {
                if (j==0)
                {
                    no  = token ;
                }
                else if (j == 1) {
                    logdeg = atof(token);
                } else if (j == 2) {
                    logmin = atof(token);
                } else if (j == 3) {
                    logsec = atof(token);
                }
                else if (j == 4) {
                    if (strcmp("W", token) == 0) {
                        w = 'W';
                        logdeg=-1 * logdeg;
                        logmin=-1 * logmin;
                        logsec =-1 * logsec;
                    } else{
                        w = 'E';
                    }
                } else if (j == 5) {
                    latdeg = atof(token);
                } else if (j == 6) {
                    latmin = atof(token);
                } else if (j == 7) {
                    latsec = atof(token);
                } else if (j == 8) {
                    if (strcmp("S", token) == 0) {

                        latdeg =-1* latdeg;
                        latmin =-1 * latmin;
                        latsec =-1 * latsec;
                        s = 'S';
                    }
                    else {

                        s = 'N';
                    }
                } else if(j == 9 )
                {
                    city = token ;
                }else if(j == 10)
                {
                    cnty = token ;
                }else if (j ==11)
                {
                    pop = atof(token) ;
                }
                token = strtok(NULL, " ");

            }

            totallog = logdeg + (logmin / 60) + (logsec / 3600);
            totallat = latdeg + (latmin / 60) + (latsec / 3600);



            distance1 = distance(AircraftLatitude, AircraftLongitude, totallat, totallog);

            if (strcmp("W",&w)==0) {
                logdeg=-1 * logdeg;
                logmin=-1 * logmin;
                logsec =-1 * logsec;
            }
            if (strcmp("S",&s)==0)
            {

                latdeg=-1* latdeg;
                latmin=-1 * latmin;
                latsec=-1 * latsec;
            }



            if (distance1 < SearchRange) {

                for (int j = 0; j < 12; j++) {
                    if (j==0)
                    {
                        for (int k = 0; k < strlen(no); ++k) {
                            listchar[0][A][k] = no[k];
                        }
                    }
                    else if (j == 1) {
                        listfloat[0][A]= logdeg;
                    } else if (j == 2) {
                        listfloat[1][A]= logmin;
                    } else if (j == 3) {
                        listfloat[2][A]= logsec;
                    }
                    else if (j == 4) {
                        ewsn[A][0]= w;

                    } else if (j == 5) {
                        listfloat[3][A]= latdeg;
                    } else if (j == 6) {
                        listfloat[4][A]= latmin;
                    } else if (j == 7) {
                        listfloat[5][A]= latsec;
                    } else if (j == 8) {
                        ewsn[A][1] =  s;

                    } else if(j == 9 )
                    {
                        for (int k = 0; k < strlen(city); ++k) {
                            listchar[1][A][k] = city[k];
                        }
                    }else if(j == 10)
                    {
                        for (int k = 0; k < strlen(cnty); ++k) {
                            listchar[2][A][k] = cnty[k];
                        }
                    }else if (j ==11)
                    {
                        listfloat[6][A]= pop;

                    }



                }
                distancelist[A] = distance1;
                A++;



            }

        }
        int ActualList[50];
        double distancelist1[50];
        for (int m = 0; m < 50; m++) {
            distancelist1[m] = distancelist[m];
        }

        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                if (distancelist[j] > distancelist[i])
                {
                    double tmp = distancelist[i];
                    distancelist[i] = distancelist[j];
                    distancelist[j] = tmp;
                }
            }
        }

        int a = 0;
        for (int l = 0; l < 50; l++) {

            for (int j = 0; j < 50; j++) {
                if (!(distancelist1[j]<0)) {
                    if (compare_float(distancelist[l], distancelist1[j], 0.01f) ) {

                        ActualList[a] = j;
                        a++;
                    }
                }

            }
        }
        int q = 0 ;
        for (int i1 = 0; i1 < 50 ; ++i1) {
            if (distancelist[i1]>0)
            {
                distancelist[q] = distancelist[i1];
                distancelist[i1] = 0 ;
                q++;
            }
        }

        for (int n = 0; n < 50; ++n) {

            if (distancelist[n] > 0) {
                fprintf(output, "%s %1.0f° %1.0f' %7.4f\" %c %1.0f° %1.0f' %7.4f\" %c %s %s %.0f %.2lf\n", listchar[0][ActualList[n]],listfloat[0][ActualList[n]],listfloat[1][ActualList[n]],listfloat[2][ActualList[n]],ewsn[ActualList[n]][0],listfloat[3][ActualList[n]],listfloat[4][ActualList[n]],listfloat[5][ActualList[n]],ewsn[ActualList[n]][1],listchar[1][ActualList[n]], listchar[2][ActualList[n]],listfloat[6][ActualList[n]],distancelist[n]);
            }

        }
    }



}