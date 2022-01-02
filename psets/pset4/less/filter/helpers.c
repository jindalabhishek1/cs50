#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int avg (int, int);

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

    avg (1, 2);
    // for (int i = 0; i < height; i++)
    // {
    //     int average = 0;
    //     for (int j = 0; j < width; j++)
    //     {
    //         if (i = 0)
    //         {
    //             if (j = 0)
    //             {

    //             }
    //         }
    //     }
    // }
    return;
}

int avg(int h, int w)
{
    RGBTRIPLE average;
    // printf("%d %d %d\n", average.rgbtRed, average.rgbtGreen, average.rgbtBlue);

    // for (int i = 0; i < h; i++)
    // {
    //     for (int j = 0; j < w; j++)
    //     {
    //         average.rgbtRed
    //     }
    // }
    return 1;
}