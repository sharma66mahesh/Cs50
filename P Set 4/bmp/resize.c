/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int factor = atoi(argv[1]);
    if(factor <= 0 || factor > 100)
    {
        printf("Error: 0 < factor <= 100\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    //create a buffer for temporary storage of all pixels of a scanline
    RGBTRIPLE buffer[bi.biWidth];
    
    //modify bi for resizing
    bi.biWidth = factor * bi.biWidth;
    bi.biHeight = factor * bi.biHeight;
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines
    int padding =  (4 - ((bi.biWidth / factor) * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //modify bi and bf headers 
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) +   padding2) * abs(bi.biHeight);  //size of all the pixels
    bf.bfSize = 54 + bi.biSizeImage;    //size of file as a whole including headers as well
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight / factor); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth / factor; j++)
        {
            // read RGB triple of a scanline into buffer
            fread(&buffer[j], sizeof(RGBTRIPLE), 1, inptr);
            //at the end of the loop with 'j' as counter all pixels of a scanline would be written with multiplication with factor
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);


        //redraw the scanline factor times --- for scaling in height
        for(int l = 0; l < factor; l++){    
            for(int j = 0; j < bi.biWidth / factor; j++)
            {
                for(int k = 0; k < factor; k++)
                {
                    fwrite(&buffer[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
                // then add it back (to demonstrate how)
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}