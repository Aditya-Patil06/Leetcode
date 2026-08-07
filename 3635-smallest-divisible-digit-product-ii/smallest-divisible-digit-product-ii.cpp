class Solution {
public:
    string smallestNumber(string num, long long t) {
        vector<int> need(4, 0);
        long long x = t;
        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {
            while (x % primes[i] == 0) {
                need[i]++;
                x /= primes[i];
            }
        }
        if (x != 1) return "-1";

        int A = need[0], B = need[1], C = need[2], D = need[3];

        vector<vector<vector<vector<int>>>> dp(
            A + 1,
            vector<vector<vector<int>>>(
                B + 1,
                vector<vector<int>>(
                    C + 1,
                    vector<int>(D + 1, 1e9))));

        vector<array<int,4>> add(10);
        add[1]={0,0,0,0};
        add[2]={1,0,0,0};
        add[3]={0,1,0,0};
        add[4]={2,0,0,0};
        add[5]={0,0,1,0};
        add[6]={1,1,0,0};
        add[7]={0,0,0,1};
        add[8]={3,0,0,0};
        add[9]={0,2,0,0};

        for (int e2=A;e2>=0;e2--)
            for (int e3=B;e3>=0;e3--)
                for (int e5=C;e5>=0;e5--)
                    for (int e7=D;e7>=0;e7--) {
                        if (e2==A&&e3==B&&e5==C&&e7==D){
                            dp[e2][e3][e5][e7]=0;
                            continue;
                        }
                        int best=1e9;
                        for(int d=1;d<=9;d++){
                            auto c=add[d];
                            int n2=min(A,e2+c[0]);
                            int n3=min(B,e3+c[1]);
                            int n5=min(C,e5+c[2]);
                            int n7=min(D,e7+c[3]);
                            if(n2==e2&&n3==e3&&n5==e5&&n7==e7) continue;
                            best=min(best,1+dp[n2][n3][n5][n7]);
                        }
                        dp[e2][e3][e5][e7]=best;
                    }

        int n=num.size();

        vector<array<int,4>> pref(n+1);
        vector<int> bad(n+1,0);

        pref[0]={0,0,0,0};
        for(int i=0;i<n;i++){
            bad[i+1]=bad[i]||(num[i]=='0');
            pref[i+1]=pref[i];
            if(num[i]!='0'){
                auto c=add[num[i]-'0'];
                pref[i+1][0]=min(A,pref[i+1][0]+c[0]);
                pref[i+1][1]=min(B,pref[i+1][1]+c[1]);
                pref[i+1][2]=min(C,pref[i+1][2]+c[2]);
                pref[i+1][3]=min(D,pref[i+1][3]+c[3]);
            }
        }

        if(!bad[n] &&
           pref[n][0]==A &&
           pref[n][1]==B &&
           pref[n][2]==C &&
           pref[n][3]==D)
            return num;

        auto buildSuffix = [&](array<int,4> st, int len){
            string res;
            while(len--){
                for(int d=1;d<=9;d++){
                    auto c=add[d];
                    array<int,4> ns={
                        min(A,st[0]+c[0]),
                        min(B,st[1]+c[1]),
                        min(C,st[2]+c[2]),
                        min(D,st[3]+c[3])
                    };
                    if(dp[ns[0]][ns[1]][ns[2]][ns[3]]<=len){
                        res.push_back(char('0'+d));
                        st=ns;
                        break;
                    }
                }
            }
            return res;
        };

        for(int i=n-1;i>=0;i--){
            if(bad[i]) continue;

            auto base=pref[i];
            int start=max(1,(num[i]-'0')+1);

            for(int d=start;d<=9;d++){
                auto c=add[d];
                array<int,4> ns={
                    min(A,base[0]+c[0]),
                    min(B,base[1]+c[1]),
                    min(C,base[2]+c[2]),
                    min(D,base[3]+c[3])
                };
                if(dp[ns[0]][ns[1]][ns[2]][ns[3]]<=n-i-1){
                    return num.substr(0,i)+char('0'+d)+buildSuffix(ns,n-i-1);
                }
            }
        }

        int L=max(n+1,dp[0][0][0][0]);
        return buildSuffix({0,0,0,0},L);
    }
};