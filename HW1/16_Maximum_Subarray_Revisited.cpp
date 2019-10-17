#include <iostream>
#define ll long long
#define MAXN 500050

using namespace std;

typedef struct sgt{
    ll left_max;
    ll right_max;
    ll sum;
    ll max;
}node;

ll N,Q;
ll arr[MAXN];
node segment_tree[4*MAXN];

void build(ll left,ll right,ll index){
    if(left == right){
        segment_tree[index].sum = arr[left];
        segment_tree[index].left_max = arr[left];
        segment_tree[index].right_max = arr[left];
        segment_tree[index].max = arr[left];
        return;
    }
    ll mid = (left+right)/2;
    ll lefttree = index*2;
    ll righttree = index*2+1;
    build(left,mid,lefttree);
    build(mid+1,right,righttree);
    segment_tree[index].left_max = max(segment_tree[lefttree].left_max,segment_tree[lefttree].sum+segment_tree[righttree].left_max);
    segment_tree[index].right_max = max(segment_tree[righttree].right_max,segment_tree[righttree].sum+segment_tree[lefttree].right_max);
    segment_tree[index].max = max(segment_tree[lefttree].max,max(segment_tree[righttree].max,segment_tree[lefttree].right_max+segment_tree[righttree].left_max));
    segment_tree[index].sum = segment_tree[lefttree].sum + segment_tree[righttree].sum;
    return;
}

ll find_max(){
    return segment_tree[1].max;
}

void update(ll place,ll value,ll start,ll end,ll index){
    if(start == end){
        segment_tree[index].max = value;
        segment_tree[index].left_max = value;
        segment_tree[index].right_max = value;
        segment_tree[index].sum = value;
        return;
    }else{
        ll mid = (start+end)/2;
        ll lefttree = index*2;
        ll righttree = index*2+1;
        if(start <= place && place <= mid){
            update(place,value,start,mid,lefttree);
        }else{
            update(place,value,mid+1,end,righttree);
        }
        segment_tree[index].left_max = max(segment_tree[lefttree].left_max,segment_tree[lefttree].sum+segment_tree[righttree].left_max);
        segment_tree[index].right_max = max(segment_tree[righttree].right_max,segment_tree[righttree].sum+segment_tree[lefttree].right_max);
        segment_tree[index].max = max(segment_tree[lefttree].max,max(segment_tree[righttree].max,segment_tree[lefttree].right_max+segment_tree[righttree].left_max));
        segment_tree[index].sum = segment_tree[lefttree].sum + segment_tree[righttree].sum;
        return;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> N >> Q;
    for(ll i = 1;i<=N;++i){
        cin >> arr[i];
    }
    build(1,N,1);
    ll ans = find_max();
    if(ans < 0){
        ans = 0;
    }
    cout << ans << endl;
    ll place,value;
    while(Q--){
        cin >> place >> value;
        update(place,value,1,N,1);
        ans = find_max();
        if(ans < 0){
            ans = 0;
        }
        cout << ans << endl;
    }
}