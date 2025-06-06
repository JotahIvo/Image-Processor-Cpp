#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>

struct Pixel {
    unsigned char r, g, b;

    Pixel() : r(0), g(0), b(0) {}

    Pixel(unsigned char red, unsigned char green, unsigned char blue) : r(red), g(green), b(blue) {} 
};

class Image {
    private:
        int m_width, m_height;
        std::vector<Pixel> m_pixel_data;

    public:
        Image() : m_width(0), m_height(0) {}

        bool load(const std::string& filename);

        bool save(const std::string& filename) const;

        int getWidth() const {
            return this->m_width;
        }

        int getHeight() const {
            return this->m_height;
        }
};

#endif