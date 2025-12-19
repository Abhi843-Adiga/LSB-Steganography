#include<stdio.h>
#include "type.h"
#include "dec.h"

status read_and_validate_decode_args(char *argv[],dec *d)
{
    if(strstr(argv[1],".bmp")!=NULL)
    d->steg_img_fname=argv[2];
    else
    {
        printf("Invalid file extension\n");
        return e_fail;
    }

    if(strstr(argv[2],".txt")!=NULL)
    d->out_txt_fname=argv[2];
    else
    d->out_txt_fname="output.txt";

    return e_suc;
}

status open_files(dec *d)
{
    if(d->steg_img_fptr=fopen(d->steg_img_fname,"rb")==NULL)
    return e_fail;
    
    if(d->out_txt_fptr=fopen(d->out_txt_fname,"wb")==NULL)
    return e_fail;
    
    return e_suc;
}

status skip_bmp_header(dec *d)
{
    fseek(d->steg_img_fptr,14,SEEK_SET);
    uint i;
    fread(&i,sizeof(int),1,d->steg_img_fptr);
    d->header_size=i+14;
    fseek(d->steg_img_fptr,d->header_size,SEEK_SET);
}

status do_decoding(dec *d)
{
    if(open_files(d)==e_suc)
    {
        printf("Files opened successfully\n");
        if(skip_bmp_header(d)==e_suc)
        {
            printf("Skipped bmp header successfully\n");
        }
        else
        {
            printf(" Failed to Skip bmp header\n");
            return e_fail;
        }
    }
    else
    {
        printf("Files open unsuccessfull\n");
        return e_fail;
    }
}