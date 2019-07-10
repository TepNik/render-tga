#include "tgaimage.h"
#include "model.h"
#include <cmath>
#include <ctime>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);
void line(ver2i t0, ver2i t1, TGAImage &image, const TGAColor &color);
void triangle(ver2i t0, ver2i t1, ver2i t2, TGAImage &image, const TGAColor &color);

int main(int argc, char **argv)
{
    int width = 500;
    int height = 500;
    TGAImage image(width, height, TGAImage::RGB);
    srand(time(NULL));
    Model mod("face.obj");
    ver3f light_dir(0, 0, -0.7);
    light_dir.normalize(0.7);
    for (int i = 0; i < mod.n_faces(); ++i)
    {
        std::vector<int> face = mod.face(i);
        ver2i triangle_coord[3];
        ver3f world_coord[3];
        for (int j = 0; j < 3; ++j)
        {
            ver3f v = mod.vert(face[j]);
            triangle_coord[j] = ver2i((v.x + 1.)*width/2., (v.y + 1.)*height/2.);
            world_coord[j] = v;
        }
        ver3f norm_triangle = (world_coord[2] - world_coord[0]) ^ (world_coord[1] - world_coord[0]);
        norm_triangle.normalize();
        float intensity = norm_triangle*light_dir;
        if (intensity > 1)
            std::cout << "Error!\n";
        if (intensity > 0)
            triangle(triangle_coord[0], triangle_coord[1], triangle_coord[2], image, TGAColor(intensity*255,
                                                                                              intensity*255,
                                                                                              intensity*255, 255));
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    system("TGAViewer.exe output.tga");
    return 0;
}

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
            image.set(y, x, color);
        else
            image.set(x, y, color);

        error += slope_ratio;
        if (error > delta_x)
        {
            y += (y1 > y0 ? 1 : -1);
            error -= delta_x << 2;
        }
    }
}

void line(ver2i t0, ver2i t1, TGAImage &image, const TGAColor &color)
{
    line(t0.x, t0.y, t1.x, t1.y, image, color);
}

void triangle(ver2i t0, ver2i t1, ver2i t2, TGAImage &image, const TGAColor &color)
{
    if (t0.y == t1.y && t0.y == t2.y)
        return;
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);

    int height_0_2 = t2.y - t0.y;
    for (int i = 0; i < height_0_2; ++i)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (i+.0)/height_0_2;
        float beta = (i - (second_half ? t1.y-t0.y : 0) + .0)/segment_height;
        ver2i A = t0 + (t2 - t0)*alpha;
        ver2i B = second_half ? t1 + (t2 - t1)*beta : t0 + (t1 - t0)*beta;
        if (A.x > B.x) std::swap(A, B);
        for(int j = A.x; j <= B.x; ++j)
            image.set(j, t0.y + i, color);
    }
}