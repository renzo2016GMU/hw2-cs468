all:	clean hw2 pipeline1
hw2:
	gcc -I/usr/local/opt/openssl/include -o  hw2 -lcrypto hw2.c

pipeline1: 
	./hw2 deskey.txt CS468-HW2.txt out.txt
clean:
	-rm hw2 