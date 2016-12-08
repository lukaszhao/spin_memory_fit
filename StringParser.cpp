#include "StringParser.h"
#include <iostream>


 std::vector<std::string>& StringParser::getResult(){
     size_t size = d_str.size();
     std::string str_temp = "";
     size_t i = 0;
     for(; i!=size; ++i){
        char c = d_str[i];
        if(d_delimiters.find(c)!=d_delimiters.end()){
            //this is a delimiter;
            if(str_temp.size()!=0){
                d_result.push_back(str_temp);
                str_temp = "";
                //std::cout<<"str_temp="<<str_temp<<"\n";
            }
        } else {
            //this is not a delimiter
            str_temp.push_back(c);
            //std::cout<<"str_temp="<<str_temp<<"\n";
        }
     }
     if(i == size){
        if(str_temp.size()!=0){
            d_result.push_back(str_temp);
            str_temp = "";
            //std::cout<<"str_temp="<<str_temp<<"\n";
        }
     }
     return d_result;
 }
