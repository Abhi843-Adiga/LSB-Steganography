#ifndef ENC_H
#define ENC_H
#include "type.h"
#define M_S "#*"
typedef struct Encoding_INFOs
{
    char *src_img_fname;
    FILE *src_img_fptr;
    uint src_img_size;
    uint header_size;
    char str[8];
    
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

status encode_magic_string(enco *en,char *m_s);

status encode_data_to_image(enco *en,char *m_s,int data);

status encode_byte_to_lsb(char sym,char *str);

#endif