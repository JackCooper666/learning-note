#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class sortbyheap{
    public:
    sortbyheap(vector<int> temp){
        for(auto val:temp){
            minPQ.push(val);
        }
        // sortres.resize(temp.size());
    }

    void prindpriorityqueue(){
        int n = minPQ.size();
        for(int i = 0; i < n; i++){
            cout << "top " << i << "-"<< minPQ.top() << "|";
            minPQ.pop();
        }
        cout << endl;
    }
    void heapdown(vector<int> &arr, int n, int i){
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        if(left < n && arr[left] > arr[largest]) largest = left;
        if(right < n && arr[right] > arr[largest]) largest = right;
        if(largest != i){
            swap(arr[i], arr[largest]);
            heapdown(arr, n, largest);
        }
    }

    // vector<int> sortres;
    vector<int> heapsort(vector<int> temp){
        int n = temp.size();
        vector<int> res;
        res.resize(n);
        res = temp;

        for(int i = n/2 - 1; i >= 0; --i){
            heapdown(res,n,i);
        }

        for(int i = n - 1; i > 0; --i){
            swap(res[0], res[i]);
            heapdown(res,i,0);
        }
        return res;
    }


    private:
    priority_queue<int,vector<int>,greater<int>> minPQ;

};

int main(){
    vector<int> temp = {0,2,5,3,1,2,4};
    sortbyheap hs(temp);
    hs.prindpriorityqueue();
    vector<int> res = hs.heapsort(temp);
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}