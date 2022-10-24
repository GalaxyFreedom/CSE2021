#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char mask_image(unsigned char *image_1 ,unsigned char *image_2,unsigned char *image_3, int width_1, int width_2, int width_3
, int height_1, int height_2, int height_3, int channel_1, int channel_2, int channel_3)
{
    int result;
    for (int i = 0; i < height_1; i++)
    {
        for (int j = 0; j < width_1; j++)
        {
            result = 0;
            for(int k = 0; k < channel_1; k++)
            {
                result += abs(image_1[i*width_1*channel_1+j*channel_1+k]-image_2[i*width_2*channel_2+j*channel_2+k]);
            }

            if (result > 140)
            {
                for (int k = 0; k < channel_3; k++){
                    image_3[i*width_3*channel_3+j*channel_3+k]=image_1[i*width_1*channel_1+j*channel_1+k];
                }
            }
        }
    }

}




int main()
{
    // declare variables
    int width_1, height_1, channel_1, width_2, height_2, channel_2, width_3, height_3, channel_3;
    char path_img_1[] = "./images/foreground.png";
    char path_img_2[] = "./images/background.png";
    char path_img_3[] = "./images/weather_forecast_resized.jpg";
    char save_path_3[] = "./images/weather_forecast_resize_new.png";

    // read image data
    unsigned char *image_1 = stbi_load(path_img_1, &width_1, &height_1, &channel_1, 0);
    unsigned char *image_2 = stbi_load(path_img_2, &width_2, &height_2, &channel_2, 0);
    unsigned char *image_3 = stbi_load(path_img_3, &width_3, &height_3, &channel_3, 0);
    if (image_1 == NULL || image_2 == NULL || image_3 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Image_1: Width = %d\nHeight = %d\nChannel = %d\n", width_1, height_1, channel_1);
    printf("Image_2: Width = %d\nHeight = %d\nChannel = %d\n", width_2, height_2, channel_2);
    printf("Image_3: Width = %d\nHeight = %d\nChannel = %d\n", width_3, height_3, channel_3);

    // fill a quarter of the image with black pixels
    mask_image(image_1, image_2, image_3, width_1, width_2, width_3, height_1, height_2, height_3, channel_1, channel_2, channel_3);
    stbi_write_png(save_path_3, width_3, height_3, channel_3, image_3,width_3 * channel_3);
    printf("New image saved to %s\n", save_path_3);
}