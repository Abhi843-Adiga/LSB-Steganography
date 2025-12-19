#include<stdio.h>
#include "type.h"
#include "enc.h"
#include "dec.h"
#include<string.h>
int main(int c,char *argv[])
{
    enco e;
    dec d;
    if(c<3)
    {
        printf("ERROR : Please provide the correct arguments\n");
        printf("USAGE : %s arg1 arg2 arg3 ..\n",argv[0]);
        return 1;
    }

    int cho=check_op_type(argv);

    if(cho==e_enc)
    {
       printf("Encoding selected !\n");
       if(read_valid_enc_args(argv,&e)==e_suc)
       {
         printf("Read and validation of encode arguments is done successfully!\n");
         if(do_encoding(&e)==e_suc)
         printf("Encoding is success\n");
         else
         { 
            printf("Failed to encode\n");
            return 1;
         }
       }
       else
       {
          printf("ERROR : Failed to read and validate the arguments Check Once again !");
          return 1;
       }
    }
    else if(cho==e_dec)
    {
        printf("Decoding selected !\n");
        if(read_and_validate_decode_args(argv,&d)==e_suc)
        {
            printf("Read and validation of decode arguments is successfull\n");
            printf("Start decoding\n");
            if(do_decoding(&d)==e_suc)
            printf("Decoding is successfull");
            else
            {
                printf("Decoding is unsuccessfull\n");
                return 1;
            }
        }
        else
        {
            printf("read and validate of decode arguments is unsuccessfull\n");
            return 1;
        }
    }
    else if(cho==e_unsup)
    {
        printf("Choose the correct method\n");
        printf("ENCODING USAGE : %s -e \".bmp\" \".txt\" \".bmp\"\n",argv[0]);
        printf("DECODING USAGE : %s -d \".bmp\" \".txt\"\n",argv[0]);
        return 1;
    }
    
    return 0;
}

optype check_op_type(char *argv[])
{
    if(strcmp(argv[1],"-e")==0)
    return e_enc;
    else if(strcmp(argv[1],"-d")==0)
    return e_dec;
    else
    return e_unsup;
}