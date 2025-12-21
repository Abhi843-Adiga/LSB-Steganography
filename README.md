#LSB IMAGE STEGANOGRAPHY

##OVERVIEW

This project implements LSB(Least Significant Bit) image steganography using the C Programming language.
LSB steganography hides secret data inside the least significant bits of pixel values in bmp image. 

The technique is file-type independent and can hide any type of file(text,audio,video,image etc).

However in this implementation  encoding and decoding have been tested only for .txt files.

##FEATURES

-Validates source and secret files before encoding.    
-Automatically assigns the default file name if not provided.     
-Uses a Magic String to identify valid stego images.      
-Can encode any type of file at the algorithm level.      
-Encoding and Decoding is demonstrated using text files.      

##USAGE

-gcc *.c -> for compilation     
-./a.out -e <inp.bmp> <sec.txt> <steg.bmp> -> for encoding     
-./a.out -d <steg.bmp> <out.txt> -> for decoding        
