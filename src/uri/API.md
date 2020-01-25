
# Uri 

This is a API documentation for using the URI class. Although the class is called URI
but it is written in a fashion that it will only pass URLs for now. if anything
changes in the future, this document will be updated to say the same

### Building
```console
$ git clone https://github.com/0xVarun/octo.git Octo
$ cd Octo && mkdir build && cd build
$ cmake -G Ninja -DBUILD_URI_LIBRARY=ON -DURI_BUILD_STYLE=<STATIC|SHARED> ..
$ ninja
```

### Usage

```c++
#include <string>
#include <iostream>

#include <octo/uri/uri.h>

int main(int argc, char **argv) {
    std::string url = "https://www.example.com:443/foo/bar?foo=bar&bar=foo";
    octo::uri::Uri uri;
    uri.parse(url); // return true (bool)
    uri.getProtocol(); // return https (std::string)
    uri.getHost(); // return www.example.com (std::string)
    uri.getPort(); // return 443 (uint16_t)
    uri.getPath(); // return { "", "foo", "bar" } (std::vector< std::string >)
    uri.getQueryString() // return { ("foo", "bar"), ("bar", "foo") } 
                         // std::vector< std::pair< std::string, std::string >>
    
    octo::Uri::uri newUri;
    newUri.setProtocol("https");
    newUri.setHost("www.google.com");
    newUri.setPort(443);
    newUri.setPath({"", "bar", "foo"});
    newUri.setQuery({ std::make_pair("q", "octo" )});

    std::cout << newUri << std::endl; // https://www.google.com:443/bar/foo?q=octo
    
}
```
