#ifndef OPENMP_H
#define OPENMP_H

#include <omp.h>

void omp_grayscale(unsigned char *const img, unsigned char *const gray_img, const int height, const int width)
{
    /*
     * default(none) - ensure no unused variable are copied during execution
     * shared(img, gray_img, height, width) - specifing data to be duplicated to each thread'
     * schedule(dynamic)
     * collapse(n) - loops collapsed into one large iteration space and divided according to the
     *  schedule at image is accessed a 1D array
     */
#pragma omp parallel for default(none) shared(img, gray_img, height, width) collapse(2)
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Find the starting index of the current pixel in the RGBA array
            int pixel_idx = (y * width + x) * 4;

            unsigned char r = img[pixel_idx];     // Red
            unsigned char g = img[pixel_idx + 1]; // Green
            unsigned char b = img[pixel_idx + 2]; // Blue

            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);

            // Store in the new 1-channel array
            gray_img[y * width + x] = gray;
        }
    }
}

void omp_gaussian_blur(unsigned char *const in, unsigned char *out, int w, int h)
{
}

void omp_edge_detect(unsigned char *const in, unsigned char *out, const int width, const int height)
{
}

#endif // OPENMP_H