#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void Line(TGAImage &, int, int, int, int);

int main(int argc, char **argv)
{
        TGAImage image(100, 100, TGAImage::RGB);

        Line(image, 20, 20, 30, 60);

        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        return 0;
}

void Line(TGAImage &image, int x1, int y1, int x2, int y2)
{
        int dx = x1 < x2 ? 1 : -1;
        float dy = (float)(y2 - y1) / (x2 - x1);

        float y = y1;
        for (int x = x1; x <= x2; x += dx, y += dy)
        {
                image.set(x, y, red);
        }
}