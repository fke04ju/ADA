#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 305
#define ll long long

using namespace std;

ll dp[MAXN][MAXM];
ll note[MAXN];
ll sub[MAXN];
ll N,M,K;

ll effort(ll a,ll b){
    if(abs(a-b)-K < 0){
        return 0;
    }else{
        return abs(a-b)-K;
    }
}

ll span(ll index){
    ll left,right;
    if(index - K < 0){
        left = index;
    }else{
        left = index-K;
    }
    if(index + K >= M){
        right = index;
    }else{
        right = index+K;
    }
    return min(sub[left],min(sub[right],sub[index]));
}

int main(){
    cin >> N >> M >> K;
    for(ll i = 0;i<M;i++){
        dp[0][i] = 0;
    }
    for(ll i = 0;i<N;i++){
        cin >> note[i];
    }
    for(ll i = 1;i<N;i++){
        ll eff = effort(note[i],note[i-1]);
        for(ll j = 0;j<M;j++){
            dp[i][j] = dp[i-1][j]+eff;
        }
        ll m = __LONG_LONG_MAX__;
        for(ll j = 0;j<M;j++){
            m = min(m,dp[i-1][j]+effort(note[i],j));
        }
        dp[i][note[i-1]] = m;
        for(ll j = 0;j<M;j++){
            sub[j] = dp[i][j];
        }
        for(ll j = 0;j<M;j++){
            dp[i][j] = span(j);
        }

    }
    ll ans = __LONG_LONG_MAX__;
    for(ll i = 0;i<M;i++){
        ans = min(ans,dp[N-1][i]);
    }
    cout << ans;
}