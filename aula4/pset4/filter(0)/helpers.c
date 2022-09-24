#include "helpers.h"
#include <math.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sepia_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_blue, sepia_green, sepia_red;
            sepia_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            sepia_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepia_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            if (sepia_blue > 0xFF)
            {
                sepia_img[i][j].rgbtBlue = 0xFF;
            }
            else
            {
                sepia_img[i][j].rgbtBlue = sepia_blue;
            }
            if (sepia_green > 0xFF)
            {
                sepia_img[i][j].rgbtGreen = 0xFF;
            }
            else
            {
                sepia_img[i][j].rgbtGreen = sepia_green;
            }
            if (sepia_red > 0xFF)
            {
                sepia_img[i][j].rgbtRed = 0xFF;
            }
            else
            {
                sepia_img[i][j].rgbtRed = sepia_red;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = sepia_img[i][j].rgbtBlue;
            image[i][j].rgbtGreen = sepia_img[i][j].rgbtGreen;
            image[i][j].rgbtRed = sepia_img[i][j].rgbtRed;
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
