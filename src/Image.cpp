#include "../include/Image.h"
#include <fstream>   
#include <iostream>  
#include <sstream>
#include <limits>
#include <array>


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


void Image::applyGrayScale() {
    for (Pixel& pixel : m_pixel_data) {
        float r_original = pixel.r;
        float g_original = pixel.g;
        float b_original = pixel.b;

        float gray_value = (0.299f * r_original) + (0.587f * g_original) + (0.114f * b_original);

        unsigned char final_gray = static_cast<unsigned char>(gray_value);

        pixel.r = final_gray;
        pixel.g = final_gray;
        pixel.b = final_gray;
    }
}


void Image::applyInvert() {
    for (Pixel& pixel : m_pixel_data) {
        float r_original = pixel.r;
        float g_original = pixel.g;
        float b_original = pixel.b;

        float new_r = 255 - r_original;
        float new_g = 255 - g_original;
        float new_b = 255 - b_original;

        pixel.r = static_cast<unsigned char>(new_r);
        pixel.g = static_cast<unsigned char>(new_g);
        pixel.b = static_cast<unsigned char>(new_b);
    }
}


void Image::applyBlur() {
    std::vector<Pixel> blurred_pixel_data(m_width * m_height);

    float kernel_values[9] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int idx = getPixelIndex(x, y);
            if (y == 0 || x == 0 || x == m_width-1 || y == m_height-1) {
                blurred_pixel_data[idx].r = 0;
                blurred_pixel_data[idx].g = 0;
                blurred_pixel_data[idx].b = 0;
            } else {
                float r_sum = 0.0f;
                float g_sum = 0.0f;
                float b_sum = 0.0f;
                int count = 0;
                for (int i = x-1; i < x+2; i++) {
                    for (int j = y-1; j < y+2; j++) {
                        int index = getPixelIndex(i, j);
                        r_sum += m_pixel_data[index].r * kernel_values[count];
                        g_sum += m_pixel_data[index].g * kernel_values[count];
                        b_sum += m_pixel_data[index].b * kernel_values[count];
                        count++;
                    }
                }

                blurred_pixel_data[idx].r = static_cast<unsigned char>(r_sum);
                blurred_pixel_data[idx].g = static_cast<unsigned char>(g_sum);
                blurred_pixel_data[idx].b = static_cast<unsigned char>(b_sum);
            }
        }
    }

    m_pixel_data = blurred_pixel_data;
}
