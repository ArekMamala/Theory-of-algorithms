# <p align="center"> Theory of Algorithms Overview 
#### <p align="center"> Student name: Arkadiusz Mamala <br>Student Number: G0034088 
### <p align="center">Introduction 
~~An introduction to your repository and code. Describe
what is contained in the repository and what the code does.~~

<i> Theory of Algorithm project 2020 - Ian McLoughlin</i><br>
At the begining of my second semester during my fourth academic year in the module Theory of Algorithms we were given a complicated task by the Lecturer Ian McLoughlin to complete.<br><br>
The task stated <br>
<i>You must write a program in the C programming language that calculates the MD5 hash digest of an input. The algorithm is specified in the Request For Comments 1321 document supplied by the Internet Engineering Task Force. The only pre-requisite is that your program performs the algorithm — you are free to decide what input the algorithm should be performed on. I suggest you allow the user to input some free text or a filename via the command line.</i><br>
<br>It was difficult for me to understand the assigment and have the knowlege on where to start on the problem given to us. I knew that it was the begining of the semester and the reason for us studying this module is because its requires new theories and new algorithms for us to reasearch and understand before we could start on any coading.<br>
<br>To the best of my knowledge, I belive that how most students felt at the start of the semester, I feel thats only right and it signifies that the module was given a lot of consideration a "module right for the students".
<br>
#### Repository
The repository contains two algorithms developed during this semmester in this module. We had studied the sha256 and the Md5 algorithms. These two algorithms are very similar in a way and we find that out while coding up both of them and comparing them side by side.<br>
In the "Theory-of-Algorithms" directory contains a README.md file which describes to the visitors and users what the repository contains and how to deploy the algorithms present.<br><br>
The md5 folder consists of only the necessary files for the md5 algorithm.
<br> <b>md5.c - </b><br> This file consists of the code typed out using c programming language. The file is easy to follow with many comments inserted for any software developer to understand. The algorithim will be explained down below if the comments in the file aren't enough or certain parts of the algorithm are tougher to understand through code.

<b>TextToHash.txt - </b><br> This file is used for the the users input or the testing input. It allows for different strings to get put through the md5 algorithm and recive a hash value for what is present in this file.

<b>README - </b><br> This is a short readme for the md5 algorithm which consists only of md5 processing information.

<b>Wiki file - </b><br>
The wiki file consists fo the reasearch carried out on this project and the md5 algorithm.

### <p align="center">Run
~~You should explain how to download, compile, and run your code.
Include instructions of how to install the compiler.~~

To run this project on any device the user need download the files onto their computer/device.

To get the project downloaded the user can do this in two ways using the terminal or downloading the provided zip file.

#### ZIP Download
1. Move into the github link of this project
    + https://github.com/ArekMamala/Theory-of-algorithms
1. top right corner you need to click on "Clone or Download"
    + An option will then appear for the user to download the .zip folder

#### CLONE Repository 
1. For this to work your coputer must have git installed 
    + link to download git  <b>https://git-scm.com/downloads</b>
1. After git is installed.
1. Open up terminal on the device that you decide to use.
    + cd into the chosen location on your computer
1. Type in the following command with the github repository link.
+ ```
    git clone  https://github.com/ArekMamala/Theory-of-algorithms 

1. Once this is done project is present in that chosen directory.

#### Compiling
1. Open the terminal on your computer
1. Move into the md5 folder the directory where the github repository got extracted to. 
1. Use the comand stated below to determine if you are in the correct directory.
+ ``` 
    dir

4. To compile the application enter the following command into th terminal.
+ ``` 
    gcc md5.c

5. This had compiled the c program and created a runnable file a.out
6. To run this program the command used in the terminal is 
+ ```
    ./a.out <command line argument> (--help) 

7. Depending on the comand line argument entered the application will execute different options.


### <p align="center">Test
~~Explain how to run the tests included in your code.~~

#### <p align="center">Test Cases for Command line Arguments
|Test Case   |      Test      |  Expected Result |  Pass/Fail
|----------|:-------------:|:------:|---------:|
| 1 |No argument | output to user to enter an argument | PASS       |
| 2 |Too many Arhuments   |  Error output too many arguments  | PASS       |
| 3 | --help |    Help option is displayed to the user | PASS       |
| 4 | --test|    Tests are automaticaly carried out | PASS       |
| 5 | --userInput | User can enter a string which gets hashed  | PASS       |
| 6 | --resources |    Resources of the project are displayed  | PASS       |


#### <p align="center">Test Cases for String hasshing
|Test Case   |      Test      |  Expected Result |  Pass/Fail
|----------|:-------------:|:------:|---------:|
| 1 | "" | d41d8cd98f00b204e9800998ecf8427e | PASS|
| 2 | "a" | 0cc175b9c0f1b6a831c399e269772661 | PASS|
| 3 | "abc" | 900150983cd24fb0d6963f7d28e17f72  | PASS|
| 4 | "message digest" |    f96b697d7cb7938d525a2f31aaf161d0  | PASS|
| 5 | "abcdefghijklmnopqrstuvwxyz" |    c3fcd3d76192e4007dfb496cca67e13b  | PASS|
| 6 | "ABCDEFGHIJKLMNOPQRSTUVWXYZab<br>cdefghijklmnopqrstuvwxyz0123456789" |    d174ab98d277d9f5a5611c2c9f419d9f  | PASS|
| 7 | "123456789012345678901234567890123<br>45678901234567890123456789012345678901234567890" |    57edf4a22be3c955ac49da2e2107b67a  | PASS|




### <p align="center">Algorithm 
~~Give an overview and explanation of the main algorithm(s)
in your code. You might use a well-thought out diagram here.~~

### <p align="center">Complexity 
~~This should be the most significant part of the report.
You must give an analysis of the complexity of the MD5 algorithm,
including the complexity of algorithms that attempt to reverse the
algorithm. That is, algorithms that attempt to find an input for
which the MD5 algorithm produces a given output. You should
research this topic before writing this section and your analysis
should be carefully referenced.~~
### <p align="center">References 
~~Provide a list of references used in your project. The
references should not just be a list of websites. Instead, there
should be a short explanation of why each reference is relevant to
your document.~~
https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository 
https://git-scm.com/downloads
https://rupinderjeetkaur.wordpress.com/2014/06/20/run-a-cc-program-on-terminal-using-gcc-compiler/