all: mouth.c ear.c brain.c
	gcc mouth.c -o mouth
	gcc ear.c -o ear
	gcc brain.c 

clean: mouth ear
	rm -f a.out mouth ear;
	sh clean
