# TP 8: Transformations

## 1. Objective

The objective of this TP is to learn how to use transformations in OpenGL.

## 2. Requirements

### 2.1 Software

#### GLFW

GLFW is a library that allows the creation of windows, OpenGL contexts and the handling of input and events. It is available for Windows, Linux and Mac OS X and is licensed under the zlib/libpng license.

For macOS, GLFW is available through Homebrew:

```bash
brew install glfw
```

#### GLAD

GLAD is a library that loads OpenGL functions at runtime. It is available for Windows, Linux, Mac OS X, and BSD systems. It is licensed under the MIT license.

GLAD requires a loader to load OpenGL functions at runtime. GLFW, SDL, SFML, and other similar libraries provide loaders for OpenGL functions. However, GLAD provides its own loader, which is what we will use in this TP.

To generate the loader, go to the [GLAD](https://glad.dav1d.de/) website and configure it as follows:

- Language: C/C++
- Specification: OpenGL
- API: gl Version 3.3
- Profile: Core

Then click on ``Generate`` and download the zip file. Unzip the file and copy the include folder and the src folder to the project folder.

## 3. Seting up Visual Studio Code

### 3.1 Install the C/C++ extension

The C/C++ extension adds language support for C/C++ to Visual Studio Code, including features such as IntelliSense and debugging.

### 3.2 Cofiguration files

The tasks.json file is used to build and run the program. It is located in the .vscode folder.

Following this YouTube video [link](https://youtu.be/7-dL6a5_B3I?si=H1uGXRxoTELzBd2d), configure the tasks.json file, and the dependencies folder.
