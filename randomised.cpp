#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>
#include <unordered_map>
#define MOD 1000000007
using namespace std;
typedef long long ll;
typedef vector < int > vi;
typedef vector < ll > vll;
typedef pair <int, int> pii;
typedef pair<ll, ll> pll;
#define rep(i,a,n) for(i=a;i<=n;i++)
#define per(i,n,a) for(i=n;i>=a;i--)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define iOS ios_base::sync_with_stdio(false); cin.tie(NULL)
#define imax numeric_limits<int>::max()
#define imin numeric_limits<int>::min()
#define llmax numeric_limits<ll>::max()
#define llmin numeric_limits<ll>::min()
ll powmod(ll a,ll b) {ll res=1;if(a>=MOD)a%=MOD;for(;b;b>>=1){if(b&1)res=res*a;if(res>=MOD)res%=MOD;a=a*a;if(a>=MOD)a%=MOD;}return res;}
ll gcd(ll a , ll b){return b==0?a:gcd(b,a%b);}
/****************CODE STARTS HERE*******************/
int B,L,D;
int score[100005];
int N[100005];
int T[100005];
int M[100005];
vector<pair<int,int> > lib_list[100005]; //score and id
const int N_RANDOM_RUNS=10000;
int main()
{
    cin>>B>>L>>D;
    for(int i=0;i<B;i++)
    {
    	cin>>score[i];
    }
    for(int i=0;i<L;i++)
    {
    	cin>>N[i]>>T[i]>>M[i];
    	for(int j=0;j<N[i];j++)
    	{
    		int x;cin>>x;
    		lib_list[i].pb(mp(-score[x],x));
    	}
    	sort(lib_list[i].begin(),lib_list[i].end());
    }

    vector<int> schedule;
    for(int i=0;i<L;i++)
    {
    	schedule.pb(i);
    }

	ll best_ans=-1;
    int best_A;
    vector<int> best_Y;
    vector<int> best_K;
    vector<vector<int> > best_ids;

    for(int i=0;i<N_RANDOM_RUNS;i++)
    {
        int current_A;
        vector<int> current_Y;
        vector<int> current_K;
        vector<vector<int> > current_ids;

    	ll current_ans=0;
    	int first_available=0; //first day available for signup
    	bool book_scanned[B];
    	memset(book_scanned,false,sizeof(book_scanned));
    	for(int j=0;j<schedule.size();j++)
    	{
    		if(first_available>=D)
    		{
    			break;
    		}

    		int lib_idx=schedule[j];
            

    		int n=N[lib_idx],m=M[lib_idx],t=T[lib_idx];

    		first_available=first_available+t;
    		int remaining_days=D-first_available;

    		int lib_book_idx=0;
    		int ctr=0;
            vector<int> books_sent;
			while(remaining_days>0 && lib_book_idx<n)
			{
				
				if(!book_scanned[lib_list[lib_idx][lib_book_idx].second])
    			{
    				book_scanned[lib_list[lib_idx][lib_book_idx].second]=true;
    				current_ans+=(-lib_list[lib_idx][lib_book_idx].first);	
                    books_sent.pb(lib_list[lib_idx][lib_book_idx].second);
    			}
    			else
    			{
    				lib_book_idx++;
    				continue;
    			}
    			ctr++;
    			lib_book_idx++;
				if(ctr%m==0)
				{
					ctr=0;
					remaining_days--;
				}
			}
            if(books_sent.size()>0)
            {
                current_Y.pb(lib_idx);
                current_ids.pb(books_sent);
                current_K.pb(books_sent.size());
            }
            
    	}
        current_A=current_K.size();
        if(current_ans > best_ans )
        {
            best_ans=current_ans;
            best_A=current_A;
            best_Y=current_Y;
            best_K=current_K;
            best_ids=current_ids;
        }
    	std::random_shuffle ( schedule.begin(), schedule.end() );
    }
    // cout<<"BEST SCORE "<<best_ans<<endl;
    cout<<best_A<<endl;
    for(int i=0;i<best_A;i++)
    {
        cout<<best_Y[i]<<" "<<best_K[i]<<endl;
        for(int j=0;j<best_K[i];j++)
        {
            cout<<best_ids[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}