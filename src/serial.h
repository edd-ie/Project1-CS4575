#ifndef SERIAL_H
#define SERIAL_H

void serial_grayscale(unsigned char *const img, unsigned char *const gray_img, const int height, const int width)
{
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

#endif // SERIAL_H