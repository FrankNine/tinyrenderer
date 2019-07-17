#include <cmath>
#include <iostream>
#include <algorithm>

#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void Line(TGAImage &, int, int, int, int);

int main(int argc, char **argv)
{
        (void) argc;
        (void) argv;

        int width = 400;
        int height = 400;

        Model* model = new Model("obj/african_head/african_head.obj");

        TGAImage image(width, height, TGAImage::RGB);

        for (int i = 0; i < model->nfaces(); i++)
        {
                std::cout << i << "/" << model->nfaces() << std::endl;
                std::vector<int> face = model->face(i);
                for (int j = 0; j < 3; j++)
                {
                        Vec3f v0 = model->vert(face[j]);
                        Vec3f v1 = model->vert(face[(j + 1) % 3]);

                        int x0 = (v0.x + 1.) * width / 2.;
                        int y0 = (v0.y + 1.) * height / 2.;
                        int x1 = (v1.x + 1.) * width / 2.;
                        int y1 = (v1.y + 1.) * height / 2.;
                        Line(image, x0, y0, x1, y1);
                }
        }

        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        return 0;
}

void Line(TGAImage &image, int x1, int y1, int x2, int y2)
{
        int xRange = abs(x2 - x1);
        int yRange = abs(y2 - y1);

        if(xRange == 0 && yRange == 0)
        {
                image.set(x1, y1, red);
                return;
        }

        if (yRange < xRange)
        {
                if(x2 < x1)
                {
                        std::swap(x1, x2);
                        std::swap(y1, y2);
                }

                float dy = (float)(y2 - y1) / (x2 - x1);
                float errorY = 0;

                float y = y1;
                for (int x = x1; x <= x2; x += 1, errorY += dy)
                {
                        if (0.5 < errorY)
                        {
                                y += 1;
                                errorY -= 1;
                        }
                        else if(errorY < -0.5)
                        {
                                y -= 1;
                                errorY += 1;
                        }
                        image.set(x, y, red);
                }
        }
        else
        {
                if(y2 < y1)
                {
                        std::swap(x1, x2);
                        std::swap(y1, y2);
                }

                float dx = (float)(x2 - x1) / (y2 - y1);
                float errorX = 0;

                float x = x1;
                for(int y = y1; y <= y2; y += 1, errorX += dx)
                {
                        if(0.5 < errorX)
                        {
                                x += 1;
                                errorX -= 1;
                        }
                        else if(errorX < -0.5)
                        {
                                x -= 1;
                                errorX += 1;
                        }
                        image.set(x, y, red);
                }
        }
}