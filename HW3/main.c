//-----------------------------------------------------
// Title: Homework3
// Author: Tunç Gürsoy
// ID: 64528127274
// Section: 1
// Assignment: 3
//-----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int bytePerPixel = 3 ;
typedef struct
{
    char* type ;
    int height ;
    int width ;
    int headerSize ;
    unsigned char* header ;
    unsigned char* data;
}Image;

int imageInfoGetter(FILE *file,Image *image)
/**
 * return 0 is undefined data type
 * return 404 file is empty
 * return 1 is successful
 * */
{
    int value;   //to read values in file
    int n = 14 ; //n is 14 because of the img default header size is 14
    unsigned char* header = malloc(sizeof(n));
    int index = 0;
    if (file!=NULL)
    {
        do {
            if (index==n)
            {
                break;
            }
            value = fgetc(file);//File get
            if (index == 0) {
                if (value == 'R')  // if we want to read more data type we have to add else if and change n and change header size
                    {

                } else {
                    return 0; //undefined data header
                }
            }

            header[index]= value;
            index++;
        }while (value !=EOF);
    } else
    {
        return  404;//File is empty
    }

    image->header= header;
    image->headerSize = n;

    char p[3] ={((char)header[0]),((char )header[1]),((char )header[2])};
    image->type =p;
    image->height= (int)(header[5]+header[6]*256);
    image->width= (int)(header[10]*256+header[9]);



    int totalsize = n+(image->width*image->height)*3;
    unsigned char* data =malloc(totalsize-n);//data size is equal total size-header size
    fread(data,sizeof(unsigned char ),totalsize-n,file);//read data of image
    image->data= data;

    return 1 ;//successful

}
void  onedto2darr(Image *image, unsigned char  *** a)//gets image pointer and 3d array pointer equalize image data to 3d array pointer
{


    int index = 0 ;
    for (int i = 0; i <image->height ; ++i)
    {
        for (int j = 0; j <image->width ; ++j)
        {
            for (int k = 0; k < 3; ++k) {
                unsigned char  t =(unsigned char) image->data[index];
                a[i][j][k] = t;
                index++;
            }

        }
    }


}
void writeImage(Image *image, unsigned char *imageData,FILE *outputfile)//gets image pointer and output FILE and write image header and data to output file
{
    fwrite(image->header,image->headerSize,1,outputfile);
    for(int i=0; i<image->height; i++){
        fwrite(imageData+(i*image->width*bytePerPixel), bytePerPixel, image->width, outputfile);
    }
}

int corpimage(Image *pImage,int height,int width,int location_x,int location_y,Image *corpedIMG,FILE *output)//corp the image with given parameters and writeimage to output file
{
    if (strcmp(corpedIMG->header,"RGB")==0)
    {
        corpedIMG->width=width;
        corpedIMG->height=height;
        corpedIMG->header[5]=(height%256);
        corpedIMG->header[6]=(height/256);
        corpedIMG->header[10]=(width/256);
        corpedIMG->header[9]=(width%256);
    }
    unsigned char *** original=(unsigned char***)malloc(sizeof(unsigned char**)*(pImage->height));
    for (int l = 0; l <(pImage->height) ; ++l) {
        original[l]=(unsigned char**)malloc(sizeof(unsigned char*)*(pImage->width));
        for (int i = 0; i <pImage->width ; ++i) {
            original[l][i]=(unsigned char*)malloc(sizeof(unsigned char)*3);
        }
    }
    onedto2darr(pImage,original);
    unsigned char *** croped=(unsigned char***)malloc(sizeof(unsigned char**)*(height));
    for (int l = 0; l <(height) ; ++l) {
        croped[l]=(unsigned char**)malloc(sizeof(unsigned char*)*(width));
        for (int i = 0; i <width ; ++i) {
            croped[l][i]=(unsigned char*)malloc(sizeof(unsigned char)*3);
        }
    }
    for (int i = location_y,y=0; i <location_y+height ; ++i,y++)
    {
        for (int j = location_x,x=0; j < location_x+width; ++j,x++)
        {
            for (int k = 0; k <3 ; ++k) {
                if (pImage->height>i&&pImage->width>j)
                {
                    croped[y][x][k]=original[i][j][k];
                } else
                    {
                    croped[y][x][k]='\0';
                    }
            }
        }
    }
    unsigned char*  a = malloc(sizeof(unsigned char)*height*width*3);
    int s = 0 ;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i <width ; ++i) {
            for (int k = 0; k <3 ; ++k) {
                a[s]=croped[j][i][k];
                s++;
            }
        }
    }
    writeImage(corpedIMG,a,output);
    return 1 ;


}
int doublecorpimage(Image *pImage,int height,int width,int location_x,int location_y,Image *corpedIMG,FILE *output)//corp the image with given parameters and double pixels and writeimage to output file
{
    if (strcmp(corpedIMG->header,"RGB")==0)
    {
        corpedIMG->width=width*2;
        corpedIMG->height=height*2;
        corpedIMG->header[5]=(height*2)%256;
        corpedIMG->header[6]=(height*2)/256;
        corpedIMG->header[10]=((width*2)/256);
        corpedIMG->header[9]=((width*2)%256);
    } else {
        corpedIMG->width = width;
        corpedIMG->height = height;
        corpedIMG->header[23] = (height / 256);
        corpedIMG->header[22] = (height % 256);
        corpedIMG->header[19] = (width / 256);
        corpedIMG->header[18] = (width % 256);

    }
    unsigned char *** original=(unsigned char***)malloc(sizeof(unsigned char**)*(pImage->height));
    for (int l = 0; l <(pImage->height) ; ++l) {
        original[l]=(unsigned char**)malloc(sizeof(unsigned char*)*(pImage->width));
        for (int i = 0; i <pImage->width ; ++i) {
            original[l][i]=(unsigned char*)malloc(sizeof(unsigned char)*3);
        }
    }
    onedto2darr(pImage,original);
    unsigned char *** croped=(unsigned char***)malloc(sizeof(unsigned char**)*(height*2));
    for (int l = 0; l <(height*2) ; ++l) {
        croped[l]=(unsigned char**)malloc(sizeof(unsigned char*)*(width*2));
        for (int i = 0; i <width*2 ; ++i) {
            croped[l][i]=(unsigned char*)malloc(sizeof(unsigned char)*3);
        }
    }

    for (int i = location_y,y=0; i <location_y+height ; ++i,y+=2)
    {
        for (int j = location_x,x=0; j < location_x+width; ++j,x+=2)
        {
            for (int k = 0; k <3 ; ++k) {
                if (pImage->height>i&&pImage->width>j)
                {
                    croped[y][x][k]=original[i][j][k];
                    croped[y+1][x][k]=original[i][j][k];
                    croped[y][x+1][k]=original[i][j][k];
                    croped[y+1][x+1][k]=original[i][j][k];
                } else
                {
                    croped[y][x][k]='\0';
                    croped[y+1][x][k]='\0';
                    croped[y][x+1][k]='\0';
                    croped[y+1][x+1][k]='\0';
                }
            }
        }
    }
    unsigned char*  a = malloc(sizeof(unsigned char)*height*width*4*3);
    int s = 0 ;
    for (int j = 0; j < (height*2); ++j) {
        for (int i = 0; i <width*2 ; ++i) {
            for (int k = 0; k <3 ; ++k) {
                a[s]=croped[j][i][k];
                s++;
            }
        }
    }
    writeImage(corpedIMG,a,output);
    return 1 ;


}


int main(int argc, char **argv) {
    Image *img = malloc(sizeof(Image));
    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");
    char DoutputName[50] = "D";
    strcat(DoutputName,argv[2]);
    FILE *Doutput = fopen(DoutputName, " wb");
    int location_x = atoi(argv[3]);
    int location_y = atoi(argv[4]);
    int cropheight = atoi(argv[6]);
    int cropwidth = atoi(argv[5]);
    char outputname[256] ;
    strcpy(outputname,argv[2]);


    int infoGetterResult = imageInfoGetter(input,img);
    if (infoGetterResult==1)
    {
        Image crop =*img;
        {
            if (doublecorpimage(img, cropheight, cropwidth, location_x, location_y, &crop, Doutput) == 1) {
                printf("%s\n","image is successfully croped to given size and doubled ");
                //successful

            }
        }
        {

                if (corpimage(img, cropheight, cropwidth, location_x, location_y, &crop, output) == 1) {
                    printf("%s\n","image is successfully croped to given size ");

                    //successful
                }

        }
    }else if (infoGetterResult==0)
    {
        printf("%s\n","undefined image type please enter try again with .IMG type file ");
    }else if (infoGetterResult==404)
    {
        printf("%s\n","File is empty or not found please try again");
    }
    fclose(input);
    fclose(output);
    return 0;
}
