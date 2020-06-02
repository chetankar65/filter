#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // averages the color intensity and then applies the same value to all the colors to get gray
            rgbGray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.000);

            image[j][i].rgbtBlue = rgbGray;
            image[j][i].rgbtGreen = rgbGray;
            image[j][i].rgbtRed = rgbGray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ///Original Colours
            float originalRed = image[i][j].rgbtRed;
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;

            //All the sepia colours
            float sepiaRed = 0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue;
            float sepiaGreen = 0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue;
            float sepiaBlue = 0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue;

            //Error checking with if conditions
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int) round(sepiaRed);
            }
            ///////////////
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (int) round(sepiaGreen);
            }
            ///////////////
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (int) round(sepiaBlue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temporary[3];
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            temporary[0] = image[j][i].rgbtBlue;
            temporary[1] = image[j][i].rgbtGreen;
            temporary[2] = image[j][i].rgbtRed;

            // swap pixels with the ones on the opposite side of the picture and viceversa
            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            image[j][width - i - 1].rgbtBlue = temporary[0];
            image[j][width - i - 1].rgbtGreen = temporary[1];
            image[j][width - i - 1].rgbtRed = temporary[2];
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        //The continue statement in C programming works somewhat like the break statement. 
                        //Instead of forcing termination, it forces the next iteration of the loop to take place,
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}

