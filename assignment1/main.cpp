#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <chrono>

/**************************************************************************/

// get sub performs a-b in base B 
// ONLY WORKS WHEN A IS LARGER THAN B 
std::vector<int> getSub(std::vector<int> a, std::vector<int> b, int B){
    
    // first zero extend smaller vector 
    int diff = a.size() - b.size(); // difference in array sizes 
    if (diff > 0){ // a > b 
        b.insert(b.begin(), diff, 0);
    }
    
    // initialise resulting vector
    std::vector<int> sum (a.size(), 0);

    // calculate subtraction of arbitrary base. 
    int carry = 0;
    int temp = 0;
    for (int i = a.size() - 1 ; i >= 0 ; i--){
        temp = a.at(i) - b.at(i) - carry;
        
        if (temp < 0) {
            carry = 1; // borrow from the next higher digit
            temp += B; // adjust the current digit by adding base B
        } else {
            carry = 0;
        }

        sum.at(i) = temp;
    }

    // Remove leading zeros
    while (sum.size() > 1 && sum[0] == 0) {
        sum.erase(sum.begin());
    }

    return sum;
}


/**************************************************************************/

// Adds a to b in base B. 
// ONLY WORKS FOR POSITIVE NUMBERS
std::vector<int> getSum(std::vector<int> a, std::vector<int> b, int B){
    
    // first zero extend smaller vector 
    int diff = a.size() - b.size(); // difference in array sizes 
    if (diff > 0){ // a > b 
        b.insert(b.begin(), diff, 0);
    }
    else if (diff < 0){ // b > a
        a.insert(a.begin(), -diff, 0);
    }
    // initialise sum vector
    std::vector<int> sum (a.size()+1, 0);

    // calculate sum of arbitrary base. 
    int carry = 0;
    int temp = 0;
    for (int i = a.size() - 1 ; i >= 0 ; i--){
        temp = a.at(i) + b.at(i) + carry;
        
        carry = temp >= B ? 1 : 0; // carry = 1 if temp > B

        sum.at(i+1) = temp % B;
    }

    sum.at(0) = carry; // if we have a final carry in most significant digit 

    // Remove leading zeros
    while (sum.size() > 1 && sum[0] == 0) {
        sum.erase(sum.begin());
    }
    return sum;
}

/**************************************************************************/

// SCHOOL METHOD of multiplication for small numbers
std::vector<int> getProduct(std::vector<int> a, std::vector<int> b, int B){
 
    // first zero extend smaller vector 
    int diff = a.size() - b.size(); // difference in array sizes 
    if (diff > 0){ // a > b 
        b.insert(b.begin(), diff, 0);
    }
    else if (diff < 0){ // b > a
        a.insert(a.begin(), -diff, 0);
    }

    // for each element in b, multiply each digit in a 
    int carry = 0;
    int temp = 0;

    std::vector<std::vector<int> > vec (b.size() , std::vector<int>(a.size(), 0));
    for (int i = b.size() - 1 ; i >= 0 ; i--){
        for (int j = a.size() - 1 ; j >= 0 ; j--){
            temp = b.at(i) * a.at(j) + carry;
            vec.at(i).at(j) = temp % B;
            temp -= temp % B;
            carry = temp/B % B;       // THIS COULD BE WRONG 
        }
        // if we have a non zero carry at the front of a row 
        vec.at(i).insert(vec.at(i).begin(), 1, carry);
        carry = 0;
    }

    // now we need to zero extend our partial products 
    int count = 1;
    for (int i = b.size()-2 ; i >= 0 ; i--){
        vec.at(i).insert(vec.at(i).end() , count, 0);
        count++;
    }
    // Debugging outputs
    /*
    for (int i = 0 ; i < vec.size() ; i++){
        for (int j = 0 ; j < vec.at(i).size() ; j++){
            std::cout << vec.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    */

    // Now that we have our partial products we can sum everything up 
    std::vector<int> product = vec.at(0);
    for (int i = 1 ; i < b.size() ; i++){
        product = getSum(product, vec.at(i), B);
    }

    // tidy up leading zero 
    while (product.size() > 1 && product[0] == 0) {
        product.erase(product.begin());
    }
    return product;
}

/**************************************************************************/

std::vector<int> karatsuba(std::vector<int> a, std::vector<int> b, int B){
    // base case 
    if (a.size() < 3 || b.size() < 3){
        return getProduct(a,b,B);
    }
    // else we need to split the numbers up 
    // first zero extend smaller vector 
    int diff = a.size() - b.size(); // difference in array sizes 
    if (diff > 0){ // a > b 
        b.insert(b.begin(), diff, 0);
    }
    else if (diff < 0){ // b > a
        a.insert(a.begin(), -diff, 0);
    }
    
    
    int k = a.size()/2;
    int d = 0;
    if (a.size() - k != a.size()/2){ // if we have an odd number of digits 
        d = a.size() - k;
    }
    else {
        d = k;
    }

    std::vector<int> a1 (a.begin(), a.begin() + k);
    std::vector<int> a0 (a.begin() + k, a.end());
    std::vector<int> b1 (b.begin(), b.begin() + k);
    std::vector<int> b0 (b.begin() + k, b.end());

    // Debugging outputs
    /*
    std::cout << "a1: ";
    for (int num : a1) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "a0: ";
    for (int num : a0) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "b1: ";
    for (int num : b1) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "b0: ";
    for (int num : b0) std::cout << num << " ";
    std::cout << std::endl;
    */

    std::vector<int> P0 = karatsuba(a0,b0,B);  
    std::vector<int> P1 = karatsuba(a1,b1,B);
    std::vector<int> P2 = karatsuba(getSum(a1,a0,B), getSum(b1,b0,B), B);

    // Debugging outputs
    /*
    std::cout << "P0: ";
    for (int num : P0) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "P1: ";
    for (int num : P1) std::cout << num << " ";
    std::cout << std::endl;

    std::cout << "P2: ";
    for (int num : P2) std::cout << num << " ";
    std::cout << std::endl;
    */

    // calculate P2 - P1 - P0 
    std::vector<int> PS;
    PS = getSub(P2, P1, B);
    PS = getSub(PS, P0, B);

    // zero extend PS by d zeros 
    PS.insert(PS.end(), d, 0);

    // zero extend P1 by 2*d zeros 
    P1.insert(P1.end(), 2*d, 0);

    // add zero extended P1 to zero extended PS 
    P1 = getSum(P1,PS,B);

    // add all of this to P0 
    return getSum(P1,P0,B);
}

/**************************************************************************/

int main(void){
    // get the input 
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string I1, I2;
    int B;

    iss >> I1 >> I2 >> B;

    // put inputs into vector for ease of manipulation 

    std::vector<int> first;
    std::vector<int> second;

    for (int i = 0 ; i < I1.size() ; i++){
        if (I1.at(i) == '-'){
            first.push_back(-(I1.at(i+1)-48));
            i += 2;
        }
        else {
            first.push_back(I1.at(i)-48);
        }
        
    }
    for (int i = 0 ; i < I2.size() ; i++){
        if (I2.at(i) == '-'){
            second.push_back(-(I2.at(i+1)-48));
            i += 2;
        }
        else {
            second.push_back(I2.at(i)-48);
        }
    }

    // TESTING/OUTPUT
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> sum = getSum(first,second,B);
    std::vector<int> test = karatsuba(first,second, B);

    // Stop timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Print the result in microseconds
    // std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

    for (int i = 0 ; i < sum.size() ; i++){
        std::cout << sum.at(i);
    }
    std::cout << " ";

    for (int i = 0 ; i < test.size() ; i++){
        std::cout << test.at(i);
    }
    std::cout << " ";

    std::cout << 0 << std::endl;
    
    return 0;
}


