
# Octo 

#### Build Status

[![Build Status](https://api.travis-ci.com/0xVarun/octo.svg?branch=development)](https://travis-ci.org/0xVarun/octo)

Octo is an attempt to write a framework for webservices in C++

a static library that you should be able to drop in and write webservices,
compile and deploy 

```cpp
#include <octo/octo.h>

void handleGet(octo::context ctx, octo::Request req, octo::Response res) {
    res->json({ "message": "ok" });
}

int main(int argc, char **argv) {
    octo::Service service;
    service.router->GET("/foo", handleGet);
    octo::RunInThread()->register(service)->run();
}
```
