#include <cmath>

#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void Line(TGAImage &, int, int, int, int);

int main(int argc, char **argv)
{
        (void) argc;
        (void) argv;
        
        TGAImage image(100, 100, TGAImage::RGB);

        Line(image, 20, 20, 70, 60);
        Line(image, 20, 20, 70, 50);
        Line(image, 20, 20, 70, 40);
        Line(image, 20, 20, 70, 30);

        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        return 0;
}

void Line(TGAImage &image, int x1, int y1, int x2, int y2)
{
        int xRange = abs(x2 - x1);
        int yRange = abs(y2 - y1);

        if (yRange < xRange)
        {
                int dx = x1 < x2 ? 1 : -1;
                float dy = (float)(y2 - y1) / (x2 - x1);

                float y = y1;
                for (int x = x1; x <= x2; x += dx, y += dy)
                {
                        image.set(x, y, red);
                }
        }
        else
        {
                int dy = y1 < y2 ? 1 : -1;
                float dx = (float)(x2 - x1) / (y2 - y1);

                float x = x1;
                for(int y = y1; y <= y2; y += dy, x += dx)
                {
                        image.set(x, y, red);
                }
        }
}