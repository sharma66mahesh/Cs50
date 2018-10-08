/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<stdio.h>
#include<stdint.h>
#include<cs50.h>

#define BLOCK 512

//these 4 bytes demark the start of jpeg    0xff 0xd8 0xff 0xe1    OR     0xff 0xd8 0xff 0xe0
int main(int argc, char* argv[])
{
    uint8_t inBuffer[BLOCK];    //512 bytes of storage for a sector(block)
    //uint8_t outBuffer[BLOCK]; //out 512 bytes into outFile
    int fileNum = 0;
    char fileName[] = "000.jpg"; 
    
    // open file for reading foresics info
    FILE *file = fopen("card.raw", "r");
    
    //check if read correctly
    if(file == NULL)
    {
        printf("Error reading file \'card.raw\'\n");
        return 1;
    }
    
    while(!feof(file))
    {
        if(fread(inBuffer, BLOCK, 1, file) == 1)
        {
            //check first four bytes for jpeg
            if(inBuffer[0] == 0xff && inBuffer[1] == 0xd8 && inBuffer[2] == 0xff && (inBuffer[3] == 0xe1 || inBuffer[3] == 0xe0))
            {
                //open jpeg file for writing
                FILE *jpeg = fopen(fileName, "a");
                do
                {
                    //write a block
                    fwrite(inBuffer, BLOCK, 1, jpeg);
                    
                    //read a block
                    fread(inBuffer, BLOCK, 1, file);
                }while(!(inBuffer[0] == 0xff && inBuffer[1] == 0xd8 && inBuffer[2] == 0xff && (inBuffer[3] == 0xe1 ||
                        inBuffer[3] == 0xe0)) && !feof(file)); //check if eof or reached or another contiguous jpeg file is encountered
                
                //seek the file pointer back by BLOCK since we've read extra block for checking
                fseek(file, -BLOCK, SEEK_CUR);
                
                //close jpeg
                fclose(jpeg);
                
                //get ready with name for another jpeg
                sprintf(fileName, "%03d.jpg", ++fileNum);   //fixed size of 3 digits, if not fill leading space with zeroes
            }
        }
    }
    
    //close card.raw
    fclose(file);
    return 0;
}
