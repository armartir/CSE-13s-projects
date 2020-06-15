Artyom Martirosyan
11/2/2019
Assignment 5: factoring
For this assignment we created a program which takes a user argument and find 
all of the prime and composite numbers from 2 to the number seleced; if the number was composite the program will also print out the prime factorization of the number. To run the program: simply type make or make all to compile and then type ./factor if you want the program to run to a specific number type ./factor -n x with x being the number; if no number is selected the default value will be 100000. So to run type make and ./factor -n x or ./factor. There is an issue with infer where it will give you an error at the line where you implement the sieve function as stated in piazza this is because of the potential that there could be a null issue to quote "infer is trying to guess what bad thing could happen" meaning this could be an issue but will most likely never be one. When running valgrind I recieved no memory leak errors.
