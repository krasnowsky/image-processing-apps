// gcc main.cpp -lstdc++ -o main

#include <iostream>
#include "CImg.h"
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace cimg_library;

int brightness(int img, int parameter)
{
    if (img+parameter >= 255) img = 255;
    else if (img+parameter <= 0) img = 0;
    else img +=parameter;
    return img;
}

void help()
{
    std::cout << "\n---------HELP CENTER----------" << std::endl;
    std::cout << "Possible commands to use:" << std::endl;
    std::cout << "1. --input [path]" << std::endl;
    std::cout << "2. --output [path]" << std::endl;
    std::cout << "3. --function [name] -argument [value]\n" << std::endl;
    std::cout << "Possible functions to use:" << std::endl;
    std::cout << "1. Brightness modification [--brightness] " << std::endl;
    std::cout << "2. Contrast modification [--contrast]" << std::endl;
    std::cout << "3. Negative [--negative]" << std::endl;
    std::cout << "4. Horizontal flip [--hflip]" << std::endl;
    std::cout << "5. Vertical flip [--vflip]" << std::endl;
    std::cout << "6. Diagonal flip [--dflip]" << std::endl;
    std::cout << "7. Shrinking [--shrink]" << std::endl;
    std::cout << "8. Enlargement [--enlarge]" << std::endl;
    std::cout << "9. Min filter [--min]" << std::endl;
    std::cout << "10. Max filter [--max]" << std::endl;
    std::cout << "11. Median filter [--median]" << std::endl;
    std::cout << "12. Mean square error [--mse]" << std::endl;
    std::cout << "13. Peak mean square error [--pmse]" << std::endl;
    std::cout << "14. Signal to noise ratio [--snr]" << std::endl;
    std::cout << "15. Peak signal to noise ratio [--psnr]" << std::endl;
    std::cout << "16. Maximum difference [--md]" << std::endl;
}

float check(float value)
{
   if(value < 0) value = 0;
   else if (value > 255) value = 255;
   return value;
}

void insertionSort(int window[])
{
    int temp, i , j;
    for(i = 0; i < 9; i++)
    {
        temp = window[i];
        for(j = i-1; j >= 0 && temp < window[j]; j--)
        {
            window[j+1] = window[j];
        }
        window[j+1] = temp;
    }
}

int main(int argc, char *argv[])
{
    char const *F1 = "--help";
    char const *F2 = "--input";
    char const *F3 = "--output";

    char *input;
    char *output;

    char const *B1 = "--brightness";
    char const *B2 = "--contrast";
    char const *B3 = "--negative";

    char const *G1 = "--hflip";
    char const *G2 = "--vflip";
    char const *G3 = "--dflip";
    char const *G4 = "--shrink";
    char const *G5 = "--enlarge";

    char const *N1 = "--min";
    char const *N2 = "--max";
    char const *N3 = "--median";

    char const *E1 = "--mse";
    char const *E2 = "--pmse";
    char const *E3 = "--snr";
    char const *E4 = "--psnr";
    char const *E5 = "--md";

    char const *A = "-argument";

    int choice;
    int parameter;

    for(int i = 0; i<argc; i++)
    {
        if (strcmp(argv[i], F1) == 0)
        {
            help();
        }
        else if (strcmp(argv[i], F2) == 0 )
        {
            input = argv[i+1];
        }
        else if (strcmp(argv[i], F3) == 0 )
        {
            output = argv[i+1];
        }

        if (strcmp(argv[i], B1) == 0) choice = 1;
        else if (strcmp(argv[i], B2) == 0) choice = 2;
        else if (strcmp(argv[i], B3) == 0) choice = 3;

        else if (strcmp(argv[i], G1) == 0) choice = 4;
        else if (strcmp(argv[i], G2) == 0) choice = 5;
        else if (strcmp(argv[i], G3) == 0) choice = 6;
        else if (strcmp(argv[i], G4) == 0) choice = 7;
        else if (strcmp(argv[i], G5) == 0) choice = 8;

        else if (strcmp(argv[i], N1) == 0) choice = 9;
        else if (strcmp(argv[i], N2) == 0) choice = 10;
        else if (strcmp(argv[i], N3) == 0) choice = 11;

        else if (strcmp(argv[i], E1) == 0) choice = 12;
        else if (strcmp(argv[i], E2) == 0) choice = 13;
        else if (strcmp(argv[i], E3) == 0) choice = 14;
        else if (strcmp(argv[i], E4) == 0) choice = 15;
        else if (strcmp(argv[i], E5) == 0) choice = 16;

        else if (strcmp(argv[i], A) == 0) parameter = atoi(argv[i+1]);
    }

    CImg<unsigned char> image(input);

    switch(choice)
    {

        case 1:
        {
            for (int x = 0; x < image.width(); x++) // brightness modification
            {
                for (int y = 0; y < image.height(); y++)
                {
                    int valR = image(x, y, 0);
                    int valG = image(x, y, 1);
                    int valB = image(x, y, 2);

                    int newR = brightness(valR, parameter);
                    image(x, y, 0) = newR;
                    int newG = brightness(valG, parameter);
                    image (x, y, 1) = newG;
                    int newB = brightness(valB, parameter);
                    image (x, y, 2) = newB;
                }
            }
            image.save_bmp(output);
            break;
        }

        case 2:     // contrast modification
        {
            float f;
            f = (259*(255+(float)parameter))/(255*(259-(float)parameter));

            for (int x = 0; x < image.width(); x++)
            {
                for (int y = 0; y < image.height(); y++)
                {
                    float valR = image(x, y, 0);
                    float valG = image(x, y, 1);
                    float valB = image(x, y, 2);

                    float newR = f*(valR-128)+128;
                    float newG = f*(valG-128)+128;
                    float newB = f*(valB-128)+128;

                    image(x, y, 0) = check(newR);
                    image(x, y, 1) = check(newG);
                    image(x, y, 2) = check(newB);
                }
            }
            image.save_bmp(output);
            break;
        }

        case 3:
        {
            for (int x = 0; x < image.width(); x++) // negative
            {
                for (int y = 0; y < image.height(); y++)
                {
                    float valR = image(x, y, 0);
                    float valG = image(x, y, 1);
                    float valB = image(x, y, 2);

                    int newR = 255 - valR;
                    image(x, y, 0) = newR;
                    int newG = 255 - valG;
                    image (x, y, 1) = newG;
                    int newB = 255 - valB;
                    image (x, y, 2) = newB;
                }
            }
            image.save_bmp(output);
            break;
        }

        case 4:
        {
            CImg<unsigned char> fliph(image.width(),image.height(),1,3,0);// horizontal flip
            for (int x = 0; x < image.width(); x++)
                {
                    for (int y = 0; y < image.height(); y++)
                    {
                        float valR = image(x, y, 0);
                        float valG = image(x, y, 1);
                        float valB = image(x, y, 2);

                        fliph((image.width()-1)-x, y, 0) = valR;
                        fliph((image.width()-1)-x, y, 1) = valG;
                        fliph((image.width()-1)-x, y, 2) = valB;
                    }
                }
            fliph.save_bmp(output);
            break;
        }

        case 5:
        {
            CImg<unsigned char> flipv(image.width(),image.height(),1,3,0);// vertical flip
            for (int x = 0; x < image.width(); x++)
                {
                    for (int y = 0; y < image.height(); y++)
                    {
                        float valR = image(x, y, 0);
                        float valG = image(x, y, 1);
                        float valB = image(x, y, 2);

                        flipv(x,(image.height()-1)-y, 0) = valR;
                        flipv(x,(image.height()-1)-y, 1) = valG;
                        flipv(x,(image.height()-1)-y, 2) = valB;
                    }
                }
            flipv.save_bmp(output);
            break;
        }

        case 6:
        {
            CImg<unsigned char> flipd1(image.width(),image.height(),1,3,0);// diagonal flip
            for (int x = 0; x < image.width(); x++)
                {
                    for (int y = 0; y < image.height(); y++)
                    {
                        float valR = image(x, y, 0);
                        float valG = image(x, y, 1);
                        float valB = image(x, y, 2);

                        flipd1(y, x, 0) = valR;
                        flipd1(y, x, 1) = valG;
                        flipd1(y, x, 2) = valB;
                    }
                }
            flipd1.save_bmp(output);
            break;
        }

/*
        case 6:
            CImg<unsigned char> flipd2(image.width(),image.height(),1,3,0);// diagonal flip
            for (int x = 0; x < image.width(); x++)
                {
                    for (int y = 0; y < image.height(); y++)
                    {
                        float valR = image(x, y, 0);
                        float valG = image(x, y, 1);
                        float valB = image(x, y, 2);

                        flipd2((image.height()-1)-y, (image.width()-1)-x, 0) = valR;
                        flipd2((image.height()-1)-y, (image.width()-1)-x, 1) = valG;
                        flipd2((image.height()-1)-y, (image.width()-1)-x, 2) = valB;

                    }
                }
            flipd2.save_bmp(output);
            break;
*/

        case 7:
        {
            CImg<unsigned char> shrink(image.width()/2, image.height()/2, 1, 3, 0); //shrinking

                    int windowR[4];
                    int windowG[4];
                    int windowB[4];

                    for(int x = 0; x < image.width() - 1; x+=2)
                    {
                        for(int y = 0; y < image.height() - 1; y+=2)
                        {
                            windowR[0] = image(x , y , 0);
                            windowR[1] = image(x+1 , y , 0);
                            windowR[2] = image(x , y+1 , 0);
                            windowR[3] = image(x+1 , y+1 , 0);
                            int avgR = (windowR[0]+windowR[1]+windowR[2]+windowR[3])/4;

                            windowG[0] = image(x,y,1);
                            windowG[1] = image(x+1 , y , 1);
                            windowG[2] = image(x , y+1 , 1);
                            windowG[3] = image(x+1 , y+1 , 1);
                            int avgG = (windowG[0]+windowG[1]+windowG[2]+windowG[3])/4;

                            windowB[0] = image(x,y,2);
                            windowB[1] = image(x+1 , y , 2);
                            windowB[2] = image(x , y+1 , 2);
                            windowB[3] = image(x+1 , y+1 , 2);
                            int avgB = (windowB[0]+windowB[1]+windowB[2]+windowB[3])/4;

                            if(x==0 && y==0)
                            {
                                shrink(x,y,0)=avgR;
                                shrink(x,y,1)=avgG;
                                shrink(x,y,2)=avgB;
                            }
                            else if (x==0)
                            {
                                shrink(x,y/2,0)=avgR;
                                shrink(x,y/2,1)=avgG;
                                shrink(x,y/2,2)=avgB;
                            }
                            else if (y==0)
                            {
                                shrink(x/2,y,0)=avgR;
                                shrink(x/2,y,1)=avgG;
                                shrink(x/2,y,2)=avgB;
                            }
                            else
                            {
                                shrink(x/2,y/2,0)=avgR;
                                shrink(x/2,y/2,1)=avgG;
                                shrink(x/2,y/2,2)=avgB;
                            }
                        }
                    }


                   shrink.save_bmp(output);
                   break;
        }

            case 8:
            {
                CImg<unsigned char> enlarge(2*image.width()-2, 2*image.height()-2, 1, 3, 0); //enlargement

                for(int x = 0; x < image.width() - 1; x++)
                {
                    for(int y = 0; y < image.height() - 1; y++)
                    {
                        if(x==0 && y==0)
                        {
                            int valR = image(x, y, 0);
                            enlarge(x, y, 0) = valR;
                            enlarge(x+1, y, 0) = valR;
                            enlarge(x, y+1, 0) = valR;
                            enlarge(x+1, y+1, 0) = valR;

                            int valG = image(x, y, 1);
                            enlarge(x, y, 1) = valG;
                            enlarge(x+1, y, 1) = valG;
                            enlarge(x, y+1, 1) = valG;
                            enlarge(x+1, y+1, 1) = valG;

                            int valB = image(x, y, 2);
                            enlarge(x, y, 2) = valB;
                            enlarge(x+1, y, 2) = valB;
                            enlarge(x, y+1, 2) = valB;
                            enlarge(x+1, y+1, 2) = valB;
                        }
                        else if (x==0)
                        {
                            int valR = image(x, y, 0);
                            enlarge(x, 2*y, 0) = valR;
                            enlarge(x+1, 2*y, 0) = valR;
                            enlarge(x, 2*y+1, 0) = valR;
                            enlarge(x+1, 2*y+1, 0) = valR;

                            int valG = image(x, y, 1);
                            enlarge(x, 2*y, 1) = valG;
                            enlarge(x+1, 2*y, 1) = valG;
                            enlarge(x, 2*y+1, 1) = valG;
                            enlarge(x+1, 2*y+1, 1) = valG;

                            int valB = image(x, y, 2);
                            enlarge(x, 2*y, 2) = valB;
                            enlarge(x+1, 2*y, 2) = valB;
                            enlarge(x, 2*y+1, 2) = valB;
                            enlarge(x+1, 2*y+1, 2) = valB;
                        }
                        else if (y==0)
                        {
                            int valR = image(x, y, 0);
                            enlarge(2*x, y, 0) = valR;
                            enlarge(2*x+1, y, 0) = valR;
                            enlarge(2*x, y+1, 0) = valR;
                            enlarge(2*x+1, y+1, 0) = valR;

                            int valG = image(x, y, 1);
                            enlarge(2*x, y, 1) = valG;
                            enlarge(2*x+1, y, 1) = valG;
                            enlarge(2*x, y+1, 1) = valG;
                            enlarge(2*x+1, y+1, 1) = valG;

                            int valB = image(x, y, 2);
                            enlarge(2*x, y, 2) = valB;
                            enlarge(2*x+1, y, 2) = valB;
                            enlarge(2*x, y+1, 2) = valB;
                            enlarge(2*x+1, y+1, 2) = valB;
                        }
                        else
                        {
                            int valR = image(x, y, 0);
                            enlarge(2*x, 2*y, 0) = valR;
                            enlarge(2*x+1, 2*y, 0) = valR;
                            enlarge(2*x, 2*y+1, 0) = valR;
                            enlarge(2*x+1, 2*y+1, 0) = valR;

                            int valG = image(x, y, 1);
                            enlarge(2*x, 2*y, 1) = valG;
                            enlarge(2*x+1, 2*y, 1) = valG;
                            enlarge(2*x, 2*y+1, 1) = valG;
                            enlarge(2*x+1, 2*y+1, 1) = valG;

                            int valB = image(x, y, 2);
                            enlarge(2*x, 2*y, 2) = valB;
                            enlarge(2*x+1, 2*y, 2) = valB;
                            enlarge(2*x, 2*y+1, 2) = valB;
                            enlarge(2*x+1, 2*y+1, 2) = valB;
                        }
                    }
                }


               enlarge.save_bmp(output);
               break;
            }

            case 9:
            {
                CImg<unsigned char> minimal(image.width(),image.height(),1,3,0); //minimal
                        int windowR[9];
                        int windowG[9];
                        int windowB[9];

                        for(int x = 1; x < image.width() - 1; x++)
                        {
                            for(int y = 1; y < image.height() - 1; y++)
                            {
                                windowR[0] = image(x - 1 ,y - 1, 0);
                                windowR[1] = image(x, y - 1, 0);
                                windowR[2] = image(x + 1, y - 1, 0);
                                windowR[3] = image(x - 1, y, 0);
                                windowR[4] = image(x, y, 0);
                                windowR[5] = image(x + 1, y, 0);
                                windowR[6] = image(x - 1, y + 1, 0);
                                windowR[7] = image(x, y + 1, 0);
                                windowR[8] = image(x + 1, y + 1, 0);

                                windowG[0] = image(x - 1 ,y - 1, 1);
                                windowG[1] = image(x, y - 1, 1);
                                windowG[2] = image(x + 1, y - 1, 1);
                                windowG[3] = image(x - 1, y, 1);
                                windowG[4] = image(x, y, 1);
                                windowG[5] = image(x + 1, y, 1);
                                windowG[6] = image(x - 1, y + 1, 1);
                                windowG[7] = image(x, y + 1, 1);
                                windowG[8] = image(x + 1, y + 1, 1);

                                windowB[0] = image(x - 1 ,y - 1, 2);
                                windowB[1] = image(x, y - 1, 2);
                                windowB[2] = image(x + 1, y - 1, 2);
                                windowB[3] = image(x - 1, y, 2);
                                windowB[4] = image(x, y, 2);
                                windowB[5] = image(x + 1, y, 2);
                                windowB[6] = image(x - 1, y + 1, 2);
                                windowB[7] = image(x, y + 1, 2);
                                windowB[8] = image(x + 1, y + 1, 2);

                                insertionSort(windowR);
                                insertionSort(windowG);
                                insertionSort(windowB);

                                minimal (x,y,0) = windowR[0];
                                minimal (x,y,1) = windowG[0];
                                minimal (x,y,2) = windowB[0];
                            }
                        }

                       minimal.save_bmp(output);
                       break;
            }

            case 10:
            {
                 CImg<unsigned char> maximum(image.width(),image.height(),1,3,0); //maximum
                        int windowR[9];
                        int windowG[9];
                        int windowB[9];

                        for(int x = 1; x < image.width() - 1; x++)
                        {
                            for(int y = 1; y < image.height() - 1; y++)
                            {
                                windowR[0] = image(x - 1 ,y - 1, 0);
                                windowR[1] = image(x, y - 1, 0);
                                windowR[2] = image(x + 1, y - 1, 0);
                                windowR[3] = image(x - 1, y, 0);
                                windowR[4] = image(x, y, 0);
                                windowR[5] = image(x + 1, y, 0);
                                windowR[6] = image(x - 1, y + 1, 0);
                                windowR[7] = image(x, y + 1, 0);
                                windowR[8] = image(x + 1, y + 1, 0);

                                windowG[0] = image(x - 1 ,y - 1, 1);
                                windowG[1] = image(x, y - 1, 1);
                                windowG[2] = image(x + 1, y - 1, 1);
                                windowG[3] = image(x - 1, y, 1);
                                windowG[4] = image(x, y, 1);
                                windowG[5] = image(x + 1, y, 1);
                                windowG[6] = image(x - 1, y + 1, 1);
                                windowG[7] = image(x, y + 1, 1);
                                windowG[8] = image(x + 1, y + 1, 1);

                                windowB[0] = image(x - 1 ,y - 1, 2);
                                windowB[1] = image(x, y - 1, 2);
                                windowB[2] = image(x + 1, y - 1, 2);
                                windowB[3] = image(x - 1, y, 2);
                                windowB[4] = image(x, y, 2);
                                windowB[5] = image(x + 1, y, 2);
                                windowB[6] = image(x - 1, y + 1, 2);
                                windowB[7] = image(x, y + 1, 2);
                                windowB[8] = image(x + 1, y + 1, 2);

                                insertionSort(windowR);
                                insertionSort(windowG);
                                insertionSort(windowB);

                                maximum (x,y,0) = windowR[8];
                                maximum (x,y,1) = windowG[8];
                                maximum (x,y,2) = windowB[8];
                            }
                        }
                       maximum.save_bmp(output);
                       break;
            }

        case 11:
        {
            CImg<unsigned char> median(image.width(),image.height(),1,3,0); //median
                int windowR[9];
                int windowG[9];
                int windowB[9];

                for(int x = 1; x < image.width() - 1; x++)
                {
                    for(int y = 1; y < image.height() - 1; y++)
                    {
                        windowR[0] = image(x - 1 ,y - 1, 0);
                        windowR[1] = image(x, y - 1, 0);
                        windowR[2] = image(x + 1, y - 1, 0);
                        windowR[3] = image(x - 1, y, 0);
                        windowR[4] = image(x, y, 0);
                        windowR[5] = image(x + 1, y, 0);
                        windowR[6] = image(x - 1, y + 1, 0);
                        windowR[7] = image(x, y + 1, 0);
                        windowR[8] = image(x + 1, y + 1, 0);

                        windowG[0] = image(x - 1 ,y - 1, 1);
                        windowG[1] = image(x, y - 1, 1);
                        windowG[2] = image(x + 1, y - 1, 1);
                        windowG[3] = image(x - 1, y, 1);
                        windowG[4] = image(x, y, 1);
                        windowG[5] = image(x + 1, y, 1);
                        windowG[6] = image(x - 1, y + 1, 1);
                        windowG[7] = image(x, y + 1, 1);
                        windowG[8] = image(x + 1, y + 1, 1);

                        windowB[0] = image(x - 1 ,y - 1, 2);
                        windowB[1] = image(x, y - 1, 2);
                        windowB[2] = image(x + 1, y - 1, 2);
                        windowB[3] = image(x - 1, y, 2);
                        windowB[4] = image(x, y, 2);
                        windowB[5] = image(x + 1, y, 2);
                        windowB[6] = image(x - 1, y + 1, 2);
                        windowB[7] = image(x, y + 1, 2);
                        windowB[8] = image(x + 1, y + 1, 2);

                        insertionSort(windowR);
                        insertionSort(windowG);
                        insertionSort(windowB);

                        median(x,y,0) = windowR[4];
                        median(x,y,1) = windowG[4];
                        median(x,y,2) = windowB[4];
                    }
                }
               median.save_bmp(output);
               break;
        }

        case 12: //mean square error
            {
            CImg<unsigned char> image1(input);
            CImg<unsigned char> image2(output);
            float sum_sq = 0;
            float mse;

               int x, y;

              for (x = 0; x < image1.width()-1; ++x)
               {
                   for ( y = 0; y < image1.height()-1; ++y)
                   {

                        float p1 = image1(x, y);

                        float p2 = image2(x, y);

                        float err = p2 - p1;
                        sum_sq += (err * err);
                   }
               }
               mse =  sum_sq / ( (x+1) * (y+1) );
               std::cout<<mse;
               break;
            }

        case 13: //Peak mean square error
        {
            CImg<unsigned char> image1(input);
            CImg<unsigned char> image2(output);
                float sum_sq1 = 0;
                float sum = 0;
                float mse, err;

            int x, y;
            float r1;
              for (x = 0; x < image1.width()-1; ++x)
               {
                   for ( y = 0; y < image1.height()-1; ++y)
                   {
                        float p1 = image1(x, y) ;

                        float p2 = image2(x, y);

                        err = p2 - p1;
                        sum_sq1 += (err * err);

                        if ( r1 < p1 )
                            {
                                r1=p1;
                            }
                                sum = r1 * r1;
                   }
               }
               mse =  sum_sq1 / ( (x+1) * (y+1) * sum);

               std::cout<<mse;
               break;
        }

        case 14: //Signal to noise ratio
            {
            CImg<unsigned char> image1(input);
            CImg<unsigned char> image2(output);

            float sum_sq = 0;
            float sum_sq1 = 0;
            float mse;


              for (int x = 0; x < image1.width()-1; ++x)
               {
                   for ( int y = 0; y < image1.height()-1; ++y)
                   {
                        float p1 = image1(x, y) ;

                        float p2 = image2(x, y);

                        float err = p2 - p1;
                        sum_sq += (err * err);
                   }
               }

               for (int x = 0; x < image1.width()-1; ++x)
               {
                   for (int y = 0; y < image1.height()-1; ++y)
                   {
                       float p1 = image1(x, y) ;

                        sum_sq1 += (p1 * p1);
                   }
               }
               mse =  10*log10(sum_sq1/sum_sq);
               std::cout<<mse;
               break;
            }

        case 15: //PEAK SIGNAL TO NOISE RATIO
            {
            CImg<unsigned char> image1(input);
            CImg<unsigned char> image2(output);

            float sum_sq = 0;
            float sum_sq1 = 0;
            float mse, sum, r1;


              for (int x = 0; x < image1.width()-1; ++x)
               {
                   for ( int y = 0; y < image1.height()-1; ++y)
                   {
                        float p1 = image1(x, y) ;

                        float p2 = image2(x, y);

                        float err = p2 - p1;
                        sum_sq += (err * err);

                        if ( r1 < p1 )
                        {
                            r1 = p1;
                        }
                        sum = r1 * r1;
                   }
               }


               mse =  10*log10(sum/sum_sq);
               std::cout<<mse;
               break;
            }

        case 16: //maximum difference
            {
            CImg<unsigned char> image1(input);
            CImg<unsigned char> image2(output);

            float sum_sq = 0;
            float mse, sum1, sum2;
            float err1;
               int x, y;

              for (x = 0; x < image1.width()-1; ++x)
               {
                   for ( y = 0; y < image1.height()-1; ++y)
                   {

                        float p1 = image1(x, y);

                        float p2 = image2(x, y);

                        float err = p2 - p1;


                        if ( err1 < err )
                        {
                            err1 = err;
                        }
                   }
               }
               if( err1 < 0)
               std::cout<<-err1;
               else std::cout<<err1;
               break;
            }
    }
    return 0;
}
