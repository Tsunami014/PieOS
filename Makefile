CFLAGS = -Wall -g -static

# — Create the main file —————————————————————————————————————————————
main: Makefile main.c
	rm -f main
	gcc $(CFLAGS) -o main main.c
	chmod +x ./main

# — Create the init file —————————————————————————————————————————————
init: Makefile init.c main.c
	rm -f ./rootfs/init
	gcc $(CFLAGS) -DWRAPPED_BUILD -o rootfs/init init.c main.c $(CORE)
	chmod +x ./rootfs/init

# — Convenience: run under kitty and pause at end ————————————————————
test: main
	@kitty bash -c './main; echo; read -p "Program finished! Press enter to continue."'

# — Clean out everything —————————————————————————————————————————————
clean:
	rm -f main
	rm -f ./rootfs/init
