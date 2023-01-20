# Football
This is a small 2D graphics football game written in C++ with help of the SDL2 library.

## How to build?

### 1.  Download the Initial Packages to build the game : 
* #### The initial Packages required to build this game are
    * git
    * g++ compiler
    * make
    * CMake 
    * SDL2
    * SDL2_Image
    * SDL2_TTF
    * SDL2_Mixer

* #### To download these packages
    * #### For RHEL/Fedora
        ```bash==
        sudo dnf install SDL2-devel SDL2_image-devel SDL2_mixer-devel SDL2_ttf-devel make cmake g++ git
        ```
        
    * #### For Debian/Ubuntu-based OS 
        ```bash==
        sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev make cmake g++ git
        ```
### 2. Clone the Project
```bash==
git clone https://github.com/AryanGitHub/football.git
cd football
```

### 3. And To build it with help of CMake 
```bash==
mkdir build && cd build
cmake ../
cmake --build .
```
### 4. To Run the game
```bash==
./football
```
