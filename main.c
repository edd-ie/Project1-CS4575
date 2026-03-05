#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./src/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./src/stb_image_write.h"

#include "./src/serial.h"

void serial_grayscale(unsigned char *const img, unsigned char *const gray_img, const int height, const int width);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3)
    {
        if (rank == 0)
            printf("Usage: mpirun -np {processors} ./main {mode} {threads}\n");
        MPI_Finalize();
        return 1;
    }

    const int mode = atoi(argv[1]);
    const int threads = atoi(argv[2]);

    int width, height, channels;
    unsigned char *img = stbi_load("./resource/parrot.png", &width, &height, &channels, 4);

    if (img == NULL)
    {
        printf("Error in loading the image\n");
        return 1;
    }

    size_t img_size = (size_t)width * height * 4;

    size_t gray_size = (size_t)width * height;
    unsigned char *gray_img = malloc(gray_size);

    if (gray_img == NULL)
    {
        stbi_image_free(img);
        return 1;
    }

    switch (mode)
    {
    case 0:
        serial_grayscale(img, gray_img, height, width);
        stbi_write_png("./resource/gray_serial.png", width, height, 1, gray_img, width);
        break;

    default:
        break;
    }

    stbi_image_free(img);
    stbi_image_free(gray_img);
    MPI_Finalize();
    return 0;
}