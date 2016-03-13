all:	des_ecb_enc des_ecb_dec pipeline1 pipeline2

des_ecb_enc:
	gcc -I/usr/local/opt/openssl/include -o  des_ecb_enc -lcrypto DES_ECB_Enc.c

des_ecb_dec:
	gcc -I/usr/local/opt/openssl/include -o  des_ecb_dec -lcrypto DES_ECB_Dec.c

pipeline1: 
	./des_ecb_enc -k deskey.txt CS468-HW2.txt CS468-HW2.mydesecb

pipeline2: 
	./des_ecb_dec -k deskey.txt CS468-HW2.mydesecb CCS468-HW2.mydesecb.txt
	
clean:
	-rm des_ecb_enc
	-rm des_ecb_dec