#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "MonoStack.h"

class SpeakerView
{
    private:
        double** heights;
        int rows;
        int cols;
    public:
        // Constructor: initializes the object and reads data from the file
    SpeakerView(const char* filename) : heights(nullptr), rows(0), cols(0) {
        readFile(filename);
    }

    // Destructor: frees dynamically allocated memory
    ~SpeakerView() {
        if (heights) {
            for (int i = 0; i < rows; ++i) {
                delete[] heights[i];
            }
            delete[] heights;
        }
    }

    void readFile(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file");
        }

        std::string line;
        std::getline(file, line); // Read "BEGIN"
        if (line != "BEGIN") {
            throw std::runtime_error("File format error: Expected 'BEGIN'");
        }

        // First pass: Count rows and determine number of columns
        while (std::getline(file, line) && line != "END") {
            if (rows == 0) {
                std::istringstream iss(line);
                double temp;
                while (iss >> temp) ++cols;
            }
            ++rows;
        }

        if (line != "END") {
            throw std::runtime_error("File format error: Expected 'END'");
        }

        // Allocate memory for heights array
        heights = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            heights[i] = new double[cols];
        }

        // Second pass: Reset file to beginning and read heights
        file.clear();
        file.seekg(0);
        std::getline(file, line); // Skip "BEGIN"
        for (int i = 0; i < rows; ++i) {
            std::getline(file, line);
            std::istringstream iss(line);
            for (int j = 0; j < cols; ++j) {
                iss >> heights[i][j];
            }
        }
    }

    void computeVisibility() {
        for(int col = 0; col < cols; ++col) //goes through each column
        {
            MonoStack<double> stack(rows, 'd'); // for each column a new montonically decreasing stack is created
            std::cout << "In column " << col << " there are "; //begin output

            int visibleCount = 0; //keeps track of how many people can see
            double* visible = new double[rows]; // new array to store heights of visible people

            for(int row = 0; row < rows; ++row) //goes through each row in current column
            {
                double height = heights[row][col]; // gets the height of the person at current position
                if(stack.isEmpty() || height > stack.peek()) // if the first person in the column is empty or they are taller than the last visible person(top of stack)
                {
                    stack.push(height); //add the persons height to the new stack
                    visible[visibleCount++] = height; //increment the visible count
                }
            }

            std::cout << visibleCount << " that can see. Their heights are: "; //prints number of visible people
            for(int i = 0; i < visibleCount; ++i)
            {
                std::cout << visible[i];
                if(i < visibleCount - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << " inches.\n";
            delete[] visible; //memory cleanup
        }
    }
};

#endif
