#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

RGBTRIPLE avg (int, int, int, int, int, int, RGBTRIPLE image[][]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            // // Testing overflow
            // BYTE blue = 27;
            // BYTE green = 28;
            // BYTE red = 28;
            BYTE avg = round (((float)blue + green + red) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            // Testing overflow
            // BYTE blue = 220;
            // BYTE green = 210;
            // BYTE red = 200;

            WORD sepiaBlue;
            WORD sepiaGreen;
            WORD sepiaRed;

            sepiaBlue = round (red * 0.272 + green * 0.534 + blue * 0.131);
            sepiaGreen = round (red * 0.349 + green * 0.686 + blue * 0.168);
            sepiaRed = round (red * 0.393 + green * 0.769 + blue * 0.189);

            if (sepiaBlue > 255)  {  sepiaBlue  = 255;  }
            if (sepiaGreen > 255) {  sepiaGreen = 255;  }
            if (sepiaRed > 255)   {  sepiaRed   = 255;  }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE *front = &image[i][0];
        RGBTRIPLE *rear = &image[i][width - 1];
        while (front != rear)
        {
            RGBTRIPLE temp = *front;
            *front = *rear;
            *rear = temp;

            front = front + 1;
            if (front == rear)
            {
                break;
            }
            rear = rear - 1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // check if only one row or only one column
    // TO DO

    // understand this
    RGBTRIPLE(*reference)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Testing data
    /*
    height = 3;
    width = 3;
    image[0][0].rgbtRed = 10;
    image[0][0].rgbtGreen = 20;
    image[0][0].rgbtBlue = 30;
    image[0][1].rgbtRed = 40;
    image[0][1].rgbtGreen = 50;
    image[0][1].rgbtBlue = 60;
    image[0][2].rgbtRed = 70;
    image[0][2].rgbtGreen = 80;
    image[0][2].rgbtBlue = 90;
    image[1][0].rgbtRed = 110;
    image[1][0].rgbtGreen = 130;
    image[1][0].rgbtBlue = 140;
    image[1][1].rgbtRed = 120;
    image[1][1].rgbtGreen = 140;
    image[1][1].rgbtBlue = 150;
    image[1][2].rgbtRed = 130;
    image[1][2].rgbtGreen = 150;
    image[1][2].rgbtBlue = 160;
    image[2][0].rgbtRed = 200;
    image[2][0].rgbtGreen = 210;
    image[2][0].rgbtBlue = 220;
    image[2][1].rgbtRed = 220;
    image[2][1].rgbtGreen = 230;
    image[2][1].rgbtBlue = 240;
    image[2][2].rgbtRed = 240;
    image[2][2].rgbtGreen = 250;
    image[2][2].rgbtBlue = 255;
    */
    // avg (1,2,1);
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE average;
        average.rgbtRed = 0;
        average.rgbtGreen = 0;
        average.rgbtBlue = 0;
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            if (i == 0)
            {
                if (j == 0)
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                else if (j == width - 1)
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                else
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = j - 1; l < j + 2; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                else if (j == width - 1)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                else
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = j - 1; l < j + 2; l++)
                        {
                            average.rgbtRed += image[k][l].rgbtRed;
                            average.rgbtGreen += image[k][l].rgbtGreen;
                            average.rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            else
            {
                count = 0;
                for (int k = i - 1; k < i + 2; k++)
                {
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        average.rgbtRed += image[k][l].rgbtRed;
                        average.rgbtGreen += image[k][l].rgbtGreen;
                        average.rgbtBlue += image[k][l].rgbtBlue;
                        count++;
                    }
                }
            }
            average.rgbtRed = round (average.rgbtRed / count);
            average.rgbtGreen = round (average.rgbtGreen / count);
            average.rgbtBlue = round (average.rgbtBlue / count);

            reference[i][j] = average;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reference[i][j];
        }
    }

    return;
}

// RGBTRIPLE avg(int start_i, int start_j, int end_i, int end_j, int height, int width, RGBTRIPLE image[height][width])
// {
//     RGBTRIPLE average;
//     average.rgbtRed = 0;
//     average.rgbtGreen = 0;
//     average.rgbtBlue = 0;

//     int n = 0;
//     for (int i = start_i; i < end_i; i++)
//     {
//         for (int j = start_j; j < end_j; j++)
//         {
//             average.rgbtRed += image[i][j].rgbtRed;
//             average.rgbtGreen += image[i][j].rgbtGreen;
//             average.rgbtBlue += image[i][j].rgbtBlue;
//             n++;
//         }
//     }
//     average.rgbtRed = round(average.rgbtRed / n);
//     average.rgbtGreen = round(average.rgbtGreen / n);
//     average.rgbtBlue = round(average.rgbtBlue / n);

//     return average;
// }