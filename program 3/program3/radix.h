#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class radix{
public:
    radix(vector<int> v_) : v(v_){};

    vector<int> sort(){
        int m = getMax();
        vector<int> arr[10];
        for(int r=1;m/r>0;r*=10){
            for(int i=0;i<v.size();i++){
                for(int j=0;j<10;j++){
                    int temp = (v[i]/r)%10;
                    if(temp==j) arr[j].push_back(v[i]);
                }
            }
            int s=0;
            for(int i=0;i<10;i++){
                for(int j=0;j<arr[i].size();j++){
                    v[s] = arr[i][j];
                    s++;
                }
            }
            for(int i=0;i<10;i++){
                arr[i].clear();
            }
        }
        return v;
    }

    vector<int> sort_print(){
        int m = getMax();
        vector<int> arr[10];
        int count = 1;
        for(int r=1;m/r>0;r*=10){
            if(count==1) cout << "First-pass:" <<  endl;
            else if(count==2) cout << "Second-pass:" << endl;
            else cout << "Third-pass:" << endl;
            count++;
            for(int i=0;i<v.size();i++){
                for(int j=0;j<10;j++){
                    int temp = (v[i]/r)%10;
                    if(temp==j) arr[j].push_back(v[i]);
                }
            }
            int s=0;
            for(int i=0;i<10;i++){
                for(int j=0;j<arr[i].size();j++){
                    v[s] = arr[i][j];
                    s++;
                }
            }
            for(int i=0;i<10;i++){
                cout << i << " " << "|";
                for(int j=0;j<arr[i].size();j++){
                    cout << " " << "-->" << " " << arr[i][j];
                }
                cout << endl;
            }
            for(int i=0;i<10;i++){
                arr[i].clear();
            }
            cout << "resulting chain : ";
            for(int i=0;i<v.size();i++){
                cout << v[i] << ",";
            }
            cout << endl;
        }
            return v;
    }

    int getMax(){
        int max = v[0];
        for(int i=0;i<v.size();i++){
            if(v[i]>max) max = v[i];
        }
        return max;
    }

    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << endl;
    }

public:
    vector<int> v;
    // maybe ?
};
