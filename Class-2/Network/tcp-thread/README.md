### Introduction

Multi thread tcp server/client test sample code.


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

Connected client: 4, loop accept.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
... ...
```

```console
$ ./tcp-client

Client recv: OK.
Client recv: OK.
Client recv: OK.
Client recv: OK.
Client recv: OK.
```
