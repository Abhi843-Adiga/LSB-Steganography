LSB IMAGE STEGANOGRAPHY:

This project implements LSB(Least Significant Bit) image steganography using the C Programming language.
LSB steganography hides secret data inside the least significant bits of pixel values in bmp image. 

The technique is file-type independent and can hide any type of file(text,audio,video,image etc).

However in this implementation  encoding and decoding have been tested only for .txt files.

FEATURES:

1.Validates source and secret files before encoding.    
2.Automatically assigns the default file name if not provided.     
3.Uses a Magic String to identify valid stego images.      
4.Can encode any type of file at the algorithm level.      
5.Encoding and Decoding is demonstrated using text files.      

USAGE:

1. gcc *.c -> for compilation     
2. ./a.out -e <inp.bmp> <sec.txt> <steg.bmp> -> for encoding     
3. ./a.out -d <steg.bmp> <out.txt> -> for decoding        
