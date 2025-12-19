#ifndef DEC_H
#define DEC_H
#include "type.h"
#include<stdio.h>
typedef struct DECODE_INFORMATION
{
   char *steg_img_fname;
   FILE *steg_img_fptr;
   uint header_size;

   char *out_txt_fname;
   FILE *out_txt_fptr;
}dec;

status read_and_validate_decode_args(char *argv[],dec *d);

status do_decoding(dec *d);

status open_files(dec *d);

status skip_bmp_header(dec *d);




#endif