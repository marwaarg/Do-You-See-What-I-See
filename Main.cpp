#include "SpeakerView.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    //claude.ai for main
    try {
        SpeakerView view(argv[1]);
        view.computeVisibility();
    } catch (const std::exception& e) { 
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    //end claude.ai
    
    return 0;
}
