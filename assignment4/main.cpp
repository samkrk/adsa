/* ADSA Assignment 4 - Implementation of Graph Algorithms */
/* Sam Kirk, 1851921                                      */

#include <iostream>
#include <vector>
#include <string>


int main(void){
    // get the input line 
    std::string inputLine;
    std::getline(std::cin, inputLine);

    std::cout << inputLine.size() << std::endl;
    int size = (inputLine.size() - 8) / 9;

    // seperate the input into the three matricies
    std::vector<std::vector<int> > country(size, std::vector<int>(size,0));
    std::vector<std::vector<int> > build(size, std::vector<int>(size,0));
    std::vector<std::vector<int> > destroy(size, std::vector<int>(size,0));
    
    int matrix_index = 0;
    int row_index = 0;
    int index = 0;
    for (int i = 0 ; i < inputLine.size() ; i++){
        if (inputLine.at(i) == ' '){
            matrix_index++;
            row_index = 0;
            index = 0;
            continue;
        } else if (inputLine.at(i) == ','){
            row_index++;
            index = 0;
        } else {
            switch (matrix_index)
            {
            case 0:
                country.at(row_index).at(index) = inputLine.at(i) - '0';
                index++;
                break;
            case 1:                
                build.at(row_index).at(index) = inputLine.at(i) - 'A';
                index++;
                break;
            case 2:
                destroy.at(row_index).at(index) = inputLine.at(i) - 'A';
                index++;
            default:
                break;
            }
        }

    }
    
    // debug print 
    for (int i = 0 ; i < country.size() ; i++){
        for (int j = 0 ; j < country.at(i).size() ; j++){
            std::cout << country.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0 ; i < build.size() ; i++){
        for (int j = 0 ; j < build.at(i).size() ; j++){
            std::cout << build.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0 ; i < destroy.size() ; i++){
        for (int j = 0 ; j < destroy.at(i).size() ; j++){
            std::cout << destroy.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
        
    return 0;

}
