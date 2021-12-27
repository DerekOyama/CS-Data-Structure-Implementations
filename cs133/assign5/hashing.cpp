#include <cstdint>
#include <boost/math/distributions/chi_squared.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <type_traits>
#include <math.h>

double frac(double f)
{
    double i;
    return modf(f, &i);
}
unsigned char char_to_unsigned(char c)
{
    return static_cast<std::make_unsigned<char>::type>(c);
}

std::vector<int> hash(int i, std::vector<std::string> &words)
{
    std::vector<int> hashes;
    hashes.resize(65536, 0);
    if (i == 0)
    {
        for (std::string word : words)
        {
            hashes.at(word.length())++;
        }
        return hashes;
    }
    else if (i == 1)
    {
        for (std::string word : words)
        {
            hashes.at(char_to_unsigned(word.at(0)))++;
        }
        return hashes;
    }
    else if (i == 2)
    {
        uint16_t ans = 0.0;
        for (std::string word : words)
        {
            for (int i = 0; i < word.length(); i++)
            {
                ans += char_to_unsigned(word.at(i));
            }
            hashes.at(ans)++;
            ans = 0.0;
        }
        return hashes;
    }
    else if (i == 3) //remainder
    {
        for (std::string word : words)
        {
            uint16_t ans = 0.0;
            for (char c : word)
            {
                ans = (ans * 256 + char_to_unsigned(c)) % 65413;
            }
            hashes[ans]++;
            ans = 0.0;
        }
        return hashes;
    }
    else if (i == 4) //multiplicative
    {
        double ans = 0.0;
        double A = (sqrt(5) - 1) / 2;
        for (std::string word : words)
        {
            for (int i = 0; i < word.length(); i++)
            {
                ans = frac(A * (ans * 256 + char_to_unsigned(word.at(i))));
            }
            hashes[(uint16_t)(ans * 65536)]++;
            ans = 0.0;
        }
        return hashes;
    }

    return hashes;
}

void print(std::vector<int> &a)
{
    //partition vector into 10x10
    //every # represents 10% of hashes
    //find which sections have how many hashes
    //print the #s
    int max = 99171;
    int partitions = 80;
    std::vector<int> h; //h has partitioned total hashes in 10 sections
    for (int i = 0; i < partitions; i++)
    {
        h.push_back(0);
    }
    int counter = 0;
    for (int i = 0; i < a.size(); i++) //load 10 sections of hash table into array
    {                                  //determine which partition we are in, if that partition has enough to put a # in, put it in
        //for the first 6553, put it into h(1)
        //0-6553
        counter += a.at(i);
        if (counter >= max / partitions)
        {
            if (i / (65536/partitions) == 30)
            {
                h.at(partitions -1)++;
            }
            else
            {
                h.at(i / (65536/partitions))++;
            }
            counter = 0;
        }
    }                            //divide each section by a.size / 10;
    std::vector<int> temp(10);
    for(int i = 0; i < partitions; i++) 
    {
         temp.at(i/(partitions / 10)) += h.at(i);
    }
    h = temp;
    for (int i = 10; i > 0; i--) //create height of histogram
    {
        for (int j = 0; j < 10; j++) //print sideways
        {
            if (h.at(j) >= i) // if it has 1/10 of hashes , print #
            {
                std::cout << "# ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
    for (int i = 0; i < 10; i++) //create base of graph
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "\n";
}

int main()
{

    //uint16_t x  x has exactly 16 bits, and is unsigned
    std::string y;

    std::vector<std::string> words;
    for (int i = 0; i < 5; i++)
    {
        int num_words = 0;

        std::fstream data;
        data.open("words", std::ios::in | std::ios::out); //make word reader

        if (data.is_open()) //checking whether the file is open
        {
            while (getline(data, y)) //get word
            {
                num_words++;        //update total of words
                words.push_back(y); //increment hash position
            }
            data.close(); //close the file object.
        }

        data.close();

        float expected = (double)num_words / 65536.0;
        float c2 = 0.0;
        float p = 0.0;
        std::vector<int> hashes = hash(i, words);
        print(hashes);
        for (int hash : hashes) //create c2
        {
            c2 += ((expected - hash) * (expected - hash)) / expected;
        }

        boost::math::chi_squared c2d(65535.0); //make & print p
        p = boost::math::cdf(c2d, c2);
        switch (i)
        {
        case 0:
            std::cout << "p for test String length: " << p << "\n";
            break;
        case 1:
            std::cout << "p for test First Char: " << p << "\n";
            break;
        case 2:
            std::cout << "p for test Additive Checksum: " << p << "\n";
            break;
        case 3:
            std::cout << "p for test Remainder: " << p << "\n";
            break;
        case 4:
            std::cout << "p for test Multiplicative: " << p << "\n";
            break;
        }
        words.clear();
    }
}
