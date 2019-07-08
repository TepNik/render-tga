#ifndef __model_cpp__
#define __model_cpp__

#include "model.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Model::Model(const char *filename) : vert_(), faces_()
{
    std::ifstream fin;
    fin.open(filename);
    if (!fin)
        return;
    std::string line;
    while(!fin.eof())
    {
        std::getline(fin, line);
        std::istringstream ss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            ss >> trash;
            ver3f ver;
            for (int i = 0; i < 3; ++i)
                ss >> ver.raw[i];
            vert_.push_back(ver);
        }
        else if (!line.compare(0, 2, "f "))
        {
            ss >> trash;
            int ind, itrash;
            std::vector<int> f;
            while(ss >> ind >> trash >> itrash >> trash >> itrash)
            {
                --ind;
                f.push_back(ind);
            }
            faces_.push_back(f);
        }
    }
    std::cout << "v: " << n_vert() << "\nf: " << n_faces() << '\n';
}

Model::~Model() {}

int Model::n_vert() const
{
    return vert_.size();
}

int Model::n_faces() const
{
    return faces_.size();
}

ver3f Model::vert(int ind) const
{
    return vert_[ind];
}

std::vector<int> Model::face(int ind) const
{
    return faces_[ind];
}

#endif