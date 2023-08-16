#pragma once
#include "Macros.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


//library generates 0-255 grayscale values stored in public "pixels"
//user accesses this and renders in main()

class PerlinNoise{
    public:
        PerlinNoise(int kernelx, int kernely, int width, int height);
        void generatePerlin();
        void generateCubes();
        std::vector<std::vector<int>> pixels; //grayscale pixel values 0-255
        std::vector<glm::vec3> cubes;

    private:
        std::vector<double> makeRandom();
        double dotProduct(int a, int b, int i, int j);
        double linearInterpolation(double y1, double y2, double mu); //leads to blocky artifacts
        double cosineInterpolation(double y1, double y2, double mu);
        double map(double value);
        double smoothstep(double value);

        int width;
        int height;
        int kernelx;
        int kernely;
        std::vector<std::vector<std::vector<double>>> grid;
        std::vector<std::vector<double>> randomSet;
};