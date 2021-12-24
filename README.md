# PortSniffer

_Made by: Rafael Almada (slimkaki)_
___

## Description

A project to create a C port sniffer, given an IP address. It may be possible to sniff throughout all the possible ports, or otherwise, search for specific ports.

## Installation

```sh
$ git clone https://github.com/slimkaki/PortSniffer
$ cd PortSniffer/
$ gcc -Wall src/main.c -o output/sniff
```

## Usage

```sh
$ ./output/sniffer <IP Address> <Port to Sniff>
```

> Disclaimer: This software is fully created by me (slimkaki) and it's intention is for educational purposes only. Creating a low-level socket code is a good material for studies.