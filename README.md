<!--
##### Add submodule:

```sh
git submodule add https://github.com/<path>
git commit -am 'added sub module'
git push origin main
```
-->

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

### Unit Tests
#### Checks
#### Memory leak (based on Dr. Memory)
```sh
drmemory -brief -batch -- ./Test/Debug/runUnitTests.exe
```