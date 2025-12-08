#include<stdio.h>
#include "type.h"
#include "enc.h"
#include<string.h>

status read_valid_enc_args(char *argv[],enco *enc)
{
    if(strstr(argv[2],".bmp")!=NULL)
    enc->src_img_fname=argv[2];
    else
    {
        printf("Invalid file extension !\n");
        return e_fail;
    }
    
    if(strstr(argv[3],".txt")!=NULL)
    enc->sec_txt_fname=argv[3];
    else
    {
        printf("Invalid file extension !\n");
        return e_fail;
    }

    if(argv[4]!=NULL)
    enc->steg_img_fname=argv[4];
    else
    enc->steg_img_fname="default.bmp";
    
    return e_suc;
}

status check_open(enco *en)
{
    en->src_img_fptr=fopen(en->src_img_fname,"r");
    if(en->src_img_fptr==NULL)
    {
        printf("File unable to open\n");
        return e_fail;
    }

    en->sec_txt_fptr=fopen(en->sec_txt_fname,"r");
    if(en->sec_txt_fptr==NULL)
    {
        printf("File unable to open\n");
        return e_fail;
    }

    en->steg_img_fptr=fopen(en->steg_img_fname,"w");
    if(en->steg_img_fptr==NULL)
    {
        printf("File unable to open\n");
        return e_fail;
    }
    return e_suc;
}

uint check_image_size(enco *en)
{
    uint h,w;
    fseek(en->src_img_fptr,18,SEEK_SET);
    fread(&w,sizeof(int),1,en->src_img_fptr);
    printf("Width of image: %u\n",w);
    fread(&h,sizeof(int),1,en->src_img_fptr);
    printf("Height of image: %u\n",h);
    return h*w*3;
}

uint check_file_size(FILE *fp)
{
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}

status check_capacity(enco *en)
{
    en->src_img_size=check_image_size(en);
    en->sec_txt_fsize=check_file_size(en->sec_txt_fptr);
    if(en->src_img_size > 16+32+32+32+(en->sec_txt_fsize*8))
    return e_suc;
    else
    return e_fail;
}

status copy_bmp_header(enco *en)
{
    fseek(en->src_img_fptr,14,SEEK_SET);
    uint s;
    fread(&s,sizeof(int),1,en->src_img_fptr);
    printf("Info Header Size: %u\n",s);
    char str[s+14];
    rewind(en->src_img_fptr);
    fread(str,s+14,1,en->src_img_fptr);
    fwrite(str,s+14,1,en->steg_img_fptr);
    return e_suc;
}

status do_encoding(enco *en)
{
    if(check_open(en)==e_suc)
    {
        printf("FILE OPENED SUCCESSFULLY\n");
        if(check_capacity(en)==e_suc)
        {
            printf("Capacity checked successfully\n");
            if(copy_bmp_header(en)==e_suc)
            {
                printf("Copied BMP header successfully\n");
            }
            else
            {
                printf("Failed to copy BMP header\n");
                return e_fail;
            }
        }
        else
        {
            printf("Failed to check capacity\n");
            return e_fail;
        }
    }
    else
    {
        printf("Failed to open the file\n");
        return e_fail;
    }
    return e_suc;
}