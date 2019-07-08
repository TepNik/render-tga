#ifndef __model_h__
#define __model_h__

#include "vertex.h"
#include <vector>

class Model
{
private:
    std::vector<ver3f> vert_;
    std::vector<std::vector<int>> faces_;
public:
    Model(const char *modelname);
    ~Model();
    int n_vert() const;
    int n_faces() const;
    ver3f vert(int ind) const;
    std::vector<int> face(int ind) const;
};

#endif