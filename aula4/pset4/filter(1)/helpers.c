#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE byte;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            byte = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j].rgbtBlue = byte;
            image[i][j].rgbtGreen = byte;
            image[i][j].rgbtRed = byte;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width-(j+1)];
            image[i][width-(j+1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tmp = 1;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            if (i != 0)
            {
                blue += image[i-1][j].rgbtBlue;
                green += image[i-1][j].rgbtGreen;
                red += image[i-1][j].rgbtRed;
                tmp++;
                if (j != 0)
                {
                    blue += image[i-1][j-1].rgbtBlue;
                    green += image[i-1][j-1].rgbtGreen;
                    red += image[i-1][j-1].rgbtRed;
                    tmp++;
                }
                if (j != width - 1)
                {
                    blue += image[i-1][j+1].rgbtBlue;
                    green += image[i-1][j+1].rgbtGreen;
                    red += image[i-1][j+1].rgbtRed;
                    tmp++;
                }
            }
            if (i != height - 1)
            {
                blue += image[i+1][j].rgbtBlue;
                green += image[i+1][j].rgbtGreen;
                red += image[i+1][j].rgbtRed;
                tmp++;
                if (j != 0)
                {
                    blue += image[i+1][j-1].rgbtBlue;
                    green += image[i+1][j-1].rgbtGreen;
                    red += image[i+1][j-1].rgbtRed;
                    tmp++;
                }
                if (j != width - 1)
                {
                    blue += image[i+1][j+1].rgbtBlue;
                    green += image[i+1][j+1].rgbtGreen;
                    red += image[i+1][j+1].rgbtRed;
                    tmp++;
                }
            }
            if (j != 0)
            {
                blue += image[i][j-1].rgbtBlue;
                green += image[i][j-1].rgbtGreen;
                red += image[i][j-1].rgbtRed;
                tmp++;
            }
            if (j != width - 1)
            {
                blue += image[i][j+1].rgbtBlue;
                green += image[i][j+1].rgbtGreen;
                red += image[i][j+1].rgbtRed;
                tmp++;
            }
            image_tmp[i][j].rgbtBlue = round(blue / (float) tmp);
            image_tmp[i][j].rgbtGreen = round(green / (float) tmp);
            image_tmp[i][j].rgbtRed = round(red / (float) tmp);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_blue, gx_green, gx_red, gy_blue, gy_green, gy_red;
            gx_blue = gx_green = gx_red = gy_blue = gy_green = gy_red = 0;
            if (j != 0)
            {
                // Gx
                gx_blue += image[i][j-1].rgbtBlue * -2;
                gx_green += image[i][j-1].rgbtGreen * -2;
                gx_red += image[i][j-1].rgbtRed * -2;
                if (i != 0)
                {
                    // Gx
                    gx_blue += image[i-1][j-1].rgbtBlue * -1;
                    gx_green += image[i-1][j-1].rgbtGreen * -1;
                    gx_red += image[i-1][j-1].rgbtRed * -1;

                    // Gy
                    gy_blue += image[i-1][j-1].rgbtBlue * 1;
                    gy_green += image[i-1][j-1].rgbtGreen * 1;
                    gy_red += image[i-1][j-1].rgbtRed * 1;
                }
                if (i != height - 1)
                {
                    // Gx
                    gx_blue += image[i+1][j-1].rgbtBlue * -1;
                    gx_green += image[i+1][j-1].rgbtGreen * -1;
                    gx_red += image[i+1][j-1].rgbtRed * -1;

                    // Gy
                    gy_blue += image[i+1][j-1].rgbtBlue * -1;
                    gy_green += image[i+1][j-1].rgbtGreen * -1;
                    gy_red += image[i+1][j-1].rgbtRed * -1;
                }
            }
            if (j != width - 1)
            {
                // Gx
                gx_blue += image[i][j+1].rgbtBlue * 2;
                gx_green += image[i][j+1].rgbtGreen * 2;
                gx_red += image[i][j+1].rgbtRed * 2;
                if (i != 0)
                {
                    // Gx
                    gx_blue += image[i-1][j+1].rgbtBlue * 1;
                    gx_green += image[i-1][j+1].rgbtGreen * 1;
                    gx_red += image[i-1][j+1].rgbtRed * 1;

                    // Gy
                    gy_blue += image[i-1][j+1].rgbtBlue * 1;
                    gy_green += image[i-1][j+1].rgbtGreen * 1;
                    gy_red += image[i-1][j+1].rgbtRed * 1;
                }
                if (i != height - 1)
                {
                    // Gx
                    gx_blue += image[i+1][j+1].rgbtBlue * 1;
                    gx_green += image[i+1][j+1].rgbtGreen * 1;
                    gx_red += image[i+1][j+1].rgbtRed * 1;

                    // Gy
                    gy_blue += image[i+1][j+1].rgbtBlue * -1;
                    gy_green += image[i+1][j+1].rgbtGreen * -1;
                    gy_red += image[i+1][j+1].rgbtRed * -1;
                }
            }

            if (i != 0)
            {
                // Gy
                gy_blue += image[i-1][j].rgbtBlue * 2;
                gy_green += image[i-1][j].rgbtGreen * 2;
                gy_red += image[i-1][j].rgbtRed * 2;
            }
            if (i != height - 1)
            {
                // Gy
                gy_blue += image[i+1][j].rgbtBlue * -2;
                gy_green += image[i+1][j].rgbtGreen * -2;
                gy_red += image[i+1][j].rgbtRed * -2;
            }


            int blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            int green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));


            if (blue > 0xFF)
            {
                tmp[i][j].rgbtBlue = 0xFF;
            }
            else
            {
                tmp[i][j].rgbtBlue = blue;
            }
            if (green > 0xFF)
            {
                tmp[i][j].rgbtGreen = 0xFF;
            }
            else
            {
                tmp[i][j].rgbtGreen = green;
            }
            if (red > 0xFF)
            {
                tmp[i][j].rgbtRed = 0xFF;
            }
            else
            {
                tmp[i][j].rgbtRed = red;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
