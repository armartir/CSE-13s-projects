Artyom Martirpsyan
Lab8 LZW Compression
For this program we are compressing and decompressing a file using a compression algorithm which was created by Mr. Zimmerman. To run this program one option is either type ./lzwencoder with several flags the first flag which must be included is the -c or -d flag which tells the user if the program is going to compress or decompress something. The next flag used is -i and an input and -o and an output(note if you dont provide either flags or simply dont give an input or output name it will default to standard in). You can also type encode or decode with most flags(except for using the -c or -d flags). For my program when infer is ran I recieve several errors as well two of them being for not freing two strdups however if you run valgrind this error doesnt come up, I believe this is due to the fact that infer doesnt run the program therefore it doesnt reach the free statements which free the strdups. The second error I recieve is an uninitialization error, I also believe that this is being caused because of the fact that the program isnt being run meaning that infer doesnt realise when they are being initialize. I am also recieving a memory leak when I run my decompression(which WORKS exactly like Eugene's example code) I believe that this error is caused because memory is being allocated inside of the loop(when you set a one char star equal to another). I hope that this grader does grade somewhat leniantly as my assingment can compress and decompress the bible.   