### Introduction

Multi thread tcp/udp server/client test sample code.


### Platform

Ubuntu for Linux.


### Build

```bash
make
```


### Run

`Note: Run the server first and then run the client.`

```console
$ ./tcp-server

TCP Sever running.
Server loop accept.
Server 4 Recv: Test for client.
Server 4 Recv: Test for client.
Server 4 Recv: Test for client.
Server 4 Recv: Test for client.
Server 4 Recv: Test for client.
Client exit.
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
