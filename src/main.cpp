#include <iostream>
#include "../include/Image.h"


int main() {
    Image minhaImagem;

    if (minhaImagem.load("images/imagem1.ppm")) {
        std::cout << "Arquivo de imagem carregado com sucesso." << std::endl;

        if (minhaImagem.save("images/output_copia.ppm")) {
            std::cout << "Imagem copiada e salva com sucesso em 'output_copia.ppm'." << std::endl;
        } else {
            std::cerr << "Falha ao salvar a imagem." << std::endl;
        }
    } else {
        std::cerr << "Falha ao carregar a imagem." << std::endl;
        return 1; 
    }

    return 0;
}
