#include<stdio.h>
#include "type.h"
#include "enc.h"
#include<string.h>

status read_valid_enc_args(char *argv[],enco *enc)
{
    if(strstr(argv[2],".bmp")!=NULL)
    {
       enc->src_img_fname=argv[2];
    }
    else
    {
        printf("Invalid file extension !\n");
        return e_fail;
    }
    
    if(strstr(argv[3],".txt")!=NULL)
    {
        enc->sec_txt_fname=argv[3];
    }
    else
    {
        printf("Invalid file extension !\n");
        return e_fail;
    }

    if(argv[4]!=NULL)
    {
        enc->steg_img_fname=argv[4];
    }
    else
    {
        enc->steg_img_fname="default.bmp";
    }
    return e_suc;
}