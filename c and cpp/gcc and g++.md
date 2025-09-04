# check versions of gcc and g++ in your system
```bash
ls /usr/bin/gcc*
ls /usr/bin/g++*
```
# check current version of gcc and g++
```bash
gcc --version
g++ --version
```
# install gcc and g++


# how to switch version of gcc and g++
```bash
sudo update-alternatives --config gcc
```

```bash
sudo update-alternatives --config g++
```

you will get something like this 

```bash
There are 2 choices for the alternative gcc (providing /usr/bin/gcc).

  Selection    Path             Priority   Status
------------------------------------------------------------
* 0            /usr/bin/gcc-12   12        auto mode
  1            /usr/bin/gcc-11   11        manual mode
  2            /usr/bin/gcc-12   12        manual mode

Press <enter> to keep the current choice[*], or type selection number: 1
update-alternatives: using /usr/bin/gcc-11 to provide /usr/bin/gcc (gcc) in manual mode
```



