<!--
##### Add submodule:

```sh
git submodule add https://github.com/<path>
git commit -am 'added sub module'
git push origin main
```

cmake --build . && ctest && ./Test/Debug/TemplatesTest.exe && ./Debug/Thread.exe 

-->
# Progressive texture
 - [Description](#description)
 - [Clone](#clone)
 - [Usage](#usage)
 - [Unit Tests](#unit-tests)

<a id="description"></a>
## Description

<a id="clone"></a>
## Clone repo
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

<a id="usage"></a>
## Usage


<a id="unit-tests"></a>
## Unit Tests
#### Checks
#### Memory leak (based on Dr. Memory)
```sh
drmemory -brief -batch -- ./Test/Debug/runUnitTests.exe
```

<br/>
<br/>
<br/>


| Platform          |   Store Asset                     |
| ----------------- | ------------------------------------------ |
| Windows           | [![Made with Unity]][Link]         |
| UWP               | [![Made with Unity]][Link]         |
| Android           | [![Made with Unity]][Link]         |
| iOS               | [![Made with Unity]][Link]         |
| macOS             | [![Made with Unity]][Link]         |

[Link]: http://ericbeets.free.fr
[Made with Unity]: https://img.shields.io/badge/Made%20with-Unity-57b9d3.svg?style=plastic&logo=unity

<!-- cmake -DCMAKE_BUILD_TYPE=Release .. -->
<!-- cmake --build . --config Release -->
<!-- cmake --install . --config Release -->
<!-- DUMPBIN -EXPORTS ../output/bin/Release/UnityPlugin.dll -->