### Introduction

Use select for tcp server/client test sample code.


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

Connected client ip: 127.0.0.1, port: 60736.
From client 4, data: Test for client.
From client 4, data: Test for client.
Connected client ip: 127.0.0.1, port: 60738.
From client 5, data: Test for client.
From client 4, data: Test for client.
From client 5, data: Test for client.
From client 4, data: Test for client.
From client 5, data: Test for client.
From client 4, data: Test for client.
From client 5, data: Test for client.
Out of band data: +.
Client 4 exit.
From client 5, data: Test for client.
Out of band data: +.
Client 5 exit.

User command:

quit
User command: quit

Server will exit.
```

```console
$ ./tcp-client

Client recv: OK.
Client recv: OK.
Client recv: OK.
Client recv: OK.
Client recv: OK.
```
