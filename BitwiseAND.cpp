#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void solution(int n, int k){
    int i=0,sonuc=0,tmp;
    while(i!=n*(n-1)/2){//i, n'in 2li kombinasyonuna eşit olmadığı sürece
        int j=i+1;
        while(j<=n){//j n den küçük olduğu sürece
        tmp=i&j;
        if(tmp>sonuc && tmp<k){ //sonuçtan büyükse ve kden küçükse 
            sonuc=tmp; //sonuç, temp olur
            if(sonuc==k-1){ //sonuç kden 1 küçükse direk yazdır ve fonksiyonu durdur.
                cout<<sonuc<<endl;
                return;
            }
        }
            j++;
        }
        i++;
    }
        cout<<sonuc<<endl;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nk_temp;
        getline(cin, nk_temp);

        vector<string> nk = split_string(nk_temp);

        int n = stoi(nk[0]);

        int k = stoi(nk[1]);
        
        //ÇÖZÜM BAŞLANGIÇ
        solution(n,k);
        //ÇÖZÜM BİTİŞ
    }
    
    
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
