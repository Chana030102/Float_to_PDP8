

op_convert: op_convert.c
	gcc -g -Wall -o op_convert op_convert.c

clean:
	rm -f op_convert


