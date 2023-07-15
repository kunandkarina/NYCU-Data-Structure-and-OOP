#include <iostream>
#include <vector>

using namespace std;

class quick{
public:
    quick(vector<int> v_): v(v_){}

    vector<int> sort(){
        quick_sort_partation(0, v.size()-1, v.size());
        return v;
    }

    vector<int> sort_print(){
        quick_sort_partation_print(0, v.size()-1, v.size());
        return v;
    }

    void quick_sort_partation_print(int start, int end, int len){
        if(start < end){
            int pivot = partition(start, end);
            cout << start << "~" << end << ":" << endl;
            print_v();

            quick_sort_partation_print(start, pivot - 1, len);

            quick_sort_partation_print(pivot + 1, end, len);
        }
        return;
    }

    void quick_sort_partation(int start, int end, int len){
        if(start < end){
            int pivot = partition(start, end);

            quick_sort_partation(start, pivot - 1, len);

            quick_sort_partation(pivot + 1, end, len);
        }
        return;
    }
    int partition(int start, int end){
        int pivot = v[start];

        int cnt = 0;
        for (int i = start + 1; i <= end; i++) {
            if (v[i] <= pivot)
                cnt++;
        }
        int pivotIndex = start + cnt;
        swap(v[pivotIndex], v[start]);
        int i = start, j = end;
        while (i < pivotIndex && j > pivotIndex) {
            while (v[i] <= pivot) {
                i++;
            }
            while (v[j] > pivot) {
                j--;
            }
            if (i < pivotIndex && j > pivotIndex) {
                swap(v[i++], v[j--]);
            }
        }
        return pivotIndex;
    }
    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << endl;
    }

public:
    vector<int> v;
};
