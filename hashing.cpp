#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, int> Question_1(vector<int> q1, int x){
    map<int,int> result_map;
    
    //Populate map with 'null' values (-1)
    for(int i = 0; i < x; i++){
        result_map[i] = -1;
    }

    //Place values into map
    for(unsigned i = 0; i < q1.size(); i++){
        int add = 0;

        //Progresses if the current location is already populated
        while(result_map[(q1.at(i) + add)%x] != -1){
            add += 1;
        }

        //Place value into hash table
        result_map[(q1.at(i) + add)%x] = q1.at(i);
    }

    return result_map;
}

map<int, int> Question_2(vector<int> q1, int x){
    map<int,int> result_map;

    //Populate map with 'null' values (-1)
    for(int i = 0; i < x; i++){
        result_map[i] = -1;
    }

    //Place values into map
    for(unsigned i = 0; i < q1.size(); i++){
        int add = 0;

        //Progresses if the current location is already populated
        while(result_map[(q1.at(i) + add + 2*(add*add)) % x] != -1){//wrong
            add += 1;
        }

        //Place value into hash table
        result_map[(q1.at(i) + add + 2*(add*add)) % x] = q1.at(i);
    }


    return result_map;
}

map<int, int> Question_3(vector<int> q1, int x){
    map<int,int> result_map;

    //Populate map with 'null' values (-1)
    for(int i = 0; i < x; i++){
        result_map[i] = -1;
    }

    //Place values into map
    for(unsigned i = 0; i < q1.size(); i++){
        int add = 0;

        //Calculate sum of digits
        int sum = 0;
        int a = q1.at(i);
        while(a > 0){
            sum += a % 10;
            a = x/10;
        }

        //Progresses if the current location is already populated
        while(result_map[(q1.at(i) + (add * sum)) % x] != -1){//wrong
            add += 1;
            
        }

        //Place value into hash table
        result_map[(q1.at(i) + (add * sum)) % x] = q1.at(i);
    }

    return result_map;
}


int main(int argc, char **argv){
    //Intialize input vector and output map
    vector<int> input{};
    map<int,int> output;

    for(int i = 0; i < argc; i++){
        input.push_back(atoi(argv[i]));
    }

    input.erase(input.begin());

    //Q1 output
    output = Question_1(input, argc+1);
    for(auto i: output){
        cout << i.second << " ";
    }
    cout << endl;

    //Q2 output
    output = Question_2(input, argc+1);
    for(auto i: output){
        cout << i.second << " ";
    }
    cout << endl;

    //Q3 output
    output = Question_3(input, argc+1);
    for(auto i: output){
        cout << i.second << " ";
    }
    cout << endl;
}