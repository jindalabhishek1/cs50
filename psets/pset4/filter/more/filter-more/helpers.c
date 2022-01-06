#include "helpers.h"
#include <math.h>
#include <stdlib.h>

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
            BYTE avg = round(((float)blue + green + red) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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

    // loop for rows
    for (int i = 0; i < height; i++)
    {
        int count = 0;
        // loop for columns
        for (int j = 0; j < width; j++)
        {
            // floats because we don't want to lose the points
            // setting value to zeros
            float rgbtRed = 0;
            float rgbtGreen = 0;
            float rgbtBlue = 0;

            // checking if in first row
            if (i == 0)
            {
                // first row first column
                if (j == 0)
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            int red = image[k][l].rgbtRed;
                            int green = image[k][l].rgbtGreen;
                            int blue = image[k][l].rgbtBlue;
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                //first row last column
                else if (j == width - 1)
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                // first row elements except first and last
                else
                {
                    count = 0;
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = j - 1; l < j + 2; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            // checking if last row
            else if (i == height - 1)
            {
                // last row first element
                if (j == 0)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                // last row last element
                else if (j == width - 1)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                // last row elements except first and last
                else
                {
                    count = 0;
                    for (int k = i - 1; k < i + 1; k++)
                    {
                        for (int l = j - 1; l < j + 2; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            // rows except first and last
            else
            {
                // rows excepts first and last, first element
                if (j == 0)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                // rows excepts first and last, last element
                else if (j == width - 1)
                {
                    count = 0;
                    for (int k = i - 1; k < i + 2; k++)
                    {
                        for (int l = j - 1; l < j + 1; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
                // rows excepts first and last, elements except first and last
                else
                {
                    count = 0;
                    for (int k = i - 1; k < i + 2; k++)
                    {
                        for (int l = j - 1; l < j + 2; l++)
                        {
                            rgbtRed += image[k][l].rgbtRed;
                            rgbtGreen += image[k][l].rgbtGreen;
                            rgbtBlue += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }

            // rounding off
            rgbtRed = round(rgbtRed / count);
            rgbtGreen = round(rgbtGreen / count);
            rgbtBlue = round(rgbtBlue / count);

            // assigning to the reference matrix of pixels
            reference[i][j].rgbtRed = rgbtRed;
            reference[i][j].rgbtGreen = rgbtGreen;
            reference[i][j].rgbtBlue = rgbtBlue;
        }
    }

    // coping data from reference to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reference[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*reference)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Testing data
    /*
    height = 3;
    width = 3;
    image[0][0].rgbtRed = 0;
    image[0][0].rgbtGreen = 10;
    image[0][0].rgbtBlue = 25;
    image[0][1].rgbtRed = 0;
    image[0][1].rgbtGreen = 10;
    image[0][1].rgbtBlue = 30;
    image[0][2].rgbtRed = 40;
    image[0][2].rgbtGreen = 60;
    image[0][2].rgbtBlue = 80;
    image[1][0].rgbtRed = 20;
    image[1][0].rgbtGreen = 30;
    image[1][0].rgbtBlue = 90;
    image[1][1].rgbtRed = 30;
    image[1][1].rgbtGreen = 40;
    image[1][1].rgbtBlue = 100;
    image[1][2].rgbtRed = 80;
    image[1][2].rgbtGreen = 70;
    image[1][2].rgbtBlue = 90;
    image[2][0].rgbtRed = 20;
    image[2][0].rgbtGreen = 20;
    image[2][0].rgbtBlue = 40;
    image[2][1].rgbtRed = 30;
    image[2][1].rgbtGreen = 10;
    image[2][1].rgbtBlue = 30;
    image[2][2].rgbtRed = 50;
    image[2][2].rgbtGreen = 40;
    image[2][2].rgbtBlue = 10;
    */

    int gx_arr[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_arr[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // loop for rows
    for (int i = 0; i < height; i++)
    {
        // loop for columns
        for (int j = 0; j < width; j++)
        {
            // floats because we don't want to lose the points
            // setting value to zeros
            float rgbtRed = 0;
            float rgbtGreen = 0;
            float rgbtBlue = 0;
            int m = 0, n = 0, termsX = 0, termsY = 0, addX = 0, addY = 0;

            // checking if in first row
            if (i == 0)
            {
                // first row first column
                if (j == 0)
                {
                    m = 0;
                    n = 0;
                    termsX = 2;
                    termsY = 2;
                    addX = 1;
                    addY = 1;
                }
                //first row last column
                else if (j == width - 1)
                {
                    m = 0;
                    n = width - 2;
                    termsX = 2;
                    termsY = 2;
                    addX = 1;
                    addY = 0;
                }
                // first row elements except first and last
                else
                {
                    m = 0;
                    n = j - 1;
                    termsX = 2;
                    termsY = 3;
                    addX = 1;
                    addY = 0;
                }
            }
            // checking if last row
            else if (i == height - 1)
            {
                // last row first element
                if (j == 0)
                {
                    m = height - 2;
                    n = 0;
                    termsX = 2;
                    termsY = 2;
                    addX = 0;
                    addY = 1;
                }
                // last row last element
                else if (j == width - 1)
                {
                    m = height - 2;
                    n = width - 2;
                    termsX = 2;
                    termsY = 2;
                    addX = 0;
                    addY = 0;
                }
                // last row elements except first and last
                else
                {
                    m = height - 2;
                    n = j - 1;
                    termsX = 2;
                    termsY = 3;
                    addX = 0;
                    addY = 0;
                }
            }
            // rows except first and last
            else
            {
                // rows excepts first and last, first element
                if (j == 0)
                {
                    m = i - 1;
                    n = 0;
                    termsX = 3;
                    termsY = 2;
                    addX = 0;
                    addY = 1;
                }
                // rows excepts first and last, last element
                else if (j == width - 1)
                {
                    m = i - 1;
                    n = width - 2;
                    termsX = 3;
                    termsY = 2;
                    addX = 0;
                    addY = 0;
                }
                // rows excepts first and last, elements except first and last
                else
                {
                    m = i - 1;
                    n = j - 1;
                    termsX = 3;
                    termsY = 3;
                    addX = 0;
                    addY = 0;
                }
            }

            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

            // checking the condition how can we make it dynamic
            for (int k = m; k < m + termsX; k++)
            {
                for (int l = n; l < n + termsY; l++)
                {
                    int a, b;
                    a = k - m + addX;
                    b = l - n + addY;
                    gxRed += image[k][l].rgbtRed * gx_arr[a][b];
                    gxGreen += image[k][l].rgbtGreen * gx_arr[a][b];
                    gxBlue += image[k][l].rgbtBlue * gx_arr[a][b];

                    gyRed += image[k][l].rgbtRed * gy_arr[a][b];
                    gyGreen += image[k][l].rgbtGreen * gy_arr[a][b];
                    gyBlue += image[k][l].rgbtBlue * gy_arr[a][b];
                }
            }

            // rounding off
            rgbtRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            rgbtGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            rgbtBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            if (rgbtRed > 255)
            {
                rgbtRed = 255;
            }
            if (rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }
            if (rgbtBlue > 255)
            {
                rgbtBlue = 255;
            }
            // assigning to the reference matrix of pixels
            reference[i][j].rgbtRed = rgbtRed;
            reference[i][j].rgbtGreen = rgbtGreen;
            reference[i][j].rgbtBlue = rgbtBlue;
        }
    }

    // coping data from reference to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reference[i][j];
        }
    }

    free (reference);

    return;
}