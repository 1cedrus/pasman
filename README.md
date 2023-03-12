# PASMAN (Password Managerment)

This is my first project and also is my first project in C programing language.
I have decided to do it just to improve my programing skill. 

## Author

- [@onecedrus](https://github.com/1cedrus)

## Support

- [@hisbrother](https://github.com/sinzii)

## Guide 

This tool is used to store your password in local (may be cloud in the future). It's use AES to encrypt password and your data.
Currently it have two version, is CLI and LINUX GTK. CLI is work well now, but LINUX GTK is a little bit bad. So I recommend you use CLI version. 

First time u use it, u need to set your master key, keep it enough secure but still ez to remmeber because if u forgot it, you can't roll back your password. It's now has 4 principle commands, NEW, DELETE, FIND, LIST.

## Installation

Install json-c

```bash
$ sudo apt update
$ sudo apt upgrade
$ sudo apt-get install libjson-c-dev
```
Install pasman

Clone this repo to your computer. In folder of pasman, run: 
```bash
$ make all
```
## Thanks you!
That's all. If you coming across with some bug. Send me that. Happy to help you.

## Updating 
Cloud store, generate password, UI