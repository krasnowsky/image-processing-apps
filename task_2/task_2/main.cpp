// gcc main.cpp -lstdc++ -o main

#include <iostream>
#include "CImg.h"
#include <math.h>
#include <chrono>

using namespace cimg_library;
using namespace std::chrono;

double truncate(double number)
{
    if(number < 0.0)
    {
        number = 0.0;
        return number;
    }
    else if (number > 255.0)
    {
        number = 255.0;
        return number;
    }
    else return number;
}

void creationHistogram(int number, char *input, char *output)
{
    CImg<unsigned char> image(input);

    int histogram[256];
    for (int i = 0; i < 256; ++i) histogram[i] = 0;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            histogram[image(x,y,number)]++;
        }
    }

    CImg<unsigned char> histogramImage(4000,3100,1,3,0);

    int counter = 0;
    for (int y = 0; y < 12*255; y+=12)
    {
        for (int x = 0; x < histogram[counter]; x++)
        {
            for (int j = 0; j < 12; j++) histogramImage(x,y+j,number) = 255;
        }
        counter++;
    }

    CImg<unsigned char> fliph(histogramImage.height(),histogramImage.width(),1,3,0);
    for (int x = 0; x < histogramImage.width(); x++)
    {
        for (int y = 0; y < histogramImage.height(); y++)
        {
            int val = histogramImage(x, y, number);
            fliph(y, (histogramImage.width()-1)-x, number) = val;
        }
    }
    fliph.save_bmp(output);
}

void calcHistogram(CImg<unsigned char> &image, int number)
{
    double histogram[256];
    for (int i = 0; i < 256; ++i) histogram[i] = 0;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            histogram[image(x,y,number)]++;
        }
    }

    double raleighValues[256];
    double sum = 0.0;

    for(int i = 0; i < 256; i++)
    {
        sum += histogram[i];
        if( sum == 0 ) raleighValues[i] = 0;
       	else raleighValues[i] = truncate(0.0 + pow((2.0 * pow( 50.0, 2.0 ) * log(1.0/((1.0/(image.height()*image.width())) * sum))), 0.5)); // truncate
    }

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            image(x,y,number) = (int)(255-raleighValues[image(x,y,number)]);

        }
    }
}

void raleigh(char *input, char *output)
{
    CImg<unsigned char> image(input);

    calcHistogram(image, 0);
    calcHistogram(image, 1);
    calcHistogram(image, 2);

    image.save_bmp(output);
}

float flat(char *input)
{
    CImg<unsigned char> image(input);
    float b = 0.0, c = 0.0, bk = 0.0, histogram[256], tab[256];
    float n = image.height() * image.width();

    for (int i = 0; i < 256; ++i) histogram[i] = 0;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            histogram[image(x,y)]++;
        }
    }

    for( int m = 0; m < 256; m++)
    {
        b += histogram[m] * m;
    }
    b = 1/b*n ;

    for ( int m = 0; m < 256; m++)
    {
       c += pow(m - b,4) * histogram[m] - 3;
    }

    return bk = (1/pow(100,4)) * (1/n*c);
}

void lineIdentificationCase(char *input, char *output, int parameter) // 79097 microseconds 17s
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> lines(image.width(),image.height(),1,1,0);
    int a = 3;
    int intensity1 = 0;
    for (int i = 0; i < image.width()-a; i++)
    {
        for (int j = 0; j < image.height()-a; j++)
        {
        int intensity2 = 0;
            for(int p = 0; p<a; p++)
            {
                for(int q = 0; q<a; q++)
                {
                    intensity1 = image(i+p, j+q);
                    switch(parameter)
                    {

                    case 1: //vertical
                        {
                            if((p==(a-1)/2)) intensity2 += (a-1)*intensity1;
                            else intensity2 += (-1)*intensity1;
                            break;
                        }

                    case 2: //horizontal
                        {
                            if((q==(a-1)/2)) intensity2 += (a-1)*intensity1;
                            else intensity2 += (-1)*intensity1;
                            break;
                        }

                     case 3: //oblique +45
                        {
                            if(( p+q==2)) intensity2 += (a-1)*intensity1;
                            else  intensity2 += (-1)*intensity1;
                            break;
                        }

                     case 4: //oblique -45
                        {
                            if((p==q)) intensity2 += (a-1)*intensity1;
                            else intensity2 += (-1)*intensity1;
                            break;
                        }

                    }
                }
            lines(i, j) = truncate(intensity2);
            }

        }
    }
    lines.save_bmp(output);
}

void lineIdentification(char *input, char *output) //74213 mircoseconds // 17 s -> 0,07s
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> lines(image.width(),image.height(),1,1,0);
    int mask[3][3] = {  -1, 2, -1,
                        -1, 2, -1,
                        -1, 2, -1};
    int temp = 0;
    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            temp = 0;
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    temp += image(i-1+x,j-1+y)*mask[y][x];
                }
            }
            lines(i, j) = truncate(temp);
        }
    }
    lines.save_bmp(output);
}

void lineIdentificationVertical(char *input, char *output) //56635 microseconds
{
    CImg<unsigned char> image(input);
    CImg<unsigned char> lines(image.width(),image.height(),1,1,0);
    for (int i = 1; i < image.width()-1; i++)
    {
        for (int j = 1; j < image.height()-1; j++)
        {
            int intensity = 0;
            for(int p = 0; p < 3; p++)
            {
                for(int q = 0; q < 3; q++)
                {
                    if(p==1) intensity += image(i+p, j+q)+image(i+p, j+q);
                    else intensity -= image(i+p, j+q);
                    break;
                }
            }
            lines(i, j) = truncate(intensity);
        }
    }
    lines.save_bmp(output);
}

void kirsh(char *input, char *output)

{
    CImg<unsigned char> image(input);
    CImg<unsigned char> kirshImage(image.width(),image.height(),1,1,0);

    const int arrtemp[8]={0,1,2,7,3,6,5,4};
    int arr[8];
    double Si = 0, Ti = 0;
    double maxValue = 0, newValue = 0;
    int counter = 0;
    int temp = 0;

    for(int y = 1; y < image.height() - 1; y++)
    {
        for(int x = 1; x < image.width() - 1; x++)
        {
            maxValue = 0;
            counter = 0;

            for(int p = y - 1; p <= y + 1; p++)
            {
                for(int q = x - 1; q <= x + 1; q++)
                {
                    if( p == y && q == x ) continue;
                    temp = 0;
                    temp = image(q, p);
                    arr[arrtemp[counter]] = temp;
                    counter++;
                }
            }

            for(int j = 0; j < 8; j++)
            {
                Si = 0;
                Ti = 0;
                newValue = 0;

                for(int i = 0; i < 3; i++)
                {
                    if(i + j <=7)
                    {
                        Si = Si + arr[i+j];
                    }

                    else Si = Si + arr[i - 8 + j];
                }

                for(int i = 3; i < 8; i++)
                {
                    if(i + j <=7)
                    {
                        Ti = Ti + arr[i+j];
                    }

                    else Ti = Ti + arr[i - 8 + j];
                }

                newValue = 5 * Si - 3 * Ti;
                if(newValue > maxValue)
                maxValue = newValue;
                }

                if(maxValue < 1)
                maxValue = 1;
                maxValue = truncate(maxValue);
                kirshImage(x, y) = maxValue;
            }
    }
         kirshImage.save_bmp(output);
}

void help()
{
    std::cout << "\n---------HELP CENTER----------" << std::endl;
    std::cout << "Possible commands to use:" << std::endl;
    std::cout << "1. --input [path]" << std::endl;
    std::cout << "2. --output [path]" << std::endl;
    std::cout << "3. --function [name] -argument [value]\n" << std::endl;
    std::cout << "Possible functions to use:" << std::endl;
    std::cout << "1. Histogram [--histogram] " << std::endl;
    std::cout << "2. Raleigh final probability density function [--hraleigh] " << std::endl;
    std::cout << "3. Flattening coefficient [--casyco] " << std::endl;
    std::cout << "4. Line identification [--slineid] " << std::endl;
    std::cout << "5. Kirsh operator [--okirsf] " << std::endl;

}

int main(int argc, char *argv[])
{
    char const *F1 = "--help";
    char const *F2 = "--input";
    char const *F3 = "--output";

    char *input;
    char *output;

    char const *H1 = "--histogram";
    char const *H3 = "--hraleigh";
    char const *C4 = "--casyco";
    char const *S6 = "--slineid";
    char const *S7 = "--slineidopt";
    char const *O4 = "--okirsf";

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

        if      (strcmp(argv[i], H1) == 0) choice = 1;
        else if (strcmp(argv[i], H3) == 0) choice = 2;
        else if (strcmp(argv[i], C4) == 0) choice = 3;

        else if (strcmp(argv[i], S6) == 0) choice = 4;
        else if (strcmp(argv[i], O4) == 0) choice = 5;
        else if (strcmp(argv[i], S7) == 0) choice = 6;

        else if (strcmp(argv[i], A) == 0) parameter = atoi(argv[i+1]);
    }

    switch(choice)
    {
        case 1:
            {
                creationHistogram(parameter, input, output);
                break;
            }
        case 2:
            {
                raleigh(input, output);
                break;
            }
        case 3:
            {
                std::cout << flat(input) << std::endl;
                break;
            }
        case 4:
            {
                auto start = high_resolution_clock::now();
                lineIdentification(input, output);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                std::cout << duration.count() << " microseconds" << std::endl;
                break;
            }
        case 5:
            {
                kirsh(input, output);
                break;
            }
        case 6:
            {
                auto start = high_resolution_clock::now();
                lineIdentificationVertical(input, output);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                std::cout << duration.count() << " microseconds" << std::endl;
                break;
            }
    }

    return 0;
}
