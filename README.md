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

## Project repository content
  This trepository consists of three folders 
  + Md5
  + shaAlgorythm
  Also consists of 
  + gitignore
  + README.md
  + overview.md  
  #### shaAlgorythm folder
   This is the sha256 algorithm that has been developed through out finalyear semester 
   in the course "Theory Of Algorithms".
   + README.md
   + Readme
   + hello.c
   + hello.py
   + lookatbits
   + lookatbits.c
   + padding.c
   + sha256
   + sha256.c
   + unions.c
  
  #### Md5 folder
   + Assets folder
     + MessageAndDiggest.pnh
     + ProccessingOfInputPart1.jpg
     + ProccessingOfInputPart2.jpg
   + README
   + a.out
   + md5.c
   + test
  
  ## How to run
   #### To run the sha256 
   1. Clone the repository 
     + using terminal command "git clone https://github.com/ArekMamala/EmergingTechnologies.git"  
     + or download zip and unzip it in chses destination
   1. make your way into the shaAlgorythm folder using the following command
     + "cd shaAlgorythm"
   1. using terminal compile the algorithm using this command
     + "sudo gcc sha25d.c" 
   1. using terminal run the folowing command to run algorithm
     + "./a.out test" 
       + "a.out" is the file created by compiling the c code
       + "test" is a testing empty text file
   
   #### To run the md5 
   1. Clone the repository 
     + using terminal command "git clone https://github.com/ArekMamala/EmergingTechnologies.git"  
     + or download zip and unzip it in chses destination
   1. make your way into the Md5 folder using the following command
     + "cd Md5"
   1. using terminal compile the algorithm using this command
     + "sudo gcc md5.c" 
   1. using terminal run the folowing command to run algorithm
     + "./a.out test" 
       + To run this program the command used in the terminal is 
       + ./a.out <command line argument> (--help) 

   1. Depending on the command line argument entered the application will execute different options.
   1. These are the following command line arguments
    * --help
    * --test
    * --userInput
    * --resources

   1. For more information on how to run or test the application look at the overview.md file 
   



#### <p align="center">Project Plan
|No.   | Things to do     |  When |  Completed/Not Completed
|:----------:|:-------------:|:------:|:---------:|
| 1 |Watch class Videos | As videos are released <br>Each week | Completed |
| 2 |Code up SHA256  | After videos are seen | Completed     |
| 3 | Compare Sha256 with MD5 | After Sha256 is complete |Completed |
| 4 | Determin necesary code <br>from sha256 for MD5 | When step 4 is completed  | Completed   |
| 5 | Study the website https://tools.ietf.org/html/rfc1321 | Any time During the project. | Completed       |
| 6 | Reasearch Md5 algorithm | Through out the project| Completed |
| 7 | Start coding algorithm | After md5 is reasearched| Completed |
| 8 | Have basic program done in c | Any time sooner the better| Completed |
| 9 | Files reading in | Through out the project| Completed |
| 10 | Coverting to hash values| Through out the project| Completed |
| 11 | correct hash value | Towards the end of the year| Not Completed |
| 12 | Reasearch for project started | After md5 program done| Completed |
| 13 | ReadMe started| End of the project| Completed |
| 14 | Complete Readme file| End of semester| Completed |
| 15 | Add command line arguments| Before new deadline| Completed |
| 16 | Start Overview| End of semester| Completed |
| 17 | Finish Overview| End of semester| Completed |
| 18 | Fix output issue| End of semester|Not Completed |
| 19 | Tidy as much code as possible|Befored deadline| Not Completed |



## Reasearch 
  * Reasearch for this project is in the wiki page of the project
  * [https://github.com/ArekMamala/Theory-of-algorithms/wiki](https://github.com/ArekMamala/Theory-of-algorithms/wiki)



