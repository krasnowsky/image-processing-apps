// gcc main.cpp -lstdc++ -o main

#include <iostream>
#include "CImg.h"

using namespace cimg_library;

void dilation(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> dilation(image.width(),image.height(),1,1,0);
    int mask[3][3] = {  255, 255, 255,
                        255, 255, 255,
                        255, 255, 255};

    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            if (image(i,j) == mask[1][1])
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++) dilation(i-1+x,j-1+y) = 255;
                }
            }
        }
    }
    dilation.save_bmp(output);
}

void erosion(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> erosion(image.width(),image.height(),1,1,255);

    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            if (image(i,j) == 0)
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++) erosion(i-1+x,j-1+y) = 0;
                }
            }
        }
    }
    erosion.save_bmp(output);
}

void opening(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> opening(image.width(),image.height(),1,1,255);

    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            if (image(i,j) == 0)
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++) opening(i-1+x,j-1+y) = 0;
                }
            }
        }
    }

    CImg<unsigned char> opening_final(image.width(),image.height(),1,1,0);

    int mask[3][3] = {  255, 255, 255,
                        255, 255, 255,
                        255, 255, 255};

    for (int a = 1; a < opening.width()-1; a++)
    {
        for (int b = 1; b < opening.height()-1; b++)
        {
            if (opening(a,b) == mask[1][1])
            {
                for (int z = 0; z < 3; z++)
                {
                    for (int v = 0; v < 3; v++) opening_final(a-1+z,b-1+v) = 255;
                }
            }
        }
    }

    opening_final.save_bmp(output);
}

void closing(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> closing(image.width(),image.height(),1,1,0);

    int mask[3][3] = {  255, 255, 255,
                        255, 255, 255,
                        255, 255, 255};

    for (int a = 1; a < image.width()-1; a++)
    {
        for (int b = 1; b < image.height()-1; b++)
        {
            if (image(a,b) == mask[1][1])
            {
                for (int z = 0; z < 3; z++)
                {
                    for (int v = 0; v < 3; v++) closing(a-1+z,b-1+v) = 255;
                }
            }
        }
    }

    CImg<unsigned char> closing_final(image.width(),image.height(),1,1,255);

    for (int i = 1; i < closing.width()-1; i++)
    {
        for (int j = 1; j < closing.height()-1; j++)
        {
            if (closing(i,j) == 0)
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++) closing_final(i-1+x,j-1+y) = 0;
                }
            }
        }
    }

    closing_final.save_bmp(output);
}

void htm(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> htm(image.width(),image.height(),1,1,0);

    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            /*if (image(i,j-1) == 255         &&
                image(i,j) == 255           &&
                image(i+1,j) == 255         &&
                image(i-1,j) == 0           &&
                image(i-1,j+1) == 0         &&
                image(i,j+1) == 0)          htm(i,j) = 255;

            if (image(i,j-1) == 255         &&
                image(i,j) == 255           &&
                image(i+1,j) == 0           &&
                image(i-1,j) == 255         &&
                image(i+1,j+1) == 0         &&
                image(i,j+1) == 0)          htm(i,j) = 255;

            if (image(i,j-1) == 0           &&
                image(i,j) == 255           &&
                image(i+1,j) == 0           &&
                image(i-1,j) == 255         &&
                image(i+1,j-1) == 0         &&
                image(i,j+1) == 255)        htm(i,j) = 255;

            if (image(i,j-1) == 0           &&
                image(i,j) == 255           &&
                image(i+1,j) == 255         &&
                image(i-1,j) == 0           &&
                image(i-1,j-1) == 0         &&
                image(i,j+1) == 255)        htm(i,j) = 255;*/

            if (image(i-1,j-1) == 255        &&
                image(i,j-1) == 255          &&
                image(i+1,j-1) == 0          &&
                image(i-1,j) == 0            &&
                image(i,j) == 255            &&
                image(i+1,j) == 0            &&
                image(i-1,j+1) == 0          &&
                image(i,j+1) == 255          &&
                image(i+1,j+1) == 0)
                {

                    htm(i,j) = 255;

                }

        }
    }

    htm.save_bmp(output);
}

void m4(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> m4(image.width(),image.height(),1,1,0);

    bool check1 = true;
    while(check1)
    {

        for (int i = 1; i < image.width()-1; i++)
        {
            for (int j = 1; j < image.height()-1; j++)
            {
                if (image(i,j) == 0             &&
                    image(i+1, j-1) == 255      &&
                    image(i+1, j) == 255        &&
                    image(i+1, j+1) == 255) m4(i,j) = 255;




                if (image(i,j) == 0             &&
                    image(i-1, j-1) == 255      &&
                    image(i, j-1) == 255        &&
                    image(i+1, j-1) == 255) m4(i,j) = 255;


                if (image(i,j) == 0             &&
                    image(i-1, j-1) == 255      &&
                    image(i-1, j) == 255        &&
                    image(i-1, j+1) == 255) m4(i,j) = 255;




                if (image(i,j) == 0             &&
                    image(i-1, j+1) == 255      &&
                    image(i, j+1) == 255         &&
                    image(i+1, j+1) == 255) m4(i,j) = 255;



                if(image(i,j) == 255) m4(i,j) = 255;

            }
        }

        check1 = false;

        for (int i = 0; i < image.width(); i++)
        {
            for (int j = 0; j < image.height(); j++)
            {
                if(image(i,j) != m4(i,j)) check1 = true;

                image(i,j) = m4(i,j);
            }
        }


    }

     m4.save_bmp(output);
}

void grow_rec(CImg<unsigned char> &image, CImg<unsigned char> &grow_img, bool* check, int i, int j, int range)
{

    grow_img(i,j) = image(i,j);

    if(!check[j*image.width()+i])
    {
        check[j*image.width()+i] = true;

        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if(image(i-1+x,j-1+y)<=image(i,j)+range && image(i-1+x,j-1+y)>=image(i,j)-range && x*y != 1) grow_rec(image, grow_img, check, i-1+x, j-1+y, range);
            }
        }
    }
}


void growing(char* input, char* output)
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> grow_img(image.width(), image.height(), 1, 1, 0);
    int range = 15;
    bool* check = new bool[image.width()*image.height()]();

    grow_rec(image, grow_img, check, 145, 29, range); // 147 - x coordinate, 29 - y coordinate of the image one wants to process

    grow_img.save_bmp(output);
}

int main(int argc, char *argv[])
{
    char const *F1 = "--input";
    char const *F2 = "--output";

    char *input;
    char *output;

    char const *D = "--dilation";
    char const *E = "--erosion";
    char const *O = "--opening";
    char const *C = "--closing";
    char const *H = "--htm";
    char const *M = "--m4";
    char const *G = "--growing";

    int choice;
    int parameter;

    for(int i = 0; i<argc; i++)
        {
            if (strcmp(argv[i], F1) == 0 )
            {
                input = argv[i+1];
            }
            else if (strcmp(argv[i], F2) == 0 )
            {
                output = argv[i+1];
            }

            if      (strcmp(argv[i], D) == 0) choice = 1;
            else if (strcmp(argv[i], E) == 0) choice = 2;
            else if (strcmp(argv[i], O) == 0) choice = 3;
            else if (strcmp(argv[i], C) == 0) choice = 4;
            else if (strcmp(argv[i], H) == 0) choice = 5;
            else if (strcmp(argv[i], M) == 0) choice = 6;
            else if (strcmp(argv[i], G) == 0) choice = 7;

    }


   switch(choice)
   {
    case 1:
        {
            dilation(input, output);
            break;
        }

    case 2:
        {
            erosion(input, output);
            break;
        }

    case 3:
        {
            opening(input, output);
            break;
        }

    case 4:
        {
            closing(input, output);
            break;
        }

    case 5:
        {
            htm(input, output);
            break;
        }
    case 6:
        {
            m4(input, output);
            break;
        }

     case 7:
        {
            growing(input, output);
            break;
        }
   }

    return 0;
}
