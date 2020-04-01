# Theory-of-algorithms

## Arkadiusz Mamala  G00349088

## Thery Of Algorithms Project Statment
You must write a program in the C programming language [2] that calculates
the MD5 hash digest of an input. The algorithm is specified in the Request
For Comments 1321 document supplied by the Internet Engineering Task
Force [5]. The only pre-requisite is that your program performs the algorithm
— you are free to decide what input the algorithm should be performed on.
I suggest you allow the user to input some free text or a filename via the
command line.

### What is the MD5 algorithm ?
The MD5 hash function was originally designed for use as a 
secure cryptographic hash algorithm for authenticating digital signatures

Plain text => 512 bits
MD5 = 128 bits

### Steps of the Algorithm
1. Append Padding => if less than 512 bits has to be 64 bits less than multiple of 512
2. Append 64 bit Representation 
    plain text length => multiple of 512 
3. Initialize the md buffers (size 32 bits) need 4 buffers 
4. Process each block (512)
5. output (message Digest in buffers)

<img src="https://github.com/ArekMamala/Theory-of-algorithms/blob/master/Md5/Assets/MessageAndDiggest.png" width="1000" height="400" />
#### Example:
+ if the plain text is 512
+ 512 - 64 = 448
=> 448+64 = 512 therefore its a multiple of 512
+ if the plain text is 1024
+ 1024 -54 = 960
=> 960+64 = 1024 therefore its a multiple of 512

### Message Processing

<img src="https://github.com/ArekMamala/Theory-of-algorithms/blob/master/Md5/Assets/ProccessingOfInputPart1.jpg" width="400" height="400" />

<img src="https://github.com/ArekMamala/Theory-of-algorithms/blob/master/Md5/Assets/ProccessingOfInputPart2.jpg" width="400" height="400" />

### References
+ https://searchsecurity.techtarget.com/definition/MD5
+ https://tools.ietf.org/html/rfc1321
+ https://github.com/ianmcloughlin/project-thalg-2020/raw/master/project.pdf
+ https://www.youtube.com/watch?v=53O9J2J5i14&t=226s#



