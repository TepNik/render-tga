#include "tgaimage.h"
#include "model.h"
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color) {
    bool is_transpose = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        is_transpose = true;
    }
    if (x1 < x0)
    {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }

    int delta_x = x1 - x0;
    int delta_y = y1 - y0;

    int slope_ratio = std::abs(delta_y) << 2;
    int error = 0;

    int y = y0;

    for (int x = x0; x <= x1; ++x)
    {
        if (is_transpose)
        {
            /* for (int t = 0; t < width; ++t)
                image.set(y, x - t, white); */
            image.set(y, x, white);
            /* for (int t = 0; t < width; ++t)
                image.set(y, x + t, white); */
        }
        else
        {
            /* for (int t = 0; t < width; ++t)
                image.set(x, y - t, white); */
            image.set(x, y, white);
            /* for (int t = 0; t < width; ++t)
                image.set(x, y + t, white); */
        }

        error += slope_ratio;
        if (error > delta_x)
        {
            y += (y1 > y0 ? 1 : -1);
            error -= delta_x << 2;
        }
    }
}

int main(int argc, char **argv)
{
    int width = 1000;
    int height = 1000;
    TGAImage image(width, height, TGAImage::RGB);
    //image.set(52, 41, red);
    /* for (int i = 0; i < 1'000'000; ++i)
    {
        line(13, 20, 80, 40, image, white);
        line(20, 13, 40, 80, image, red);
        line(80, 40, 13, 20, image, red);
    } */
    Model mod("example.txt");
    for (int i = 0; i < mod.n_faces(); ++i)
    {
        std::vector<int> face = mod.face(i);
        for (int j = 0; j < 3; ++j)
        {
            ver3f v0 = mod.vert(face[j]);
            ver3f v1 = mod.vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.)*width/2;
            int x1 = (v1.x + 1.)*width/2;
            int y0 = (v0.y + 1.)*height/2;
            int y1 = (v1.y + 1.)*height/2;
            line(x0, y0, x1, y1, image, white);
        }
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
