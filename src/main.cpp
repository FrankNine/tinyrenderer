#include <cmath>
#include <iostream>
#include <algorithm>

#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void Line(TGAImage &, Vec2i, Vec2i);

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
                std::vector<int> face = model->face(i);
                for (int j = 0; j < 3; j++)
                {
                        Vec3f v0 = model->vert(face[j]);
                        Vec3f v1 = model->vert(face[(j + 1) % 3]);

                        int x0 = (v0.x + 1.) * width / 2.;
                        int y0 = (v0.y + 1.) * height / 2.;
                        int x1 = (v1.x + 1.) * width / 2.;
                        int y1 = (v1.y + 1.) * height / 2.;
                        Line(image, Vec2i(x0,y0), Vec2i(x1, y1));
                }
        }

        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
        image.write_tga_file("output.tga");
        return 0;
}


void Line(TGAImage &image, Vec2i v1, Vec2i v2)
{
        Vec2i delta = v2 - v1;

        if(delta.x == 0 && delta.y == 0)
        {
                image.set(v1.x, v1.y, red);
                return;
        }

        if (delta.y < delta.x)
        {
                if(v2.x < v1.x)
                {
                        std::swap(v1, v2);
                }

                float dy = (float)(v2.y - v1.y) / (v2.x - v1.x);
                float errorY = 0;

                float y = v1.y;
                for (int x = v1.x; x <= v2.x; x += 1, errorY += dy)
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
                if(v2.y < v1.y)
                {
                        std::swap(v1, v2);
                }

                float dx = (float)(v2.x - v1.x) / (v2.y - v1.y);
                float errorX = 0;

                float x = v1.x;
                for(int y = v1.y; y <= v2.y; y += 1, errorX += dx)
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