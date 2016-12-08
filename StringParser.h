#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <string>
#include <vector>
#include <unordered_set>

class StringParser
{
    private:
        std::string d_str;
        std::unordered_set<char> d_delimiters;
        std::vector<std::string> d_result;


    public:
        StringParser(){
            d_delimiters.insert(',');
            d_delimiters.insert(' ');
            d_delimiters.insert('\t');
            d_delimiters.insert(';');
        };

        StringParser(char delimiter){
            d_delimiters.insert(delimiter);
        }

        StringParser(char delimiter1, char delimiter2){
            d_delimiters.insert(delimiter1);
            if(delimiter2 != delimiter1) d_delimiters.insert(delimiter2);
        }

        virtual ~StringParser(){};

        void setString(const std::string& str){
            d_str = str;
            d_result.clear();
        }

        std::vector<std::string>& getResult();
};

#endif // STRINGPARSER_H
