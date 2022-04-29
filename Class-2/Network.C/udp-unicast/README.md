### Introduction

UDP unicast server/client test sample code.


### Platform

Ubuntu for Linux.


### Build

```console
make
```


### Run

`Note: Run the server first and then run the client.`

```console
$ ./udp-server

UDP server running.
[Server] client ip: 127.0.0.1, port: 49851.
[Server] Recv data: Hello UDP Server.
[Server] client ip: 127.0.0.1, port: 49851.
[Server] Recv data: Hello UDP Server.
[Server] client ip: 127.0.0.1, port: 49851.
[Server] Recv data: Hello UDP Server.
[Server] client ip: 127.0.0.1, port: 49851.
[Server] Recv data: Hello UDP Server.
[Server] client ip: 127.0.0.1, port: 49851.
[Server] Recv data: Hello UDP Server.
... ...
```

```console
$ ./udp-client

[Client] Recv data: OK.
[Client] Recv data: OK.
[Client] Recv data: OK.
[Client] Recv data: OK.
[Client] Recv data: OK.
```
