
function install_clang {
    wget https://apt.llvm.org/llvm.sh;
    chmod +x llvm.sh;

    sudo ./llvm.sh 17;

    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100;
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100;

    sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang-17 100;
    sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-17 100;

    rm ./llvm.sh;
}

function set_clang {
    sudo update-alternatives --set cc /usr/bin/clang-17;
    sudo update-alternatives --set c++ /usr/bin/clang++-17;
}

function install_gcc {
    sudo apt update;
    sudo apt install software-properties-common -y;

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y;
    sudo apt update;

    sudo apt install gcc-13 g++-13 -y;

    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100;
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100;

    sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-13 100;
    sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-13 100;
}

function set_gcc {
    sudo update-alternatives --set cc /usr/bin/gcc-13;
    sudo update-alternatives --set c++ /usr/bin/gcc++-13;
}

function install_gtest {
    sudo apt-get install libgtest-dev;

    cd /usr/src/gtest;

    sudo cmake CMakeLists.txt;
    sudo make;

    sudo cp ./lib/libgtest*.a /usr/lib;

    sudo mkdir /usr/local/lib/gtest;
    sudo ln -s /usr/lib/libgtest.a /usr/local/lib/gtest/libgtest.a;
    sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/gtest/libgtest_main.a;

    cd -;
}

function install_cmake {
    wget https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7-linux-x86_64.sh
    chmod +x cmake-3.27.7-linux-x86_64.sh;

    sudo ./cmake-3.27.7-linux-x86_64.sh --skip-license --prefix=/opt/cmake-3.27.7-linux-x86_64/;
    sudo ln -s /opt/cmake-3.27.7-linux-x86_64/bin/* /usr/local/bin;
    
    rm cmake-3.27.7-linux-x86_64.sh;
}

function install_clang_format {
    sudo apt install clang-format-17
}

function prepare {
    install_cmake;    
    install_gtest;
    install_clang;
    install_clang_format;
    set_clang;
}

function build {
    mkdir -p ./build && (cd ./build && cmake .. && make);
}

function rebuild {
    rm -rf ./build && build;
}

function run {
    build && ./build/aoc "$@"; 
}

function format {
    find src/ -iname *.hh -o -iname *.cc | xargs clang-format-17 -i -style=file:.clang-format
}

function deactivate {
    export PS1=${PS1/"(sdk) "/}
    unset -f install_clang set_clang install_gcc set_gcc install_gtest install_cmake install_clang_format prepare build rebuild run format deactivate
}

export PS1="(sdk) $PS1"
