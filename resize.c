/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");// Usage: ./copy infile outfile
        return 1;
    }
    // remember filenames
    int n = atoi(argv[1]); // n
    if (n < 0 || n > 100)
    {
        printf("(n) must be a positive integer less than or equal to 100\n");
        return -1;
    }
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile); // stderr ??
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_n;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_n = bf; // bf for image size n
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_n; // bi for image size n
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_n = bi;
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    bi_n.biWidth = bi.biWidth * n;
    bi_n.biHeight = bi.biHeight * n;
    
    // printf("bi.biWidth=%i  bi_n.biWidth=%i\n", bi.biWidth, bi_n.biWidth);
    // printf("bi.biHeight=%i  bi_n.biHeight=%i\n", bi.biHeight, bi_n.biHeight);
    
    // determine padding for scanlines
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new = (4 - (bi_n.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // printf("padding_old=%i  padding_new=%i\n", padding_old, padding_new);
    
    // bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // there are
    // bi.bisizeimage = ((sizeof(RGBTRIPLE) * bi.Width) + padding_old) * abs(bi.biHeight); // there are
    
    // Determine new image sizes
    bi_n.biSizeImage = (sizeof(RGBTRIPLE) * bi_n.biWidth + padding_new) * abs(bi_n.biHeight);
    
    bf_n.bfSize = bi_n.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr); // *n

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr); // *n 
    
    // printf("bi.biHeight=%i\n", bi.biHeight);
    // printf("bi_n.biHeight=%i\n", bi_n.biHeight);
    // printf("bi.biWidth=%i\n", bi.biWidth); 
    // printf("bi_n.biWidth=%i\n", bi_n.biWidth);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < n; j++)
        {
            // Return to the beginning of a scanline
            fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + // => bf.bfOffBits +
                          i * (padding_old + (abs(bi.biWidth) * sizeof(RGBTRIPLE))), SEEK_SET );
         
            // temporary storage
            for(int y = 0; y < bi.biWidth; y++)
            {
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int x = 0; x < n; x++)
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); // * n
            }
        
            // skip over padding, if any
            fseek(inptr, padding_new, SEEK_CUR); // padding_n
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding_new; k++)
                fputc(0x00, outptr);
        
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}