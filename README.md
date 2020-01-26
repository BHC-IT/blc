# install
``` bash
[ -d blc ] && (cd blc && git pull) || git clone https://github.com/BHC-IT/blc
mkdir blc/build
cd blc/build && cmake ..  && sudo make -j9 install
```
