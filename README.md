# cpp-rss
Sample c++ REST service implementation using "served"


## Installation

[Using CentOS-8.2]

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake
sudo dnf install make
sudo dnf install gcc
sudo dnf install gcc-c++
sudo dnf install libstdc++-
sudo dnf install libstdc++-devel
sudo dnf install glibc
sudo dnf install glibc-devel
sudo dnf install pkgconfig
sudo dnf install boost
sudo dnf install boost-devel
sudo dnf install boost-static

git clone git@github.com:meltwater/served.git
cd served
mkdir build && cd build
cmake .. && make
sudo make install

export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

### Building

```bash
git clone https://github.com/Shariful-NomaD-Islam/cpp-rss.git
cd cpp-rss
mkdir build
cd build
rm -rf *
cmake .. 
make
```

### Execute

```bash
../build/cpp-rss
```

### Available example:

```bash
curl "http://localhost:9191/api/version"
curl "http://localhost:9191/api/greeting?name=_NAME_"
curl "http://localhost:9191/api/named-user/nomad"
curl "http://localhost:9191/api/patern-user/8"
curl "http://localhost:9191/api/get"
curl -d '{ " key ": " value " }' -H " Content - Type : application / json " -X POST http://localhost:9191/api/post/45
```



###### Created time: 25 AUG 2020
###### Last updated: 25 AUG 2020