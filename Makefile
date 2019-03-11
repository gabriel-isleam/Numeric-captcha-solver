
build: 
	gcc -Wall bmp_header.h ex.c 

run: $1
	cat input.txt | ./a.out

clean:
	rm a.out bmp_header.h.gch captcha_task1.bmp captcha_task2.txt captcha_task3.bmp
