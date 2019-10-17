#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

char word1[2050];
char word2[2050];
int table[2050][2050] = {};

int compare(char *str1,char *str2){
    int l1 = strlen(str1);
    int l2 = strlen(str2);
    for(int i = 0;i<=l1;++i){
        table[i][0] = i;
    }
    for(int i = 0;i<=l2;++i){
        table[0][i] = i;
    }
    for(int i = 1;i<=l1;++i){
        for(int j = 1;j<=l2;++j){
            if(str1[i-1] != str2[j-1]){
                table[i][j] = table[i-1][j-1];
            }else{
                table[i][j] = min(table[i-1][j-1],min(table[i-1][j],table[i][j-1]))+1;
            }
        }
    }
    int min = 2147483647;
    for(int i = 0;i<=l2;i++){
        if(table[l1][i] < min){
            min = table[l1][i];
        }
    }
    for(int i = 0;i<=l1;i++){
        if(table[i][l2] < min){
            min = table[i][l2];
        }
    }
    return min;
}

int main(){
    scanf("%s%s",word1,word2);
    cout << compare(word1,word2) << endl;
}