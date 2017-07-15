# my-FTP-server

This is a second year Epitech project, it is therefore subjected to the "C Norm" wich is a programming style convention created by the school.  
The full epitech norm is available here: https://youtrack.jetbrains.com/_persistent/norme-en.pdf?file=74-190945&v=0&c=true
If some parts of the code seems weird in their syntax, it's probably due to this norm.

The purpose of this project was to create a FTP server.
* The server must implement the given protocol (must be RFC959 compliant).
* The network communication will be achieved with TCP sockets.
* The server MUST be able to handle several clients at the same time by using a
fork.

```sh
Usage : ./server port path
port is the port number on which the server socket is listening.
path is the path to the home directory for the "Anonymous" user.
```

Forbidden functions :

* recv
* send
* all the system calls that make a socket non-blocking.


## Grade : 16.6/20
