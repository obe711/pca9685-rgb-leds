# _PCA9685 RGB LEDS_

PCA9685 RGB led library for ESP32 (ESP-IDF)

## Folder contents

The project **pca9685-rgb-leds** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components/ (https://github.com/UncleRus/esp-idf-lib)
├── main
│   ├── CMakeLists.txt
│   ├── pca9685_leds.h - header file for PCA9685 RGB LEDS
│   └── main.c - example & test program
└── README.md                  This is the file you are currently reading
```

Additionally, the pca9685-rgb-leds contains Makefile and component.mk files, used for the legacy Make based build system.
They are not used or needed when building with CMake and idf.py.

## Links

[esp-idf-lib](https://esp-idf-lib.readthedocs.io/en/latest/groups/pca9685.html)
