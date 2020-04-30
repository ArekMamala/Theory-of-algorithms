//Arkadiusz Mamala
//Theory of Algorythms - MD5

// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

// Resources
// https://tools.ietf.org/html/rfc1321

/* Constants for MD5Transform routine.
 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21



// Pre-defined hash values
const uint32_t k[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


//got from sha256 algorithm
union block {
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
};

typedef unsigned long int UINT4;

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += F((b), (c), (d)) + (x) + (ac); \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define GG(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += G((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define HH(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += H((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define II(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += I((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }

enum flag {READ, PAD0, FINISH};

//padding for the files size 64 
static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



//from sha 256 argorithm chenged to suit md5 
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status) {
  //padding 
  // no bytes variable
  size_t nobytesread; 

  if (*status == FINISH)
    return 0;

  int i;

  if (*status == PAD0) {
    for (i = 0; i < 56; i++)
      M->eight[i] = 0x00;
    M->sixfour[7] = *nobits;
    *status = FINISH;
    return 1;
  }

  nobytesread = fread(M->eight, 1, 64, infile);
  if (nobytesread == 64)
    return 1;

  // If we can fit all padding in last block:
  if (nobytesread < 56) {
    M->eight[nobytesread] = 0x80;
    for (int i = nobytesread + 1; i < 56; i++)
      M->eight[i] = 0;
    M->sixfour[7] = *nobits;
    *status = FINISH;
    return 1;
  }
  
  // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
  M->eight[nobytesread] = 0x80;
  for (int i = nobytesread + 1; i < 64; i++)
    M->eight[i] = 0;
  *status = PAD0;
  return 1;
}

static void md5_hash(union block *M, uint32_t *Hash)
{
  uint32_t a, b, c, d;
  a = Hash[0];
  b = Hash[1];
  c = Hash[2];
  d = Hash[3];

  /* Round 1 */
  FF(a, b, c, d, M->threetwo[0], S11, k[0]);  /* 1 */
  FF(d, a, b, c, M->threetwo[1], S12, k[1]);  /* 2 */
  FF(c, d, a, b, M->threetwo[2], S13, k[2]);  /* 3 */
  FF(b, c, d, a, M->threetwo[3], S14, k[3]);  /* 4 */
  FF(a, b, c, d, M->threetwo[4], S11, k[4]);  /* 5 */
  FF(d, a, b, c, M->threetwo[5], S12, k[5]);  /* 6 */
  FF(c, d, a, b, M->threetwo[6], S13, k[6]);  /* 7 */
  FF(b, c, d, a, M->threetwo[7], S14, k[7]);  /* 8 */
  FF(a, b, c, d, M->threetwo[8], S11, k[8]);  /* 9 */
  FF(d, a, b, c, M->threetwo[9], S12, k[9]);  /* 10 */
  FF(c, d, a, b, M->threetwo[10], S13,k[10]); /* 11 */
  FF(b, c, d, a, M->threetwo[11], S14,k[11]); /* 12 */
  FF(a, b, c, d, M->threetwo[12], S11,k[12]); /* 13 */
  FF(d, a, b, c, M->threetwo[13], S12,k[13]); /* 14 */
  FF(c, d, a, b, M->threetwo[14], S13,k[14]); /* 15 */
  FF(b, c, d, a, M->threetwo[15], S14,k[15]); /* 16 */
  /* Round 2 */
  GG(a, b, c, d, M->threetwo[1], S21, k[16]);  /* 17 */
  GG(d, a, b, c, M->threetwo[6], S22, k[17]);  /* 18 */
  GG(c, d, a, b, M->threetwo[11], S23,k[18]); /* 19 */
  GG(b, c, d, a, M->threetwo[0], S24, k[19]);  /* 20 */
  GG(a, b, c, d, M->threetwo[5], S21, k[20]);  /* 21 */
  GG(d, a, b, c, M->threetwo[10], S22,k[21]);  /* 22 */
  GG(c, d, a, b, M->threetwo[15], S23,k[22]); /* 23 */
  GG(b, c, d, a, M->threetwo[4], S24, k[23]);  /* 24 */
  GG(a, b, c, d, M->threetwo[9], S21, k[24]);  /* 25 */
  GG(d, a, b, c, M->threetwo[14], S22,k[25]); /* 26 */
  GG(c, d, a, b, M->threetwo[3], S23, k[26]);  /* 27 */
  GG(b, c, d, a, M->threetwo[8], S24, k[27]);  /* 28 */
  GG(a, b, c, d, M->threetwo[13], S21,k[28]); /* 29 */
  GG(d, a, b, c, M->threetwo[2], S22, k[29]);  /* 30 */
  GG(c, d, a, b, M->threetwo[7], S23, k[30]);  /* 31 */
  GG(b, c, d, a, M->threetwo[12], S24,k[31]); /* 32 */

  /* Round 3 */
  HH(a, b, c, d, M->threetwo[5], S31, k[32]);  /* 33 */
  HH(d, a, b, c, M->threetwo[8], S32, k[33]);  /* 34 */
  HH(c, d, a, b, M->threetwo[11], S33,k[34]); /* 35 */
  HH(b, c, d, a, M->threetwo[14], S34,k[35]); /* 36 */
  HH(a, b, c, d, M->threetwo[1], S31, k[36]);  /* 37 */
  HH(d, a, b, c, M->threetwo[4], S32, k[37]);  /* 38 */
  HH(c, d, a, b, M->threetwo[7], S33, k[38]);  /* 39 */
  HH(b, c, d, a, M->threetwo[10], S34,k[39]); /* 40 */
  HH(a, b, c, d, M->threetwo[13], S31,k[40]); /* 41 */
  HH(d, a, b, c, M->threetwo[0], S32, k[41]);  /* 42 */
  HH(c, d, a, b, M->threetwo[3], S33, k[42]);  /* 43 */
  HH(b, c, d, a, M->threetwo[6], S34, k[43]);   /* 44 */
  HH(a, b, c, d, M->threetwo[9], S31, k[44]);  /* 45 */
  HH(d, a, b, c, M->threetwo[12], S32,k[45]); /* 46 */
  HH(c, d, a, b, M->threetwo[15], S33,k[46]); /* 47 */
  HH(b, c, d, a, M->threetwo[2], S34, k[47]);  /* 48 */

  /* Round 4 */
  II(a, b, c, d, M->threetwo[0], S41, k[48]);  /* 49 */
  II(d, a, b, c, M->threetwo[7], S42, k[49]);  /* 50 */
  II(c, d, a, b, M->threetwo[14], S43,k[50]); /* 51 */
  II(b, c, d, a, M->threetwo[5], S44, k[51]);  /* 52 */
  II(a, b, c, d, M->threetwo[12], S41,k[52]); /* 53 */
  II(d, a, b, c, M->threetwo[3], S42, k[53]);  /* 54 */
  II(c, d, a, b, M->threetwo[10], S43,k[54]); /* 55 */
  II(b, c, d, a, M->threetwo[1], S44, k[55]);  /* 56 */
  II(a, b, c, d, M->threetwo[8], S41, k[56]);  /* 57 */
  II(d, a, b, c, M->threetwo[15], S42,k[57]); /* 58 */
  II(c, d, a, b, M->threetwo[6], S43, k[58]);  /* 59 */
  II(b, c, d, a, M->threetwo[13], S44,k[59]); /* 60 */
  II(a, b, c, d, M->threetwo[4], S41, k[60]);  /* 61 */
  II(d, a, b, c, M->threetwo[11], S42,k[61]); /* 62 */
  II(c, d, a, b, M->threetwo[2], S43, k[62]);  /* 63 */
  II(b, c, d, a, M->threetwo[9], S44, k[63]);  /* 64 */

  Hash[0] += a;
  Hash[1] += b;
  Hash[2] += c;
  Hash[3] += d;
}


static void hashTheFile (){
  
  FILE *infile = fopen("test", "rb");
  if (!infile)
  {
    //if there is no file
    printf("Error: couldn't open file s.\n");
  }
 
    uint32_t H[4] = {
    0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476  
  };
  
  // The current padded message block.
  union block M;
  uint64_t nobits = 0;
  enum flag status = READ;

    // Read through all of the padded message blocks.
    while (nextblock(&M, infile, &nobits, &status)) {
      // Calculate the next hash value.
      md5_hash(&M, H);
    }

    printf("\nHash value of file with MD5 algorithm\n");

    //loop through h
    for (int i = 0; i < 4; i++)
          //print out hash
      printf("%02" PRIx32 "", H[i]);
    printf("\n");
    //close file
    fclose(infile);

}


void writeToFile(char *str){
    FILE *fptr;

    // opening file in writing mode
    fptr = fopen("test", "w");

    // exiting program 
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "%s", str);
    fclose(fptr);
}


int main(int argc, char *argv[])
{

  int i;
  if( argc == 2 )
  {
      printf("The arguments supplied are: ");
      for(i = 1; i < argc; i++)
      {
          printf("%s\t", argv[i]);
          if (strcmp(argv[i],"--help") == 0)
          {
            printf("\n*** HELP ***");
            printf("\nplease enter one of the following command line arguments.\n\n");
            printf("\t--help => How to run Program information.\n");
            printf("\t--test => Automatic testing of the following strings.\n");
            printf("\t\t''\n\t\t'a'\n\t\t'abc'\n\t\t'message digest'\n\t\t'abcdefghijklmnopqrstuvwxyz'\n\t\t'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'\n\t\t'12345678901234567890123456789012345678901234567890123456789012345678901234567890'");
            printf("\n\t--userInput => Testing of Users input.\n");
            printf("\t\tAllows the user to enter a string that will be hashed and print out the result to the user.\n");
            printf("\t--resources => Resoures of the project.\n");
            printf("\t\tA link to the project repository.\n\t\tLink to the projects readme & Reasearch.\n\n");
            
          }else if (strcmp(argv[i],"--test") == 0){
            
            printf("\n*** Test ***");
            writeToFile("");
            hashTheFile();
            printf("Expected Result: d41d8cd98f00b204e9800998ecf8427e\n");
    
            printf("\nString tested: 'a'");
            writeToFile("a");
            hashTheFile();
            printf("Expected Result: 0cc175b9c0f1b6a831c399e269772661\n");

            printf("\nString tested: 'abc'");
            writeToFile("abc");
            hashTheFile();            
            printf("Expected Result: 900150983cd24fb0d6963f7d28e17f72\n");

            printf("\nString tested: 'message digest'");
            writeToFile("message digest");
            hashTheFile();
            printf("Expected Result: f96b697d7cb7938d525a2f31aaf161d0\n");

            printf("\nString tested: 'abcdefghijklmnopqrstuvwxyz'");
            writeToFile("abcdefghijklmnopqrstuvwxyz");
            hashTheFile();
            printf("Expected Result: c3fcd3d76192e4007dfb496cca67e13b\n");


            printf("\nString tested: 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'");
            writeToFile("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
            hashTheFile();
            printf("Expected Result: d174ab98d277d9f5a5611c2c9f419d9f\n");


            printf("\nString tested: '12345678901234567890123456789012345678901234567890123456789012345678901234567890'");
            writeToFile("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
            hashTheFile();
            printf("Expected Result: 57edf4a22be3c955ac49da2e2107b67a\n");


          }else if (strcmp(argv[i],"--userInput")  == 0){
           
            printf("\n*** User Input ***");
            char str[100] = ""; 
            char fileName[100]  = "test.txt";
            printf("\nEnter an string to hash: ");
            scanf("%[^\n]%*c", str); 
            writeToFile(str);
            hashTheFile();


          }else if (strcmp(argv[i],"--resources")  == 0){
            printf("\n*** Resources ***");
            printf("\nProject reposritory.\n");
            printf("\thttps://github.com/ArekMamala/Theory-of-algorithms\n");
            printf("Readme repository.\n");
            printf("\thttps://github.com/ArekMamala/Theory-of-algorithms/blob/master/README.md\n"); 
            printf("Reasearch repository.\n");
            printf("\thttps://github.com/ArekMamala/Theory-of-algorithms/wiki\n"); 
          }else{
            printf("\nplease enter one of the following command line arguments.\n\n");
            printf("--help => How to run Program information.\n");
            printf("--test => Automatic testing of the following strings.\n");
            printf("--userInput => Testing of Users input.\n");
            printf("--resources => Resoures of the project.\n\n");
          }
      }
  }
  else
  {
    printf("Incorect input format.\n");
    printf("\nplease enter one of the following command line arguments.\n\n");
    printf("--help => How to run Program information.\n");
    printf("--test => Automatic testing of the following strings.\n");
    printf("--userInput => Testing of Users input.\n");
    printf("--resources => Resoures of the project.\n\n");
   }
  
}