/*************************************************************************************
 *************************************************************************************
 Renzo Tejada
 *************************************************************************************
 **************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdbool.h>

/*Max number of characters to be read/write from file*/
#define MAX_CHAR_FOR_FILE_OPERATION 1000000

#define BUFSIZE 128

long
read_and_show_the_file (char const* path, char **buf, bool add_nul)
{
  FILE *fp;
  size_t fsz;
  long off_end;
  int rc;

  /* Open the file */
  fp = fopen (path, "r");
  if ( NULL == fp)
    {
      return -1L;
    }

  /* Seek to the end of the file */
  rc = fseek (fp, 0L, SEEK_END);
  if (0 != rc)
    {
      return -1L;
    }

  /* Byte offset to the end of the file (size) */
  if (0 > (off_end = ftell (fp)))
    {
      return -1L;
    }
  fsz = (size_t) off_end;

  /* Allocate a buffer to hold the whole file */
  *buf = malloc (fsz + (int) add_nul);
  if ( NULL == *buf)
    {
      return -1L;
    }

  /* Rewind file pointer to start of file */
  rewind (fp);

  /* Slurp file into buffer */
  if (fsz != fread (*buf, 1, fsz, fp))
    {
      free (*buf);
      return -1L;
    }

  /* Close the file */
  if ( EOF == fclose (fp))
    {
      free (*buf);
      return -1L;
    }

  if (add_nul)
    {
      /* Make sure the buffer is NUL-terminated, just in case */
      *buf[fsz] = '\0';
    }

  /* Return the file size */
  return (long) fsz;
}

long
write_and_show_the_file (char const* path, char **buf, bool add_nul)
{
  FILE *fp;
  size_t fsz;
  long off_end;
  int rc;

  /* Open the file */
  fp = fopen (path, "w");
  if ( NULL == fp)
    {
      return -1L;
    }

  fsz = (size_t) off_end;

  /* Allocate a buffer to hold the whole file */
  *buf = malloc (fsz + (int) add_nul);
  if ( NULL == *buf)
    {
      return -1L;
    }

  /* Rewind file pointer to start of file */
  rewind (fp);

  /* Slurp file into buffer */
  if (fsz != fread (*buf, 1, fsz, fp))
    {
      free (*buf);
      return -1L;
    }

  /* Close the file */
  if ( EOF == fclose (fp))
    {
      free (*buf);
      return -1L;
    }

  if (add_nul)
    {
      /* Make sure the buffer is NUL-terminated, just in case */
      *buf[fsz] = '\0';
    }

  /* Return the file size */
  return (long) fsz;
}

int
main (int argc, char *argv[])
{

  char *in_file_name  = argv[1];
  char *out_file_name = argv[2];
  char *in_file_key   = argv[3];
  char *inputarray; 			//inputarray will hold all chars of in_file_name
  char out[BUFSIZE], back[BUFSIZE];
  long file_size;

  DES_cblock key;
  DES_cblock seed =
    { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
  DES_key_schedule keysched;

  RAND_seed (seed, sizeof(DES_cblock));
  DES_random_key (&key);
  DES_set_key ((C_Block *) key, &keysched);


  memset(back, 0, sizeof(back));
  memset(out, 0, sizeof(out));
  unsigned char *e = out;

/*************************************************************************************
 *************************************************************************************
 * Step 1: read_and_show_the_file function reads *in_file_name, and stores it in in_file_name
 *************************************************************************************
 **************************************************************************************/
  file_size = read_and_show_the_file (in_file_name, &inputarray, false);

  if (file_size < 0L)
    {
      perror ("File read failed");
      return 1;
    }
  (void) fwrite (inputarray, 1, file_size, stdout);
  printf ("\n1. Plain_text: %s ", inputarray);

  /*************************************************************************************
   *************************************************************************************
   * Step 2: Create and write in out_file_name the hexadecimal value after inputfile has being encrypted
   *************************************************************************************
   **************************************************************************************/

  FILE *fp;
  fp = fopen (out_file_name, "wb");
  DES_ecb_encrypt ((C_Block *) inputarray, (C_Block *) out, &keysched, DES_ENCRYPT);
  printf ("\nCiphertext:");
  while (*e)
    {
      fprintf (fp, " %02x", *e++);
      printf (" %02x", *e++);
    };
  printf("\n------------------------\n");

  /*************************************************************************************
     *************************************************************************************
     * Step 3: Read out_file_name.txt file (now holding the cipher text) and along with the key Decrypte
     *************************************************************************************
     **************************************************************************************/
  DES_ecb_encrypt( (C_Block *) out, (C_Block *) back, &keysched, DES_DECRYPT);

  printf("\nDecrypted Text: %s\n", back);

  // int c=0; ---->for testing: prints array of input file
  // while(inputarray[c]!='\n'){
  //  printf("%c",inputarray[c]);
  //  c++;
  // }

  return 0;
}
