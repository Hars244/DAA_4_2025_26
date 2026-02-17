#include<iostream>
using namespace std;
int upperbound(int arr[],int left,int right,int target){
    if (left > right)
        return left;

    int mid = left + (right - left) / 2;
    if (arr[mid] > target)
        return upperbound(arr, left, mid -1 , target);
    else
        return upperbound(arr, mid + 1, right, target);
}
int lowerbound(int arr[],int left,int right,int target){
    if (left > right)
        return left;

    int mid = left + (right - left) /2;
    if (arr[mid] >= target)
        return lowerbound(arr, left, mid -1 , target);
    else
        return lowerbound(arr, mid + 1, right, target);
}
int main(){
    int n;
    cin >> n;

    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int target;
    cin >> target;

    int lb = lowerbound(arr, 0, n - 1, target);
    int ub = upperbound(arr, 0, n - 1, target);

    cout << "Count = " << ub - lb << endl;

    return 0;
}