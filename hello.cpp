#include <bits/stdc++.h>
using namespace std;

void solve_last_segment(bool,&ul,bool paragraph){
    if(ul){
        cout<<"</ul>"<<endl;
        ul = false;
    }
    if(paragraph){
        cout<<"</p>"<<endl;
        paragraph = false;
    }
}

string getHTML(string unsigned int start ,unsigned int end){
    string ans = "";
    unsigned int index = start;
    unsigned int s1,s2;
    string link = "";
    string text = "";
    while (index < end){
        switch(str[index]){
            case '_':
               index++;
               s1 = index;
               while (index , end && str[index] != '_'){
                  index++;
               }
               s2 = index;
               index++;
               ans += "<em>" + getHTML(str,s1,s2) + "</em>"<<endl;
               break;
            case '[' :
                index++;
                s1 = index;
                while (index < end && str[index] != ']')
        }
    }
}