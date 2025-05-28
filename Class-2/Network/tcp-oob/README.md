### Introduction

Tcp out of band data server/client test sample code.


### Platform

Ubuntu for Linux.


### Build

```console
make
```


### Run

`Note: Run the server first and then run the client.`

```console
$ ./tcp-server

TCP Sever running.
Server ip: 127.0.0.1, port: 65533.
Press CTRL+C to quit.

Recv: Test for client.
Recv: Test for client.
Oob data: A.
```

```console
$ ./tcp-client

```
