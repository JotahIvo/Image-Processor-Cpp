#include "../include/Image.h"
#include <fstream>   
#include <iostream>  
#include <sstream>
#include <limits>


bool Image::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Can't open the file " << filename << std::endl;
        return false; 
    }

    std::string magic_number;
    file >> magic_number;

    if (magic_number != "P3") {
        std::cerr << "Error: Invalid file format" << std::endl;
        return false;
    }

    auto ignore_comments_and_spaces = [&]() {
        while (isspace(file.peek())) {
            file.get();
        }
        while (file.peek() == '#') {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (isspace(file.peek())) {
                file.get();
            }
        }
    };

    int max_color_value;

    ignore_comments_and_spaces();
    file >> m_width;
    ignore_comments_and_spaces();
    file >> m_height;
    ignore_comments_and_spaces();
    file >> max_color_value;

    if (!file) {
        std::cerr << "Error: Impossible to read dimensions or max color value" << std::endl;
        return false;
    }

    m_pixel_data.resize(m_width * m_height);

    int r, g, b;
    for (int i = 0; i < m_width * m_height; i++) {
        if (!(file >> r >> g >> b)) {
            std::cerr << "Error: Image file looks crashed or incompleted" << std::endl;
            return false;
        }
        m_pixel_data[i].r = static_cast<unsigned char>(r);
        m_pixel_data[i].g = static_cast<unsigned char>(g);
        m_pixel_data[i].b = static_cast<unsigned char>(b); 
    }

    std::cout << "Image: " << filename << " loaded with success (" << m_width << "x" << m_height << ")." << std::endl;
    file.close();
    return true;
}


bool Image::save(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Can't open or create the file " << filename << std::endl;
        return false;
    }

    file << "P3\n";
    file << m_width << " " << m_height << "\n";
    file << "255\n";

    for (const Pixel& pixel : m_pixel_data) {
        file << static_cast<int>(pixel.r) << " " << static_cast<int>(pixel.g) << " " << static_cast<int>(pixel.b) << "\n";
    }

    return true;
}
