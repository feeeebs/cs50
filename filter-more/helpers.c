#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //average RGB values
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;

            //set each RGB value to average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            //swap each pixel with its mirror
            //blue
            int tempblue = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = tempblue;

            //green
            int tempgreen = image[i][width - j].rgbtGreen;
            image[i][width - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = tempgreen;

            //red
            int tempred = image[i][width - j].rgbtRed;
            image[i][width - j].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = tempred;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];
    newimage[height][width].rgbtBlue = 0;
    newimage[height][width].rgbtGreen = 0;
    newimage[height][width].rgbtRed = 0;
    int bluesum = 0;
    int greensum = 0;
    int redsum = 0;
    int divisor = 0;

    // loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //check to the left
            if ((j - 1) >= 0)
            {
                //add direct left value to the sum
                bluesum += image[i][j-1].rgbtBlue;
                greensum += image[i][j-1].rgbtGreen;
                redsum += image[i][j-1].rgbtRed;

                //add 1 to the divisor
                divisor++;

                //check left down
                if ((i - 1) >= 0)
                {
                    //add the value to the sum
                    bluesum += image[i-1][j-1].rgbtBlue;
                    greensum += image[i-1][j-1].rgbtGreen;
                    redsum += image[i-1][j-1].rgbtRed;
                    //add 1 to the divisor
                    divisor++;

                }
                //check left up
                if ((i + 1) < height)
                {
                    //add the value to the sum
                    bluesum += image[i+1][j-1].rgbtBlue;
                    greensum += image[i+1][j-1].rgbtGreen;
                    redsum += image[i+1][j-1].rgbtRed;
                    //add 1 to the divisor
                    divisor++;
                }
            }
            //check to the right
            if ((j + 1) < width)
            {
                //add direct right value to the sum
                bluesum += image[i][j+1].rgbtBlue;
                greensum += image[i][j+1].rgbtGreen;
                redsum += image[i][j+1].rgbtRed;
                //add 1 to divisor
                divisor++;

                //check right up
                if ((i + 1) < height)
                {
                    //add right up value to the sum
                    bluesum += image[i+1][j+1].rgbtBlue;
                    greensum += image[i+1][j+1].rgbtGreen;
                    redsum += image[i+1][j+1].rgbtRed;
                    //add 1 to divisor
                    divisor++;
                }
                //check right down
                if ((i - 1) >= 0)
                {
                    //add right down value to the sum
                    bluesum += image[i-1][j+1].rgbtBlue;
                    greensum += image[i-1][j+1].rgbtGreen;
                    redsum += image[i-1][j+1].rgbtRed;
                    //add 1 to divisor
                    divisor++;
                }
            }

            //check directly above
            if ((i + 1) < height)
            {
                //add direct above value to the sum
                bluesum += image[i+1][j].rgbtBlue;
                greensum += image[i+1][j].rgbtGreen;
                redsum += image[i+1][j].rgbtRed;
                //add 1 to divisor
                divisor++;
            }

            //check directly below
            if ((i - 1) >= 0)
            {
                bluesum += image[i-1][j].rgbtBlue;
                greensum += image[i-1][j].rgbtGreen;
                redsum += image[i-1][j].rgbtRed;

                divisor++;
            }

            //set new image values to averages
            newimage[i][j].rgbtBlue = bluesum / divisor;
            newimage[i][j].rgbtGreen = greensum / divisor;
            newimage[i][j].rgbtRed = redsum / divisor;

            //reset sums and divisor to zero
            bluesum = 0;
            greensum = 0;
            redsum = 0;
            divisor = 0;
        }
    }
    //set the old image values to the new image values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
