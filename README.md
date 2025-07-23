# Progressive Texture Loading

## Table of Contents
 - [Description](#description)
 - [RoadMap](#roadmap)
 - [Clone](#clone)
 - [Usage](#usage)
    - [Build](#build)
    - [Compilation](#compilation)
    - [Entry points](#entry-points)
    - [Unit Tests](#unit-tests)

<a id="description"></a>
## Description
This project implements a **progressive texture** loading system designed to minimize lag and frame drops during texture loading by loading textures incrementally in blocks of pixels. It enables textures to be loaded incrementally in a way that approaches **asynchronous behavior**, without blocking the main thread.

Originally developed for **Unity** (with plans for future support on ***Unreal Engine***), this system targets all major platforms including *Desktop* (Windows, Linux, macOS), *Mobile* (iOS, Android), and mixed reality (MR) *Headsets* (Quest, Hololens, ..).

This approach is especially crucial for large-scale projects and real-time applications such as **Augmented Reality (AR)** and **Virtual Reality (VR)**, where maintaining smooth performance and responsiveness is essential. By progressively loading textures, the system prevents noticeable hitches and ensures a seamless user experience, even with high-resolution or numerous textures.

> 🔗 This repository focuses on the **native C++ side** of the texture loading system.  
> It is meant to be used alongside a separate repository that contains the **managed C# layer for Unity integration**, which handles runtime communication, lifecycle management, and higher-level texture API access within the Unity engine.

<a id="roadmap"></a>
## RoadMap

### OS
- [X] Windows
- [ ] Linux
- [ ] MacOS
- [ ] Android
- [ ] iOS

### Platforms
- [X] OpenGL
- [ ] Direct X (11, 12)
- [ ] Metal
- [ ] Vulkan

### Source Loading Features
- [X] File from disk
- [ ] File from http request
- [ ] File from encode data
- [ ] File from raw data

### Supported Features
- [ ] Dynamic block size
- [ ] Mipmap
- [ ] Gamma / Linear
- [ ] Y Flip


<a id="clone"></a>
## Clone
```sh
$> git clone --recurse-submodules https://github.com/EricBeetsOfficial/ProgressiveTexture.git
```
##### or
```sh
$> git clone https://github.com/EricBeetsOfficial/ProgressiveTexture.git
$> cd ProgressiveTexture
$> git submodule init
$> git submodule update
```

<a id="usage"></a>
## Usage

<a id="build"></a>
#### Build
```
$> cd ProgressiveTexture
$> mkdir build && cd build
$> cmake -DCMAKE_BUILD_TYPE="Release" ..
```

<a id="compilation"></a>
#### Compilation
```
$> cd ProgressiveTexture
$> cd build
$> cmake --build . --config Release --target install
```

<a id="entry-points"></a>
#### Entry points
```
$> cd ProgressiveTexture
$> cd build
$> DUMPBIN -EXPORTS ../output/bin/Release/UnityPlugin.dll
```

<a id="unit-tests"></a>
#### Unit Tests
###### Checks
###### Memory leak (based on Dr. Memory)
```sh
drmemory -brief -batch -- ./Test/Debug/runUnitTests.exe
```