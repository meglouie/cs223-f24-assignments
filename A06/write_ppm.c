/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE *outfile;
    outfile = fopen(filename, "w");
    if(!outfile){
        printf("Can't open file '%s' \n", filename);
        return;
    }
    fprintf(outfile, "P6\nCreated by Megan\n%d %d \n255\n", w, h);
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            unsigned char pix[3] = {pixels[i*w + j].red, pixels[i*w + j].green, pixels[i*w + j].blue};
            fwrite(pix, sizeof(unsigned char), 3, outfile);
        }
    }
    fclose(outfile);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
