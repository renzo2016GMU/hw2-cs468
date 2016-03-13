/*************************************************************************************
 *************************************************************************************
 Renzo Tejada
 Dec
 *************************************************************************************
 **************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>

/*Max number of characters to be read/write from file*/

#define BUFSIZE 512

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
	char *in_file_key = argv[2];//key from the directory file that holds the key
	char *in_file_name = argv[3];//as cyphertext
	char *out_file_name = argv[4];

	char *inputarray, *keyarray; 		// will hold all chars of in_file_name
	unsigned char out[BUFSIZE], back[BUFSIZE];
	long file_size;
	long key_size;

	DES_key_schedule keysched;
	DES_cblock key;
	DES_random_key(&key);
	DES_set_key((C_Block *) key, &keysched);

	memset(back, 0, sizeof(back));
	memset(out, 0, sizeof(out));
	unsigned char *e = out;
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

	FILE *fp;
	fp = fopen(out_file_name, "wb");

	DES_ecb_encrypt((C_Block *) inputarray, (C_Block *) out, &keysched, DES_DECRYPT);
	DES_ecb_encrypt((C_Block *) out, (C_Block *) back, &keysched, DES_DECRYPT);

	//printf("\nCiphertext:");
	while (*e)
	{
		fprintf(fp, " %02x", *e++);
//		printf(" %02x", *e++);
	};
	printf("\n------------------------\n");




	char *encrypted;
	encrypted=malloc(sizeof(inputarray));
	memcpy(encrypted,Encrypt(key,inputarray,sizeof(inputarray)), sizeof(inputarray));












	//******   currently only printing 8 characters to the cyphertext. should be more?

	/*************************************************************************************
	 *************************************************************************************
	 * Step 3: Read out_file_name.txt file (now holding the cipher text) and along with the key Decrypte
	 *************************************************************************************
	 **************************************************************************************/

//	printf("\nDecrypted Text: %s\n", back);

	// int c=0; ---->for testing: prints array of input file
	// while(inputarray[c]!='\n'){
	//  printf("%c",inputarray[c]);
	//  c++;
	// }

	return 0;
}
