# Simple C++ Image Processor

A command-line image processing tool built with modern C++. This project serves as a practical exercise for learning and applying core C++ concepts, including Object-Oriented Programming (OOP), the Standard Template Library (STL), file I/O, and project management with CMake.

The application can load an image in the simple PPM (Portable Pixmap) format, apply various filters, and save the resulting image.

## Features

* **Grayscale Conversion:** Converts a color image to shades of gray using a luminosity-preserving weighted average.
* **Color Inversion:** Inverts the colors of the image, creating a "photo negative" effect.
* **Gaussian Blur:** Softens the image by applying a 3x3 convolution kernel, blending each pixel with its neighbors.
* **Command-Line Interface:** Easy to use and scriptable.
* **Cross-Platform Build System:** Uses CMake for easy compilation on Linux, macOS, and Windows.

## Requirements

To build and run this project, you will need:

* A C++17 compliant compiler (e.g., GCC, Clang, MSVC).
* [CMake](https://cmake.org/download/) (version 3.10 or higher).
* A build tool like `make`, `Ninja`, or Visual Studio.

## How to Build and Run

Follow these steps from your terminal:

**1. Clone the Repository**

```bash
# Replace with your actual repository URL
git clone [https://github.com/your-username/ImageProcessor.git](https://github.com/your-username/ImageProcessor.git)
cd ImageProcessor
```

**2. Configure the Project with CMake**

This step generates the native build files (e.g., Makefiles on Linux/macOS or a Visual Studio solution on Windows) in a `build` directory. You only need to do this once, or after changing `CMakeLists.txt`.

```bash
# From the project's root directory
cmake -S . -B build
```

**3. Compile the Project**

This step compiles your C++ source code into an executable. Run this command every time you make changes to your `.h` or `.cpp` files.

```bash
# From the project's root directory
cmake --build build
```
The executable, named `processor`, will be created inside the `build` directory.

**4. Run the Application**

The program is a command-line tool. Use it as follows:

**Usage:**
```
./build/processor <input_file> <output_file> <filter_name>
```

**Available Filters:**
* `grayscale`
* `invert`
* `blur`

**Examples:**
```bash
# Apply the grayscale filter
./build/processor images/input.ppm images/output_grayscale.ppm grayscale

# Apply the blur filter
./build->/build/processor images/input.ppm images/output_blur.ppm blur
```

After running, check the `images` folder for your new output files!

## Project Structure

The project is organized as follows:

```
ProcessadorDeImagem/
├── build/                # Build files are generated here
├── images/               # Sample input/output images
├── include/              # Header files (.h)
│   └── Image.h
├── src/                  # Source files (.cpp)
│   ├── Image.cpp
│   └── main.cpp
└── CMakeLists.txt        # The heart of the build system
```

## Supported Image Format

This tool currently supports the **PPM (Portable Pixmap) P3 format**, which is a simple, text-based image format. This makes it easy to create and inspect test images manually.

A PPM P3 file looks like this:
```ppm
P3
# Optional comment
width height
max_color_value
R1 G1 B1  R2 G2 B2 ...
...
```

## Future Work

This project can be extended in many ways:

* **Add More Filters:** Implement other convolution kernels like Sharpen, Emboss, or Sobel/Prewitt for edge detection.
* **Support More Image Formats:** Integrate a simple, single-header library like [stb_image.h](https://github.com/nothings/stb) to load and save common formats like PNG and JPG.
* **Filter Parameters:** Allow filters to take arguments from the command line (e.g., `./build/processor ... blur 5` for a larger blur radius).
* **Performance Optimization:** Profile the code and explore performance improvements, such as multi-threading for applying filters. This is a great stepping stone towards GPU programming with CUDA.