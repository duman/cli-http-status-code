# HTTP Status Code from CLI

I keep forgetting what's what if it's not a common error, such as 404. So, I made this. You can run it on Linux and Windows.

Here's an example of it while working:
![GIF of CLI](https://i.imgur.com/p4Phiss.gif)

Check [releases](https://github.com/tkduman/cli-http-status-code/releases) for the executables if you don't want to compile it yourself.

Some notable things:
* Linux version uses libcurl, because I didn't find anything that could work in place of wininet.
* Windows version works on native wininet, thus way faster. Also the "Remote server is offline or unreachable, connection timed out." message is instant. Libcurl keeps on trying, so I set up a 5 second timeout limit on Linux. If no response is received after 5 seconds it will timeout and tell you.
* I remembered that a friend of mine requested this so he could use it while working, so here it is.

## Features and basics

* You can check status of a site by typing the domain.
Here's a few examples:
```console
duman@ubuntu:~$ status a.co
a.co	Response: 200 OK
duman@ubuntu:~$ status google.com
google.com	Response: 200 OK
duman@ubuntu:~$ status bmw.com
bmw.com	Response: 200 OK
duman@ubuntu:~$ status github.com
github.com	Response: 200 OK
duman@ubuntu:~$ status httpstat.us/500
httpstat.us/500	Response: 500 Internal Server Error
duman@ubuntu:~$ status google.com/32483
google.com/32483	Response: 404 Not Found
```

This will connect to the server and grab the status code, will display the URL that you've tried and the response of the server as the output.

* You can also directly ask what's the meaning of a status code. I keep forgetting them as I mentioned earlier.
Here's a few examples:
```console
duman@ubuntu:~$ status 200
OK
duman@ubuntu:~$ status 500
Internal Server Error
duman@ubuntu:~$ status 404
Not Found
duman@ubuntu:~$ status 403
Forbidden
duman@ubuntu:~$ status 418
I'm a teapot
duman@ubuntu:~$ status 422
Unprocessable Entity
```

Status code and their meanings are embedded to the source code, it should work pretty fast.

## Building on Linux

Before starting the building process make sure that you have correct libraries. I've done all the testing on Ubuntu 16.04.
Here's how you build it on Ubuntu 16.04. (May or may not work on other versions, find appropriate libraries. Also feel free to update the README if you wish to, I'll mostly likely forget about this repository tomorrow.)

```console
sudo apt-get install libcurl4-openssl-dev
g++ -std=c++0x http-status-linux.cpp -o status -lcurl
```

There you go, it's done. You can follow instructions on the [release](https://github.com/tkduman/cli-http-status-code/releases) page and add it to your path, so that you can call it directly by typing `status 503`. Isn't that cool? *(You may want to name it as something else because status itself is a thing already, you'll overwrite it if you leave the name as status on linux.)*

## Building on Windows

I've used Microsoft Visual Studio 2017, version 15.8.5. Nothing special needs to be installed because Windows version is using [wininet](https://docs.microsoft.com/en-us/windows/desktop/wininet/about-wininet), just build [http-status-windows.cpp](https://github.com/tkduman/cli-http-status-code/blob/master/http-status-windows.cpp) and you're good to go. Put the status.exe somewhere you like and add that folder to your path. Done! You can start using it right away. *(Don't forget to restart your command prompt for changes to apply.)*

## Is something wrong?

Open an issue, I'll try to fix it or help you with your problem. Do you know the solution already? Amazing, go ahead and submit a request.

Have fun.
