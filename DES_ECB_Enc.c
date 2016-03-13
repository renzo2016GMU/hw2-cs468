/*************************************************************************************
 *************************************************************************************
 Renzo Tejada
 File name des_ecb_enc

 *************************************************************************************
 **************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>

/*Max number of characters to be read/write from file*/

#define BUFSIZE 512

char *
Encrypt( char *Key, char *Msg, int size);


/*Read file passed in first argument*/
long read_file(char const* path, char **buf, bool add_nul)
{
	FILE *fp;
	size_t fsz;
	long end_reached;

	fp = fopen(path, "r");
	if (NULL == fp) 	{	return -1L;	}
	/* Look for end of file */
	int rc;
	rc = fseek(fp, 0L, SEEK_END);
	if (0 != rc)
	{
		return -1L;
	}

	/* Byte offset to the end of the file (size) */
	if (0 > (end_reached = ftell(fp)))
	{
		return -1L;
	}
	fsz = (size_t) end_reached;

	/* Allocate a buffer to hold the whole file */
	*buf = malloc(fsz + (int) add_nul);
	if ( NULL == *buf)
	{
		return -1L;
	}

	/* Rewind file pointer to start of file */
	rewind(fp);

	/* Slurp file into buffer */
	if (fsz != fread(*buf, 1, fsz, fp))
	{
		free(*buf);
		return -1L;
	}

	/* Close the file */
	if ( EOF == fclose(fp))
	{
		free(*buf);
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

long read_file_key(char const* path, char **buf, bool add_nul)
{
	FILE *fp;
	size_t fsz;
	long end_reached;
	int rc;

	/* Open the file */
	fp = fopen(path, "r");
	if ( NULL == fp)
	{
		return -1L;
	}

	/* Seek to the end of the file */
	rc = fseek(fp, 0L, SEEK_END);
	if (0 != rc)
	{
		return -1L;
	}

	/* Byte offset to the end of the file (size) */
	if (0 > (end_reached = ftell(fp)))
	{
		return -1L;
	}
	fsz = (size_t) end_reached;

	/* Allocate a buffer to hold the whole file */
	*buf = malloc(fsz + (int) add_nul);
	if ( NULL == *buf)
	{
		return -1L;
	}

	/* Rewind file pointer to start of file */
	rewind(fp);

	/* Slurp file into buffer */
	if (fsz != fread(*buf, 1, fsz, fp))
	{
		free(*buf);
		return -1L;
	}

	/* Close the file */
	if ( EOF == fclose(fp))
	{
		free(*buf);
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


int main(int argc, char *argv[])
{
	char  *checkfork = argv[1];
//	int x = 0;
//		x=	strcmp(checkfork,'-k');
//	if(x!=0){
//		printf("Error");
//		exit(0);
//	}
	char *in_file_key = argv[2];
	char *in_file_name = argv[3];
	char *out_file_name = argv[4];

	char *inputarray, *keyarray; 		// will hold all chars of in_file_name
	unsigned char CS468_HW2_mydesecb[BUFSIZE], back[BUFSIZE];
	long file_size;
	long key_size;

	DES_key_schedule keysched;
	DES_cblock key;
	DES_random_key(&key);
	DES_set_key((C_Block *) key, &keysched);

	memset(back, 0, sizeof(back));
	memset(CS468_HW2_mydesecb, 0, sizeof(CS468_HW2_mydesecb));
	unsigned char *e = CS468_HW2_mydesecb;
	unsigned char *f = key;

	/*************************************************************************************
	 *************************************************************************************
	 * Step 1: read_file function reads *in_file_name, and stores it in in_file_name
	 *************************************************************************************
	 **************************************************************************************/

	printf(
			"\n------------------------------------------------------------------------------------------------\n----------------------------------------Start of Program----------------------------------------\n------------------------------------------------------------------------------------------------\n");
	printf("\n1. Plain_text_input: ");
	file_size = read_file(in_file_name, &inputarray, false);

	if (file_size < 0L)
	{
		perror("File read failed");
		return 1;
	}
	(void) fwrite(inputarray, 1, file_size, stdout);

	printf("\n1. Plain_text_Key:  ");
	key_size = read_file_key(in_file_key, &keyarray, false);

	if (key_size < 0L)
	{
		perror("File read failed");
		return 1;
	}
	(void) fwrite(keyarray, 1, key_size, stdout);

	DES_cblock plaintext_value_key;
	DES_string_to_key(inputarray, &plaintext_value_key); //Convert key from char to hex key format
//  while (*f)
//    {
//      fprintf (fp, " %02x", *e++);
//      printf (" %02x", *e++);
//    };
//  printf("\n------------------------\n");

	/*************************************************************************************
	 *************************************************************************************
	 * Step 2: Create and write in out_file_name the hexadecimal value after inputfile has being encrypted
	 *************************************************************************************
	 **************************************************************************************/
//encryption occurs  1 out gets cyphertext
	FILE *fp;
	fp = fopen(out_file_name, "wb");
	DES_ecb_encrypt((C_Block *) inputarray, (C_Block *) CS468_HW2_mydesecb, &keysched,
			DES_ENCRYPT);
	//printf("\nCiphertext:");
	while (*e)
	{
		fprintf(fp, %c, *e++);
//		printf(" %02x", *e++);
	};

//	 int ret;
//	 char oldname[] = "out.txt";
//	 char newname[] = "CS468-HW2.mydesecb";
//	 ret= rename(oldname, newname);
//	   ret = rename(oldname, newname);
//
//	   if(ret == 0)
//	   {
//	      printf("File renamed successfully");
//	   }
//	   else
//	   {
//	      printf("Error: unable to rename the file");
//	   }


	char *encrypted;
	encrypted=malloc(sizeof(inputarray));
	memcpy(encrypted,Encrypt(keyarray,inputarray,sizeof(inputarray)), sizeof(inputarray));
	printf("Encrypted text\t : %s \n",encrypted);

	printf("\n------------------------------\n");

	//******   currently only printing 8 characters to the cyphertext. should be more?

	/*************************************************************************************
	 *************************************************************************************
	 * Step 3: Read out_file_name.txt file (now holding the cipher text) and along with the key Decrypte
	 *************************************************************************************
	 **************************************************************************************/
//	DES_ecb_encrypt((C_Block *) CS468_HW2_mydesecb, (C_Block *) back, &keysched, DES_DECRYPT);


	return 0;
}
//	DES_ecb_encrypt((C_Block *) inputarray, (C_Block *) CS468_HW2_mydesecb, &keysched,DES_ENCRYPT);
// DES_ecb_encrypt((C_Block *) inputarray, (C_Block *) CS468_HW2_mydesecb, &keysched,DES_ENCRYPT);
char *
Encrypt( char *Key, char *Msg, int size)
{

        static char*    Res;
        int             n=0;
        DES_cblock      Key2;
        DES_key_schedule schedule;

        Res = ( char * ) malloc( size );

        /* Prepare the key for use with DES_cfb64_encrypt */
        memcpy( Key2, Key,8);
        DES_set_odd_parity( &Key2 );
        DES_set_key_checked( &Key2, &schedule );

        /* Encryption occurs here */
        DES_cfb64_encrypt( ( unsigned char * ) Msg, ( unsigned char * ) Res,
                           size, &schedule, &Key2, &n, DES_ENCRYPT );

         return (Res);
}
