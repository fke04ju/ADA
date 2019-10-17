#include <iostream>
#include <cstdio>
#define MAXN 500050

using namespace std;

long long int array[MAXN];
long long int preprocessing_max[MAXN];
long long int preprocessing_min[MAXN];
long long int count[2*MAXN];
long long int sum = 0;

void max_left_min_left(long long int left,long long int mid,long long int right){
    long long int tmp_max = array[mid];
    long long int tmp_min = array[mid];
    long long int j;
    for(long long int i = mid;i>=left;i--){
        if(tmp_max < array[i]){
            tmp_max = array[i];
        }
        if(tmp_min > array[i]){
            tmp_min = array[i];
        }
        j = tmp_max - tmp_min + i;
        if(j <= right && j > mid && preprocessing_max[j] < tmp_max && preprocessing_min[j] > tmp_min){
            sum++;
        }
    }
    return;
}

void max_right_min_right(long long int left,long long int mid,long long int right){
    long long int tmp_max = array[mid+1];
    long long int tmp_min = array[mid+1];
    long long int j;
    for(long long int i = mid+1;i<=right;i++){
        if(tmp_max < array[i]){
            tmp_max = array[i];
        }
        if(tmp_min > array[i]){
            tmp_min = array[i];
        }
        j = i - tmp_max + tmp_min;
        if(j <= mid && j >= left && preprocessing_max[j] < tmp_max && preprocessing_min[j] > tmp_min){
            sum++;
        }
    }
    return;
}

void max_left_min_right(long long int left,long long int mid,long long int right){
    for(long long int i = mid+1;i<=right;i++){
        count[i+preprocessing_min[i]] = 0;
    }
    for(long long int i = mid;i>=left;i--){
        count[i+preprocessing_max[i]] = 0;
    }
    long long int l_ptr = mid+1;
    long long int r_ptr = mid+1;
    for(long long int j = mid;j>=left;--j){
        while(r_ptr <= right && preprocessing_max[r_ptr] < preprocessing_max[j]){
            count[preprocessing_min[r_ptr]+r_ptr]++;
            r_ptr++;
        }
        while(l_ptr <= right && preprocessing_min[l_ptr] > preprocessing_min[j]){
            count[preprocessing_min[l_ptr]+l_ptr]--;
            l_ptr++;
        }
        if(r_ptr > l_ptr){
            sum += count[j+preprocessing_max[j]];
        }
    }
    return;
}

void max_right_min_left(long long int left,long long int mid,long long int right){  
    for(long long int i = left;i<=mid;i++){
        count[preprocessing_min[i]-i+MAXN] = 0;
    }
    for(long long int i = mid+1;i<=right;i++){
        count[preprocessing_max[i]-i+MAXN] = 0;
    }
    //max-j = min-i
    long long int l_ptr = mid;
    long long int r_ptr = mid;
    for(long long int j = mid+1;j<=right;++j){
        while(r_ptr >= left && preprocessing_min[r_ptr] > preprocessing_min[j]){
            count[preprocessing_min[r_ptr]-r_ptr+MAXN]--;
            r_ptr--;
        }
        while(l_ptr >= left && preprocessing_max[l_ptr] < preprocessing_max[j]){
            count[preprocessing_min[l_ptr]-l_ptr+MAXN]++;
            l_ptr--;
        }
        if(l_ptr < r_ptr){
            sum += count[preprocessing_max[j]-j+MAXN];
        }
    }
    return;
}

void devide_and_conquer(long long int left,long long int right){
    if(left == right){
        sum++;
        return;
    }
    long long int mid = (left+right)/2;
    long long int tmp_min = array[mid];
    long long int tmp_max = array[mid];
    for(long long int i = mid;i>=left;i--){
        if(tmp_min > array[i]){
            tmp_min = array[i];
        }
        if(tmp_max < array[i]){
            tmp_max = array[i];
        }
        preprocessing_min[i] = tmp_min;
        preprocessing_max[i] = tmp_max;
    }
    tmp_min = array[mid+1];
    tmp_max = array[mid+1];
    for(long long int i = mid+1;i<=right;i++){
        if(tmp_max < array[i]){
            tmp_max = array[i];
        }
        if(tmp_min > array[i]){
            tmp_min = array[i];
        }
        preprocessing_max[i] = tmp_max;
        preprocessing_min[i] = tmp_min;
    }
    max_left_min_left(left,mid,right);
    max_right_min_right(left,mid,right);
    max_left_min_right(left,mid,right);
    max_right_min_left(left,mid,right);
    devide_and_conquer(left,mid);
    devide_and_conquer(mid+1,right);
    return;
}

int main(){
    long long int n;
    cin >> n;
    for(long long int i = 0;i<n;++i){
        cin >> array[i];
    }
    devide_and_conquer(0,n-1);
    cout << sum << endl;
}