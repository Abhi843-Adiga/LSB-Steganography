#include<stdio.h>
#include "type.h"
#include "dec.h"
#include<string.h>

status read_and_validate_decode_args(char *argv[],dec *d)
{
    if(strstr(argv[2],".bmp")!=NULL)
    d->steg_img_fname=argv[2];
    else
    {
        printf("Invalid file extension\n");
        return e_fail;
    }

    if(argv[3]!=NULL)
    d->out_txt_fname=argv[3];
    else
    d->out_txt_fname="output.txt";

    return e_suc;
}

status open_files(dec *d)
{
    if((d->steg_img_fptr=fopen(d->steg_img_fname,"rb"))==NULL)
    return e_fail;
    
    if((d->out_txt_fptr=fopen(d->out_txt_fname,"wb"))==NULL)
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
    return e_suc;
}

char byte_to_lsb(dec *d)
{
    char ch=0;
    char rch;
    for(int i=0;i<8;i++)
    {
        fread(&rch,1,1,d->steg_img_fptr);
        ch= ch | (rch & 1) << i;
    }
    return ch;
}

status data_to_image(dec *d,char *str)
{
    char st[strlen(str)+1];
    for(int i=0;i<strlen(str);i++)
    st[i]=byte_to_lsb(d);
    st[strlen(str)]='\0';
    if(strcmp(st,str)==0)
    return e_suc;
    else
    {
        printf("%s",st);
        return e_fail;
    }
}

status decode_magic_string(dec *d,char *str)
{
    return data_to_image(d,str);
}

uint decode_size_to_lsb(dec *d)
{
    uint in=0;
    unsigned char rid;
    for(int i=0;i<32;i++)
    {
        fread(&rid,1,1,d->steg_img_fptr);
        in=in | ((rid & 1) <<i);
    }
    return in;
}

status decode_ext_size(dec *d,uint size)
{
    uint i=decode_size_to_lsb(d);
    if(i==size)
    {
         return e_suc;
    }
    else
    {
        printf("%u",i);
        return e_fail;
    }
}

status decode_extn_data(dec *d,char *str)
{
    return data_to_image(d,str);
}

status decode_data_size(dec *d)
{
    d->c=decode_size_to_lsb(d);
    return e_suc;
}

status decode_data(dec *d)
{
    char ch;
    for(int i=0;i<d->c;i++)
    {
        ch=byte_to_lsb(d);
        fwrite(&ch,1,1,d->out_txt_fptr);
    }
    return e_suc;
}

status do_decoding(dec *d)
{
    if(open_files(d)==e_suc)
    {
        printf("Files opened successfully\n");
        if(skip_bmp_header(d)==e_suc)
        {
            printf("Skipped bmp header successfully\n");
            if(decode_magic_string(d,M_S)==e_suc)
            {
                printf("Decoded Magic string successfully\n");
               strcpy(d->str,strstr(d->out_txt_fname,"."));
                if(decode_ext_size(d,strlen(d->str))==e_suc)
                {
                    printf("Decoded extension size\n");
                    if(decode_extn_data(d,d->str)==e_suc)
                    {
                        printf("Decoded extn data successfully\n");
                        if(decode_data_size(d)==e_suc)
                        {
                            printf("Decoded data size successfully\n");
                            if(decode_data(d)==e_suc)
                            {
                                printf("Decoded secret data successfully\n");
                            }
                            else
                            {
                                printf("Failed to decode secret data\n");
                                return e_fail;
                            }
                        }
                        else
                        {
                            printf("Decode of data size failure\n");
                            return e_fail;
                        }
                    }
                    else
                    {
                        printf("Decode of extn data failure\n");
                        return e_fail;
                    }
                }
                else
                {
                    printf("Decode of extn size failure\n");
                    return e_fail;
                }
            }
            else
            {
                printf("Decoding of magic_string failure\n");
                return e_fail;
            }
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
    return e_suc;
}