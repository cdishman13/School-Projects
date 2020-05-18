all: game check advance winnable

game: play.c
	gcc -o game -I/share/cs327/include play.c /share/cs327/lib/libtermbox.a

winnable: win.c
	gcc -o winnable win.c

check: check.c
	gcc -o check check.c

advance: solitare.c
	gcc -o advance solitare.c
