/*************************************************************************/
/*                           15 ADA Meetup                               */
/*                 Recent : 2019.09.27 11:28:43 UTF+8                    */
/*               First AC : 2019.09.27 10:51:42 UTF+8                    */
/*                         Points : 100/100                              */
/*                         Runtime : 2.652s                              */
/*************************************************************************/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;
long long N;
long long taste[1000010];
long long tolerant[1000010];
long long counting = 0;
long long newarr[1000010];
long long c;
inline long long Read() {
	char c;
	long long ans = 0;
	bool Sign = false;
	while(!isdigit(c=getchar()) && c != '-'); 
	if(c == '-') {
		Sign = true;
		c = getchar();
	}
	do {
		ans = (ans<<3) + (ans<<1) + (c - '0');
	}while(isdigit(c=getchar()));
	return Sign ? -ans : ans;
}
inline void Write(long long x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	}
	if(x >= 10) Write(x / 10);
	putchar(x % 10 + '0');
}
long long rbs(long long point,long long left,long long right){
    if(right >= left){
        long long middle = left+(right-left)/2;
        if(newarr[middle] == point){
            long long cnt = middle;
            while(newarr[cnt] == point && cnt < c){
                cnt++;
            }
            return cnt;
        }
        if(newarr[middle] > point){
            return rbs(point,left,middle-1);
        }
        return rbs(point,middle+1,right);
    }else{
        long long cnt = left;
        while(newarr[cnt+1] == point && cnt+1 < c){
            cnt++;
        }
        return cnt;
    }
}
long long lbs(long long point,long long left,long long right){
    if(right >= left){
        long long middle = left+(right-left)/2;
        if(newarr[middle] == point){
            long long cnt = middle;
            while(newarr[cnt-1] == point && cnt-1 >= 0){
                cnt--;
            }
            return cnt;
        }
        if(newarr[middle] > point){
            return lbs(point,left,middle-1);
        }
        return lbs(point,middle+1,right);
    }else{
        long long cnt = left;
        while(newarr[cnt-1] == point && cnt-1 >= 0){
            cnt--;
        }
        return cnt;
    }
}
void merge(long long index_i,long long index_j,long long mid){
    if(index_i == mid){
        return;
    }
    c = 0;
    for(long long i = index_i;i<mid;++i){
        newarr[i-index_i] = taste[i];
        ++c;
    }
    sort(newarr,newarr+c);
    for(long long i = mid;i<index_j;++i){
        long long rightpoint = taste[i]+tolerant[i];
        long long leftpoint = taste[i]-tolerant[i];
        long long rightindex = rbs(rightpoint,0,c-1);
        long long leftindex = lbs(leftpoint,0,c-1);
        counting += (rightindex-leftindex);
    }
    long long mid1 = (index_i+mid)/2;
    long long mid2 = (index_j+mid)/2;
    merge(index_i,mid,mid1);
    merge(mid,index_j,mid2);
    return;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    N = Read();
    for(long long i = 0;i<N;++i){
        taste[i] = Read();
    }
    for(long long i = 0;i<N;++i){
        tolerant[i] = Read();
    }
    merge(0,N,N/2);
    Write(counting);
    puts("");
}