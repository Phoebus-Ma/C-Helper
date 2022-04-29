### Introduction

Socket unix tcp server/client local communication test sample code.


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
Communication node: /tmp/testunix.sock.
Press CTRL+C to quit!

Connected client: 4, loop accept.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
From client 4 Recv: Test for client.
Connected client: 5, loop accept.
From client 5 Recv: Test for client.
From client 4 Recv: Test for client.
From client 5 Recv: Test for client.
From client 4 Recv: Test for client.
From client 5 Recv: Test for client.
Client exit.
From client 5 Recv: Test for client.
From client 5 Recv: Test for client.
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
