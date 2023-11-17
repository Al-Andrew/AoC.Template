# AoC.Template

C++ template for AoC.
This handles reading getting the input from the site, and reading it in.

## build

We use xmake for a build system. So everything is one command. 

```sh
$ xmake build
```

## run

```sh
$ xmake run day01
```

### If you need to make changes
chage the root `main.cpp` file and run the `populate_days.ps1` script to copy it over to each of the days.

