# HASH(Handy-Shell) for Linux/UNIX systems
---------------------------------------------------------------------
### There are specific rules for developers.
* Each developer will create his/her branch and will work on it.
* No changes will be directly committed to Master Branch.
* Follow coding [style guide](https://google.github.io/styleguide/cppguide.html) as defined by google. 
* Proper comments needed.

---------------------------------------------------------------------
## How to Use
* Compile `linuxLogoConfig.c` and `linuxLogo.c` and save them inside `~/.linuxLogo` directory.

#### Run these commands
* `$ gcc -o linuxLogo linuxLogo.c`
* `$ gcc -o linuxLogoXonfig linuxLogoConfig.c`
* `$ mkdir ~/.linuxLogo`
* `$ mv ./linuxLogo ./linuxLogoXonfig ~/.linuxLogo`
* `$ gcc hash.c`
* `$ ./a.out`
---------------------------------------------------------------------
