#ifndef DEC_H
#define DEC_H
#include "type.h"
#include<stdio.h>
typedef struct DECODE_INFORMATION
{
   char *steg_img_fname;
   FILE *steg_img_fptr;
   uint header_size;
   char str[4];

   char *out_txt_fname;
   FILE *out_txt_fptr;
}dec;

status read_and_validate_decode_args(char *argv[],dec *d);

status do_decoding(dec *d);

status open_files(dec *d);

status skip_bmp_header(dec *d);

status decode_magic_string(dec *d,char *str);

status data_to_image(dec *d,char *str);

char byte_to_lsb(dec *d);

status decode_ext_size(dec *d,uint size);

uint decode_size_to_lsb(dec *d,uint size);

status decode_extn_data(dec *d,char *str);

status decode_data_size(dec *d);

status decode_data(dec *d);




#endif