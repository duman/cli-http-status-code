# HTTP Status Code from CLI

I keep forgetting what's what if it's not a common error, such as 404. So, I made this. You can run it on Linux and Windows.

Here's an example of it while working: **(NEW, now with descriptions and with ability to display header)**
![GIF of CLI](https://i.imgur.com/UW4RGXf.gif)

Check [releases](https://github.com/tkduman/cli-http-status-code/releases) for the executables if you don't want to compile it yourself.

Some notable things:
* Linux version uses libcurl, because I didn't find anything that could work in place of wininet.
* Windows version works on native wininet, thus way faster. Also the "Remote server is offline or unreachable, connection timed out." message is instant. Libcurl keeps on trying, so I set up a 5 second timeout limit on Linux. If no response is received after 5 seconds it will timeout and tell you.
* Windows version now uses curl for calling the header, but if you don't want to see the header everything will work through wininet.
* Linux version uses curl for everything.
* I remembered that a friend of mine requested this so he could use it while working, so here it is.

## Features and basics

* You can check status of a site by typing the domain.
Here's a few examples:
```console
duman@ubuntu:~/Desktop/http-cli$ status a.co
a.co	Response: 200 OK

Description: The request has succeeded.
duman@ubuntu:~/Desktop/http-cli$ status google.com
google.com	Response: 200 OK

Description: The request has succeeded.
duman@ubuntu:~/Desktop/http-cli$ status 420
Method Failure / Enhance Your Calm (Twitter)

Description 1: Not part of the HTTP standard, but defined by Spring in the HttpStatus class to be used when a method failed. This status code is deprecated by Spring.

Description 2: Not part of the HTTP standard, but returned by version 1 of the Twitter Search and Trends API when the client is being rate limited. Other services may wish to implement the 429 Too Many Requests response code instead.
duman@ubuntu:~/Desktop/http-cli$ status reddit.com -h
reddit.com	Response: 200 OK

Description: The request has succeeded.

Header:
HTTP/1.1 301 Moved Permanently
Retry-After: 0
Location: https://www.reddit.com/
Content-Length: 0
Accept-Ranges: bytes
Date: Mon, 17 Dec 2018 16:02:23 GMT
Via: 1.1 varnish
Connection: close
X-Served-By: cache-fra19122-FRA
X-Cache: HIT
X-Cache-Hits: 0
X-Timer: S1545062543.362026,VS0,VE0
Cache-Control: private, max-age=3600
Server: snooserv
```

This will connect to the server and grab the status code, will display the URL that you've tried and the response of the server as the output.

* You can see the header response from the server if you wish to by adding "-h" or "h" as the second argument. **(NEW, both Windows and Linux!)**

Here's an few example:
```console
status google.com -h
https://google.com      Response: 200 OK

Description: The request has succeeded.

Header:
HTTP/1.1 301 Moved Permanently
Location: https://www.google.com/
Content-Type: text/html; charset=UTF-8
Date: Sun, 16 Dec 2018 17:05:12 GMT
Expires: Tue, 15 Jan 2019 17:05:12 GMT
Cache-Control: public, max-age=2592000
Server: gws
Content-Length: 220
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Alt-Svc: quic=":443"; ma=2592000; v="44,43,39,35"
```

* You can also directly ask what's the meaning of a status code. I keep forgetting them as I mentioned earlier. **(NEW, Now with descriptions!)
Here's a few examples:
```console
duman@ubuntu:~$ status 200
OK

Description: The request has succeeded.
duman@ubuntu:~$ status 500
Internal Server Error

Description: The server encountered an unexpected condition that prevented it from fulfilling the request.
duman@ubuntu:~$ status 404
Not Found

Description: The origin server did not find a current representation for the target resource or is not willing to disclose that one exists.
duman@ubuntu:~$ status 403
Forbidden

Description: The server understood the request but refuses to authorize it.
duman@ubuntu:~$ status 418
I'm a teapot

Description: Any attempt to brew coffee with a teapot should result in the error code "418 I'm a teapot". The resulting entity body MAY be short and stout.
duman@ubuntu:~$ status 422
Unprocessable Entity

Description: The server understands the content type of the request entity (hence a 415 Unsupported Media Type status code is inappropriate), and the syntax of the request entity is correct (thus a 400 Bad Request status code is inappropriate) but was unable to process the contained instructions.
```

Status code and their meanings are embedded to the source code, it should work pretty fast.
Non-http standard code is also included, which means you can check CloudFlare and some other custom code, such as 420.

```console
status httpstat.us/420
https://httpstat.us/420 Response: 420 Method Failure / Enhance Your Calm (Twitter)

Description 1: Not part of the HTTP standard, but defined by Spring in the HttpStatus class to be used when a method failed. This status code is deprecated by Spring.

Description 2: Not part of the HTTP standard, but returned by version 1 of the Twitter Search and Trends API when the client is being rate limited. Other services may wish to implement the 429 Too Many Requests response code instead.
```

* **(NEW, URL is now checked with regex)**
Invalid URL will now warn you, however if your URL contains unicode character such as "ü", program will crash. On the next version I'll probably fix this.

## Building on Ubuntu

Before starting the building process make sure that you have correct libraries. I've done all the testing on Ubuntu 16.04.
Here's how you build it on Ubuntu 16.04. (May or may not work on other versions, find appropriate libraries. Also feel free to update the README if you wish to, I'll mostly likely forget about this repository tomorrow.)

```console
sudo apt-get install libcurl4-openssl-dev
g++ -std=c++0x http-status-linux.cpp -o status -lcurl
```

There you go, it's done. You can follow instructions on the [release](https://github.com/tkduman/cli-http-status-code/releases) page and add it to your path, so that you can call it directly by typing `status 503`. Isn't that cool? *(You may want to name it as something else because status itself is a thing already, you'll overwrite it if you leave the name as status on linux.)*

~~*Linux version currently doesn't support displaying the header feature, will be added with next release.*~~

## Building on CentOS 7

Building on CentOS is slightly trickier but nothing hard.

```console
yum install curl-devel # this is equivalent of libcurl4-openssl-dev from Ubuntu
yum install gcc-c++ # installs g++, however gcc version is too low to compile the code

yum install centos-release-scl
yum install devtoolset-6
scl enable devtoolset-6 bash # this will make your gcc go to 6.3.1 version, and everything will good to go
g++ -std=c++0x http-status-linux.cpp -o status -lcurl
```

There you go, it's done. You can follow instructions on the [release](https://github.com/tkduman/cli-http-status-code/releases) page and add it to your path, so that you can call it directly by typing `status 503`. Isn't that cool? *(You may want to name it as something else because status may be a thing itself already, you'll overwrite it if you leave the name as status on linux.)*

## Building on Windows

I've used Microsoft Visual Studio 2017, version 15.8.5. You will need libcurl to make this run on Windows. [First version](https://github.com/tkduman/cli-http-status-code/releases/tag/v1.0.0) did not require any extra libraries, however with the added ability to display the header you have to build the source code with libcurl.

After the build, you can place the executable anywhere and add the folder to your path to use it with ease.

## Is something wrong?

Open an issue, I'll try to fix it or help you with your problem. Do you know the solution already? Amazing, go ahead and submit a request.

Have fun.
