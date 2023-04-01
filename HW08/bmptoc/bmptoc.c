// bmptoc.c
// Name: Hardik Sangwan

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

// Your program will only support BMP files that
// have a max size that is equivalent to the size
// of the GBA screen.
#define MAX_BMP_FILE_SIZE (0x36 + 240 * 160 * 4)
char data_arr[MAX_BMP_FILE_SIZE];

//Function prototypes
unsigned int getWidth(char*);
unsigned int getHeight(char*);

int main(int argc, char *argv[]) {
    // The implementation of the program is broken down into steps below.

    // 1. Make sure the user passed in the correct number of arguments
    // Hint: You'll want to see what value argc has.
    if (argc != 2) 
    {
        printf("The number of arguments passed is not correct \n");
        return 0;
    }

    FILE *infile;
    // 2. Open the file. If it doesn't exist, tell the user and then exit
    // Hint: read the man page for fopen by typing `man fopen`
    //       either in your terminal or google

    // We've implemented this part for you. It reads in the bmp file into
    // a buffer (assuming you've open the file properly), then closes the file.
    fread(data_arr, 1, MAX_BMP_FILE_SIZE, infile);
    fclose(infile);

    // 3. Get the width and height of the image. Read the BMP file format
    // to determine what you should do for this one. Then implement the
    // functions at the end of the file.
    unsigned int width = getWidth(data_arr);
    unsigned int height = getHeight(data_arr);

    // We've implemented outputing the header file correctly assuming your
    // getWidth and getHeight work properly. Read this code carefully and
    // read the man pages because you'll have to do something similar
    // for generating the C file.
    FILE *outheader;
    char filename[100];

    strcpy(filename, argv[1]);
    int fname_len = strlen(filename);
    filename[fname_len - 3] = 'h';
    filename[fname_len - 2] = '\0'; // file.bmp -> file.h
    if(!(outheader = fopen(filename, "w"))) {
        printf("Error creating file %s: %s\n", filename, strerror(errno));
    }
    filename[fname_len - 4] = '\0';
    char *ptr = filename;
    while(*ptr) {
        *ptr = toupper(*ptr); // file.h -> FILE
        ++ptr;
    }

    /* File format:
     *
     *  #define FILE_WIDTH 100
     *  #define FILE_HEIGHT 150
     *  const unsigned short file_data[15000];
     */

    fprintf(outheader, "#define %s_WIDTH %d\n", filename, width);
    fprintf(outheader, "#define %s_HEIGHT %d\n", filename, height);

    strcpy(filename, argv[1]);
    filename[fname_len - 4] = '\0';
    fprintf(outheader, "const unsigned short %s_data[%d];\n", filename, width * height);

    fclose(outheader);


    // 4. Now you are responsible for creating a c file with the same basename
    // as the bmp file that was passed in file.bmp -> file.c
    // Hint: Use the code above as a guide for how to
    //       initialize the filename and  open the file.
    FILE *fdata;
    char data_name[strlen(header_name_complete)];
    sprintf(data_name,"%s.c",header_name);
    fdata = fopen(data_name, "w");
    fprintf(fdata, "const unsigned short %s_data[%d] = {\n",header_name, size);
    /* File format:
     *
     *  const unsigned short file_data[15000] = {
     *    0x4521, 0x5B2F, 0x1F69, ...
     *  };
     */

    // 5. You must output the first part of the C file which will look like the
    // line above. Note that instead of 15000 you will have the width * height.
    // Hint: Look at how fprintf is used elsewhere in this code and read the
    //       man page.
    //


    // 6. Iterate over the pixel data convert it to hex and write the output to the C file.
    // Hint: Pay careful attention to the format of the BMP file. It is stored
    // in reverse order.

    // Useful variables:
    // data_arr - array of bytes that contains all the data in the bmp file
    // height/width - self explanatory, just so you're aware they're there
    for(int i = height - 1;i >= 0; i--) 
    {
        for(unsigned int j = 0; j<width; j++) 
        {
            int data = *(unsigned int*)(0x36 + data_arr + 4 * ((width * i) + j));
            int blue = (data >> 3) & 0x1F;
            int green = (data >> 11) & 0x1F;
            int red = (data >> 19) & 0x1F;
            short pixel = red | (green) << 5 | (blue) << 10;
            fprintf(fdata, "0x%04X,\t", pixel);
        }
        fprintf(fdata, "\n");
    }

    // 7. Finally write the closing brace and semicolon to the file and
    // close the file.
    fprintf(fdata, "};\n");
    fclose(fdata);
    // You're done with this part, but don't forget there are other files
    // you need to implement code in.

    return 0;
}

/*
 *
 * Format of a bmp header (data_arr)
 * file offset  |   length   |     field
 * 0x12         |  4 bytes   |  image width
 * 0x16         |  4 bytes   |  image height
 *
 */

// TODO
// complete this function that uses the bmp data_arr to retrieve the width of
// the image
// HINT: this can be done in one line
unsigned int getWidth(char *data_arr) {
    // YOUR CODE HERE
    unsigned int width = *((unsigned int *)(data_arr + 0x12));
    return width;
}

// TODO
// complete this function that uses the bmp data_arr to retrieve the height of
// the image
// HINT: this can be done in one line
unsigned int getHeight(char *data_arr) {
    // YOUR CODE HERE
    unsigned int height = *((unsigned int *)(data_arr + 0x16));
    return height;
}
