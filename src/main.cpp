#include <iostream>
#include "../include/Image.h"


void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <input_file> <output_file> <filter_name>" << std::endl;
    std::cerr << "Available filters: grayscale, invert, blur" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage(argv[0]);
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string filter_name = argv[3];

    Image image;
    std::cout << "Uploading Image from " << input_file << "..." << std::endl;
    if (!image.load(input_file)) {
        return 1;
    }
    std::cout << "Image uploaded with success." << std::endl;

    std::cout << "Applying filter " << filter_name << "..." << std::endl;
    if (filter_name == "grayscale") {
        image.applyGrayScale();
    } else if (filter_name == "invert") {
        image.applyInvert();
    } else if (filter_name == "blur") {
        image.applyBlur();
    } else {
        std::cout << "Error: Filter: " << filter_name << "doesn't exist." << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    std::cout << "Filter applied" << std::endl;

    std::cout << "Saving image at " << output_file << "..." << std::endl;
    if (!image.save(output_file)) {
        return 1;
    }

    std::cout << "Image processed and saved with success!" << std::endl;

    return 0;
}
