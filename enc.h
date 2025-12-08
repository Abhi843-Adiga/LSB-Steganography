#ifndef ENC_H
#define ENC_H
#include "type.h"

typedef struct Encoding_INFOs
{
    char *src_img_fname;
    FILE *src_img_fptr;
    uint src_img_size;
    
    char *sec_txt_fname;
    FILE *sec_txt_fptr;
    long sec_txt_fsize;
    
    char *steg_img_fname;
    FILE *steg_img_fptr;
}enco;

optype check_op_type(char *argv[]);

status read_valid_enc_args(char *argv[],enco *enc);

status do_encoding(enco *en);

status check_open(enco *en);

status check_capacity(enco *en);

uint check_image_size(enco *en);

uint check_file_size(FILE *fp);

status copy_bmp_header(enco *en);

#endif