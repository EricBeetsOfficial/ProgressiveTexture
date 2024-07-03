Add submodule:

git submodule add https://github.com/<path>
git commit -am 'added sub module'
git push origin main

Clone:
git clone https://github.com/<path>
cd <path>
git submodule init
git submodule update

or

git clone --recurse-submodules https://github.com/<path>

Run Dr. Memory:
drmemory -brief -batch -- ./Test/Debug/runUnitTests.exe