#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Heap_constructor {
    public:
    vector<int> heapify_up(const vector<int>& data, string type);
    vector<int> heapify_down(const vector<int>& data, string type);
    void heapify_down_build(vector<int> &heap,int i, int n, string type);
};

vector<int> Heap_constructor::heapify_up(const vector<int>& data, string type) {
    if(data.empty()) return {};
    if(type == "max_heap"){
        vector<int> heap;
        for(auto node:data){
            heap.push_back(node);
            int i = heap.size() - 1;
            while(i > 0 && heap[i] > heap[(i - 1)/2]){
                swap(heap[i], heap[(i - 1)/2]);
                i = (i - 1) / 2;
            }
        }
        return heap;
    }
    else if(type == "min_heap"){
        vector<int> heap;
        for(auto node:data){
            heap.push_back(node);
            int i = heap.size() - 1;
            while(i > 0 && heap[i] < heap[(i - 1)/2]){
                swap(heap[i],heap[(i - 1)/2]);
                i = (i - 1)/2;
            }
        }
        return heap;
    }
    else {
        cout << "Invalid heap type specified." << endl;
        return {};
    }
}

vector<int> Heap_constructor::heapify_down(const vector<int>& data, string type){
    int n = data.size();
    vector<int> heap;
    heap = data;
    for(int i = n/2 - 1; i >= 0; --i){
        heapify_down_build(heap,i,n,type);
    }
    return heap;
}

void Heap_constructor::heapify_down_build(vector<int> &heap,int i, int n, string type){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(type == "max_heap"){
        if(left < n && heap[largest] < heap[left]) largest = left;
        if(right < n && heap[largest] < heap[right]) largest = right;
    }
    else if(type == "min_heap"){
        if(left < n && heap[largest] > heap[left]) largest = left;
        if(right < n && heap[largest] > heap[right]) largest = right;        
    }
    else{
        ;
    }

    if(largest != i){
        swap(heap[i],heap[largest]);
        heapify_down_build(heap,largest,n,type);
    }
}

int main(){
    vector<int> heap_res;
    vector<int> heap_input = {4,5,7,1,8};
    heap_res.resize(heap_input.size());

    Heap_constructor constructor;
    heap_res = constructor.heapify_up(heap_input,"max_heap");
    cout<<"max heap, heapify up"<< endl;
    for(int i = 0; i < heap_res.size(); i++){
        cout << heap_res[i] << " ";
    }
    cout << endl;
    
    heap_res.clear();
    heap_res.resize(heap_input.size());
    heap_res = constructor.heapify_up(heap_input,"min_heap");
    cout<<"min heap, heapify up"<< endl;
    for(int i = 0; i < heap_res.size(); i++){
        cout << heap_res[i] << " ";
    }
    cout << endl;

    heap_res.clear();
    heap_res.resize(heap_input.size());
    heap_res = constructor.heapify_down(heap_input,"max_heap");
    cout << "max heap, heapify down" << endl;
    for(int i = 0; i < heap_res.size();i++){
        cout << heap_res[i] << " ";
    }
    cout << endl;

    heap_res.clear();
    heap_res.resize(heap_input.size());
    heap_res = constructor.heapify_down(heap_input,"min_heap");
    cout << "min heap, heapify down" << endl;
    for(int i = 0; i < heap_res.size();i++){
        cout << heap_res[i] << " ";
    }
    cout << endl;
    return 0;
}