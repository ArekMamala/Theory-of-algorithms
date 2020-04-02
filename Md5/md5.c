//Arkadiusz Mamala
//Theory of Algorythms - MD5

// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Resources
// https://tools.ietf.org/html/rfc1321

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
    (a) += F((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define GG(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += G((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define HH(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += H((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }
#define II(a, b, c, d, x, s, ac)                 \
  {                                              \
    (a) += I((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT((a), (s));                 \
    (a) += (b);                                  \
  }

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

enum flag {READ, PAD0, FINISH};

//padding for the files size 64 
static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

#define VAR uint32_t

//got from sha256 algorithm
union block {
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
};

//from sha 256 argorithm chenged to suit md5 p
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
      M->eight[i] = 0x00;
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
  FF(a, b, c, d, M[0], S11, 0xd76aa478);  /* 1 */
  FF(d, a, b, c, M[1], S12, 0xe8c7b756);  /* 2 */
  FF(c, d, a, b, M[2], S13, 0x242070db);  /* 3 */
  FF(b, c, d, a, M[3], S14, 0xc1bdceee);  /* 4 */
  FF(a, b, c, d, M[4], S11, 0xf57c0faf);  /* 5 */
  FF(d, a, b, c, M[5], S12, 0x4787c62a);  /* 6 */
  FF(c, d, a, b, M[6], S13, 0xa8304613);  /* 7 */
  FF(b, c, d, a, M[7], S14, 0xfd469501);  /* 8 */
  FF(a, b, c, d, M[8], S11, 0x698098d8);  /* 9 */
  FF(d, a, b, c, M[9], S12, 0x8b44f7af);  /* 10 */
  FF(c, d, a, b, M[10], S13, 0xffff5bb1); /* 11 */
  FF(b, c, d, a, M[11], S14, 0x895cd7be); /* 12 */
  FF(a, b, c, d, M[12], S11, 0x6b901122); /* 13 */
  FF(d, a, b, c, M[13], S12, 0xfd987193); /* 14 */
  FF(c, d, a, b, M[14], S13, 0xa679438e); /* 15 */
  FF(b, c, d, a, M[15], S14, 0x49b40821); /* 16 */
M  /* Round 2 */
  GG(a, b, c, d, M[1], S21, 0xf61e2562);  /* 17 */
  GG(d, a, b, c, M[6], S22, 0xc040b340);  /* 18 */
  GG(c, d, a, b, M[11], S23, 0x265e5a51); /* 19 */
  GG(b, c, d, a, M[0], S24, 0xe9b6c7aa);  /* 20 */
  GG(a, b, c, d, M[5], S21, 0xd62f105d);  /* 21 */
  GG(d, a, b, c, M[10], S22, 0x2441453);  /* 22 */
  GG(c, d, a, b, M[15], S23, 0xd8a1e681); /* 23 */
  GG(b, c, d, a, M[4], S24, 0xe7d3fbc8);  /* 24 */
  GG(a, b, c, d, M[9], S21, 0x21e1cde6);  /* 25 */
  GG(d, a, b, c, M[14], S22, 0xc33707d6); /* 26 */
  GG(c, d, a, b, M[3], S23, 0xf4d50d87);  /* 27 */
  GG(b, c, d, a, M[8], S24, 0x455a14ed);  /* 28 */
  GG(a, b, c, d, M[13], S21, 0xa9e3e905); /* 29 */
  GG(d, a, b, c, M[2], S22, 0xfcefa3f8);  /* 30 */
  GG(c, d, a, b, M[7], S23, 0x676f02d9);  /* 31 */
  GG(b, c, d, a, M[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH(a, b, c, d, M[5], S31, 0xfffa3942);  /* 33 */
  HH(d, a, b, c, M[8], S32, 0x8771f681);  /* 34 */
  HH(c, d, a, b, M[11], S33, 0x6d9d6122); /* 35 */
  HH(b, c, d, a, M[14], S34, 0xfde5380c); /* 36 */
  HH(a, b, c, d, M[1], S31, 0xa4beea44);  /* 37 */
  HH(d, a, b, c, M[4], S32, 0x4bdecfa9);  /* 38 */
  HH(c, d, a, b, M[7], S33, 0xf6bb4b60);  /* 39 */
  HH(b, c, d, a, M[10], S34, 0xbebfbc70); /* 40 */
  HH(a, b, c, d, M[13], S31, 0x289b7ec6); /* 41 */
  HH(d, a, b, c, M[0], S32, 0xeaa127fa);  /* 42 */
  HH(c, d, a, b, M[3], S33, 0xd4ef3085);  /* 43 */
  HH(b, c, d, a, M[6], S34, 0x4881d05);   /* 44 */
  HH(a, b, c, d, M[9], S31, 0xd9d4d039);  /* 45 */
  HH(d, a, b, c, M[12], S32, 0xe6db99e5); /* 46 */
  HH(c, d, a, b, M[15], S33, 0x1fa27cf8); /* 47 */
  HH(b, c, d, a, M[2], S34, 0xc4ac5665);  /* 48 */

  /* Round 4 */
  II(a, b, c, d, M[0], S41, 0xf4292244);  /* 49 */
  II(d, a, b, c, M[7], S42, 0x432aff97);  /* 50 */
  II(c, d, a, b, M[14], S43, 0xab9423a7); /* 51 */
  II(b, c, d, a, M[5], S44, 0xfc93a039);  /* 52 */
  II(a, b, c, d, M[12], S41, 0x655b59c3); /* 53 */
  II(d, a, b, c, M[3], S42, 0x8f0ccc92);  /* 54 */
  II(c, d, a, b, M[10], S43, 0xffeff47d); /* 55 */
  II(b, c, d, a, M[1], S44, 0x85845dd1);  /* 56 */
  II(a, b, c, d, M[8], S41, 0x6fa87e4f);  /* 57 */
  II(d, a, b, c, M[15], S42, 0xfe2ce6e0); /* 58 */
  II(c, d, a, b, M[6], S43, 0xa3014314);  /* 59 */
  II(b, c, d, a, M[13], S44, 0x4e0811a1); /* 60 */
  II(a, b, c, d, M[4], S41, 0xf7537e82);  /* 61 */
  II(d, a, b, c, M[11], S42, 0xbd3af235); /* 62 */
  II(c, d, a, b, M[2], S43, 0x2ad7d2bb);  /* 63 */
  II(b, c, d, a, M[9], S44, 0xeb86d391);  /* 64 */

  Hash[0] += a;
  Hash[1] += b;
  Hash[2] += c;
  Hash[3] += d;


}

int main(int argc, char *argv[])
{
  //file reading from sha256 example
  if (argc != 2)
  {
    //if the amount of iles is not right
    printf("Error: expected single filename as argument.\n");
    return 1;
  }

  FILE *infile = fopen(argv[1], "rb");
  if (!infile)
  {
    //if there is no file
    printf("Error: couldn't open file %s.\n", argv[1]);
    return 1;
  }
 
    uint32_t H[] = {
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
      printf("%02" PRIX32 "", H[i]);
    printf("\n");
    //close file
    fclose(infile);

  return 0;
}