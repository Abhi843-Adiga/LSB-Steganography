#ifndef ENC_H
#define ENC_H
#include "type.h"

typedef struct Encoding_INFOs
{
    char *src_img_fname;
    char *sec_txt_fname;
    char *steg_img_fname;
}enco;

optype check_op_type(char *argv[]);

status read_valid_enc_args(char *argv[],enco *enc);

#endif