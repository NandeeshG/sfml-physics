# Install dependencies

```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev
```

# Create build files

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

# Compile

```
cmake --build build --config Release
```

# Run

```
./build/bin/main
```
