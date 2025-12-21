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
        printf("ERROR: Invalid file extension !\n");
        return e_fail;
    }
    
    if(strstr(argv[3],".txt")!=NULL)
    enc->sec_txt_fname=argv[3];
    else
    {
        printf("ERROR: Invalid file extension !\n");
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
    en->src_img_fptr=fopen(en->src_img_fname,"rb");
    if(en->src_img_fptr==NULL)
    {
        printf("ERROR: File unable to open\n");
        return e_fail;
    }

    en->sec_txt_fptr=fopen(en->sec_txt_fname,"r");
    if(en->sec_txt_fptr==NULL)
    {
        printf("ERROR: File unable to open\n");
        return e_fail;
    }

    en->steg_img_fptr=fopen(en->steg_img_fname,"wb");
    if(en->steg_img_fptr==NULL)
    {
        printf("ERROR: File unable to open\n");
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
    uint s=ftell(fp);
    rewind(fp);
    return s;
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
    en->header_size=s+14;
    char st[en->header_size];
    rewind(en->src_img_fptr);
    fread(st,en->header_size,1,en->src_img_fptr);
    fwrite(st,en->header_size,1,en->steg_img_fptr);
    fseek(en->src_img_fptr,en->header_size,SEEK_SET);
    fseek(en->steg_img_fptr,en->header_size,SEEK_SET);
    return e_suc;
}

status encode_byte_to_lsb(char sym,char *str)
{
    for(int i=0;i<8;i++)
    str[i]=(str[i] & 0xFE) | ((sym>>i) & 1);
    return e_suc;
}

status encode_data_to_image(enco *en,char *data,int si)
{
   for(int i=0;i<si;i++)
    {
        fread(en->str,8,1,en->src_img_fptr);
        encode_byte_to_lsb(data[i],en->str);
        fwrite(en->str,8,1,en->steg_img_fptr);
    }
   return e_suc;
}

status encode_magic_string(enco *en,char *m_s)
{
    return encode_data_to_image(en,m_s,strlen(m_s));
}

status size_to_lsb(enco *en,uint size)
{
    char str[32];
    fread(str,32,1,en->src_img_fptr);
    for(int i=0;i<32;i++)
    str[i]=(str[i] & 0xFE) | ((size>>i) & 1);
    fwrite(str,32,1,en->steg_img_fptr);
    return e_suc;
}

status encode_ext_size(enco *en,uint size)
{
    return size_to_lsb(en,size);
}

status encode_ext(enco *en,char *str)
{
    return encode_data_to_image(en,str,strlen(str));
}

status encode_file_size(enco *en,uint size)
{
    return size_to_lsb(en,size);
}

status encode_file_data(enco *en)
{
    char str[en->sec_txt_fsize];
    fseek(en->sec_txt_fptr,0,SEEK_SET);
    fread(str,1,en->sec_txt_fsize,en->sec_txt_fptr);
    return encode_data_to_image(en,str,en->sec_txt_fsize);
}

status copy_remaining_data(enco *en)
{
    uint rem=en->header_size+en->src_img_size-ftell(en->src_img_fptr);
    char str[rem];
    fread(str,rem,1,en->src_img_fptr);
    fwrite(str,rem,1,en->steg_img_fptr);
    return e_suc;
}

status do_encoding(enco *en)
{
    printf("Checking required files can open...\n");
    sleep(2);
    if(check_open(en)==e_suc)
    {
        printf("INFO: FILE OPENED SUCCESSFULLY\n");
        printf("Checking image can hold the secret file data...\n");
        sleep(2);
        if(check_capacity(en)==e_suc)
        {
            printf("INFO: Capacity checked successfully\n");
            printf("Copying the BMP Header...\n");
            sleep(2);
            if(copy_bmp_header(en)==e_suc)
            {
                printf("INFO: Copied BMP header successfully\n");
                printf("ENCODING START...\n");
                sleep(3);
                if(encode_magic_string(en,M_S)==e_suc)
                {
                    printf("INFO: Magic string is encoded successfully\n");
                    strcpy(en->st,strstr(en->sec_txt_fname,"."));
                    if(encode_ext_size(en,strlen(en->st))==e_suc)
                    {
                        printf("INFO: Extension size encoded successfully\n");
                        if(encode_ext(en,en->st)==e_suc)
                        {
                            printf("INFO: Extension data encoded successfully\n");
                            if(encode_file_size(en,en->sec_txt_fsize)==e_suc)
                            {
                                printf("INFO: Encoded secret file size successfully\n");
                                if(encode_file_data(en)==e_suc)
                                {
                                   printf("INFO: Encoded secret file successfully\n");
                                   if(copy_remaining_data(en)==e_suc)
                                   {printf("INFO: Copied remaining data successfully\n");
                                    sleep(2);}
                                   else{
                                    printf("ERROR: Copy of remaining data failure\n");
                                    return e_fail;
                                   }
                                } 
                                else
                                {
                                    printf("ERROR: Encoding of secret file failure\n");
                                    return e_fail;
                                }
                            }
                            else
                            {
                                printf("ERROR: Secret file size encoding failure\n");
                                return e_fail;
                            }
                        }
                        else
                        {
                            printf("ERROR: Extension data encoding failure\n");
                            return e_fail;
                        }
                    }
                    else
                    {
                        printf("ERROR:Extension size encode failure\n");
                        return e_fail;
                    }
                }
                else
                {
                    printf("ERROR:Magic string encoding failure\n");
                    return e_fail;
                }
            }
            else
            {
                printf("ERROR: Failed to copy BMP header\n");
                return e_fail;
            }
        }
        else
        {
            printf("ERROR: Failed to check capacity\n");
            return e_fail;
        }
    }
    else
    {
        printf("ERROR: Failed to open the file\n");
        return e_fail;
    }
    return e_suc;
}