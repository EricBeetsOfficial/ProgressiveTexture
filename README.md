<!--
##### Add submodule:

```sh
git submodule add https://github.com/<path>
git commit -am 'added sub module'
git push origin main
```

cmake --build . && ctest && ./Test/Debug/TemplatesTest.exe && ./Debug/Thread.exe 

-->
**Summary**
 - [Description](#description)
 - [Clone](#clone)
 - [Usage](#usage)
 - [Unit Tests](#unit-tests)

<a id="description"></a>
#### Description

<a id="usage"></a>
#### Usage


<a id="clone"></a>
#### Clone repo
```sh
git clone --recurse-submodules https://github.com/<path>
```
##### or
```sh
git clone https://github.com/<path>
cd <path>
git submodule init
git submodule update
```

<a id="unit-tests"></a>
#### Unit Tests
##### Checks
##### Memory leak (based on Dr. Memory)
```sh
drmemory -brief -batch -- ./Test/Debug/runUnitTests.exe
```