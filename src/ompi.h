#ifndef OMPI_H
#define OMPI_H

void mpi_grayscale(unsigned char *const img, unsigned char *const gray_img, const int height, const int width, const int size, const int rank)
{
    int chunks = width * height;
    int base_part = chunks / size;
    int remainder = chunks % size;

    int *counts = (int *)malloc(size * sizeof(int));
    int *displ = (int *)malloc(size * sizeof(int));
    int *g_counts = (int *)malloc(size * sizeof(int));
    int *g_displ = (int *)malloc(size * sizeof(int));

    int offset = 0;
    int g_offset = 0;
    for (int i = 0; i < size; i++)
    {
        // Ranks get 1 extra pixel
        int current_chunk_size = base_part + (i < remainder ? 1 : 0);
        counts[i] = current_chunk_size * 4; // 4 channels rgba
        displ[i] = offset;
        offset += counts[i];

        // Use g_counts and g_displ in MPI_Gatherv
        g_counts[i] = current_chunk_size;
        g_displ[i] = g_offset;
        g_offset += g_counts[i];
    }

    // Each rank allocates only what it needs based on its specific count
    unsigned char *img_buf = (unsigned char *)malloc(counts[rank]);
    unsigned char *gray_buf = (unsigned char *)malloc(g_counts[rank]);

    MPI_Scatterv(img, counts, displ, MPI_UNSIGNED_CHAR, img_buf, counts[rank], MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < g_counts[rank]; i++)
    { // Local index for 4-channel input
        int in_idx = i * 4;
        gray_buf[i] = (unsigned char)(0.299 * img_buf[in_idx] + 0.587 * img_buf[in_idx + 1] + 0.114 * img_buf[in_idx + 2]);
    }

    MPI_Gatherv(gray_buf, g_counts[rank], MPI_UNSIGNED_CHAR, gray_img, g_counts, g_displ, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    free(counts);
    free(displ);
    free(g_counts);
    free(g_displ);
    free(img_buf);
    free(gray_buf);
}

void mpi_gaussian_blur(unsigned char *const in, unsigned char *out, int w, int h)
{
}

void mpi_edge_detect(unsigned char *const in, unsigned char *out, const int width, const int height)
{
}

#endif // OMPI_H