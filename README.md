# Pie OS
An "operating system" whose sole purpose is to print out all the digits of pi forever in the shape of a pie

# Dependancies
```bash
sudo apt-get install pkg-config # for building
sudo apt install libevdev-dev
```

# Building and running
- To build into an executable:
    - `make main`: Makes the main file into an executable `./main`
    - `make clean`: Removes all output from make and build and test
## Testing
- If you use VSCode, there's a launch configuration setup for this
- `make test`: Makes the main file into an executable and then runs it in kitty (ensure installed)

## To make into a bootable OS
- **BUILDING FOR THE FIRST TIME:** `./build`
- **BUILDING AFTER HAVING DONE IT BEFORE:** `./updateBuild`

### Manual use
Here are all the commands in `./build` and `./updateBuild` (only the ones with `*` are in `./updateBuild`)
1. Create the new filesystem's root folder
```bash
mkdir ./rootfs
```
2. `*`Compile the code into the rootfs
```bash
make init
```
3. `*`Pack it into an initrd and move it to the boot folder
```bash
(cd rootfs && find . | cpio -o -H newc) | gzip > initrd-tos.img
sudo mv initrd-tos.img /boot/
```
4. Add GRUB config files to have the new OS as an option
```bash
sudo tee /etc/grub.d/40_custom > /dev/null <<EOF
#!/bin/sh
exec tail -n +3 $0

menuentry "Terminal OS" {
            search --set=root --file /boot/vmlinuz
            linux /boot/vmlinuz root=/dev/ram0 rdinit=/init
            initrd /boot/initrd-tos.img
}
EOF
sudo chmod +x /etc/grub.d/40_custom
```
5. `*`Update grub and pray everything works
```bash
sudo update-grub
```
