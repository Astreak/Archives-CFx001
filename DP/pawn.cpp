//https://codeforces.com/contest/41/problem/D
/* Author : PrjB aka "Astreak","isthisdp" */
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define vi vector<int>
#define vii vector<vector<int>> 
#define vll vector<ll>
#define vs vector<string>
#define vc vector<char>
#define mp make_pair
#define em emplace_back
#define all(x) x.begin(),x.end()
#define f first
#define s second
#define fR(i,a,b) for(int i=(a);i<(b);i++)
#define fr(i,a) for(int i=0;i<(a);i++)
#define fd(i,a) for(int i=(a)-1;i>=0;i--)
#define fD(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define indp2(dp,n,m,val) for(int i=0;i<=n;i++)for(int j=0;j<=m;j++) dp[i][j]=val;
#define indp1(dp,n,val)for(int i=0;i<=n;i++)dp[i]=val;
using namespace std;
const ll INF=1e16+10;
const int MOD=1e9+7;
template<class T> bool setmin(T& a, const T& b) {return b<a ? a=b,1:0;}
template<class T> bool setmax(T& a, const T& b) {return a<b ? a=b,1:0;}
inline int sz(vector<int>& A){
	return (int)A.size();
}
inline void inp1(vector<int>& A){
	for(auto& x:A) cin>>x;
}
inline void oup1(vector<int>& A){
	for(auto x:A) cout<<x<<" ";
}
inline void oup2(vector<int>& A){
	for(auto x:A) cout<<x<<"\n";
}
inline void IOS(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return;
}
inline ll LCM(ll a,ll b){
	return (a*b)/(__gcd(a,b));
}
inline bool check_sol(ll a,ll b,ll c){
	return !(c%(__gcd(a,b)));
}
inline ll NOP(ll a){
	return (a*(a-1))/2;
}
inline void inp(vector<int>& A){
	for(auto& x:A) cin>>x;
	return ;
}
inline void oup(vector<int>& A){
	for(auto x:A) cout<<x<<" ";
	cout<<"\n";
	return;
}
inline ll SS(ll a){
	return a*(a+1)/2;
}
ll bin_exp(ll a,ll b){
	ll res=1;
	while(b>=1){
		if(b&1) res=((res%MOD)*(a%MOD))%MOD;
		a=((a%MOD)*(a%MOD))%MOD;
		b>>=1;
	}
	return res;
}
class SegTree{
public:
	vector<int> seg;
	int N;
	SegTree(int n){
		int temp=1;
		while(temp<n)temp*=2;
		N=temp;
		seg.assign(2*temp,0);
	}
	int combine(int a,int b){
		return __gcd(a,b);
	}
	int make_data(int a){ return a;}
	void build(int indx,int v,int l,int r,int x=0){
		if(l==r-1){
			seg[x]=make_data(v);return;
		}
		int m=l+((r-l)>>1);
		if(indx<m) build(indx,v,l,m,2*x+1);
		else build(indx,v,m,r,2*x+2);
		seg[x]=combine(seg[2*x+1],seg[2*x+2]);
		return ;
	}
	int query(int l,int r,int lx,int rx,int x=0){
		if(rx<=l || lx>=r) return 0;
		if(lx>=l && rx<=r) return seg[x];
		int m=lx+(rx-lx)/2;
		return combine(query(l,r,lx,m,2*x+1),query(l,r,m,rx,2*x+2));
	}
};
class DisJ{
public:
	vector<int> parent;
	vector<int> R;
	DisJ(int n){
		for(int i=0;i<n;i++){
			parent.push_back(i);
			R.emplace_back(0);
		}
	}
	int get_R(int u){
		if(parent[u]==u)
			return u;
		else{
			parent[u]=get_R(parent[u]);
			return parent[u];
		}
	}
	void merge(int u,int v){
		int a=get_R(u);int b=get_R(v);
		if(R[a]>R[b])
			parent[b]=a;
		else if(R[b]>R[a])
			parent[a]=b;
		else{
			++R[a];
			parent[b]=a;
		}
	}
};
class Point{
private:
	int x,y;
public:
	Point(int a,int b): x(a),y(b){}
	friend Point operator+(Point const&,Point const&);
	friend ll operator*(Point const&,Point const&);
	friend ostream& operator<<(ostream& os,Point const&);
};
Point operator+(Point const& p1,Point const& p2){
	return Point(p1.x+p2.x,p1.y+p2.y);
}
ostream& operator<<(ostream& os,Point const& p){
	return os<<"<"<<p.x<<","<<p.y<<">";
}
bool check(vector<int> A,int n){
	sort(A.begin(),A.end());
	if(A[0]==A[n-1]) return false;
	return true;
};
struct D{
	ll a,b,c,d;
};
struct pp{
	int a,b,c;
};
void test_case(){
	int n,m,k;
	cin>>n>>m>>k;
	int A[n][m];
	for(int i=0;i<n;i++){
		string ok;
		cin>>ok;
		for(int j=0;j<m;j++){
			A[i][j]=ok[j]-'0';
		}
	}
	pp dp[n][m][k+1];
	string trie[n][m][k+1];
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int l=0;l<=k;l++){
				dp[i][j][l]={0,false,j};
				trie[i][j][l]="";
			}
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=m-1;j>=0;j--){
			for(int l=0;l<=k;l++){
				if(i==n-1){
					dp[i][j][A[i][j]%(k+1)]={A[i][j],true,j};
					trie[i][j][A[i][j]%(k+1)]="";
					continue;
				}
				if(j==m-1) continue;
				int rem=A[i][j]%(k+1);
				int temp=rem;
				if(rem<=l) temp=l-rem;
				else if(rem>l) temp=k+1-rem+l;
				dp[i][j][l]={dp[i+1][j+1][temp].a+A[i][j],dp[i+1][j+1][temp].b,dp[i+1][j+1][temp].c};
				if(dp[i][j][l].b) trie[i][j][l]=trie[i+1][j+1][temp]+'L';
			}
		}
 
		for(int j=0;j<m;j++){
			for(int l=0;l<=k;l++){
				if(i==n-1){
					dp[i][j][A[i][j]%(k+1)]={A[i][j],true,j};
					continue;
				}
				if(j==0) continue;
				int rem=A[i][j]%(k+1);
				int temp=rem;
				if(rem<=l) temp=l-rem;
				else if(rem>l) temp=k-rem+1+l;
				int ok=dp[i+1][j-1][temp].a+A[i][j];
				if(dp[i][j][l].b==true && dp[i+1][j-1][temp].b==true){
					int yy=dp[i][j][l].a;
					int goat=max(ok,yy);
					if(ok>yy){
						trie[i][j][l]=trie[i+1][j-1][temp]+'R';
						dp[i][j][l]={ok,true,dp[i+1][j-1][temp].c};
					}
				}
				else if(dp[i][j][l].b==true) continue;
				else if(dp[i+1][j-1][temp].b==true){
				   trie[i][j][l]=trie[i+1][j-1][temp]+'R';
	                     dp[i][j][l]={ok,true,dp[i+1][j-1][temp].c};
				}
				else dp[i][j][l]={0,false,-1};
		      }
		}
	}
	int ans=-1;
	int indx=-1;
	int hh=-1;
	for(int i=0;i<m;i++){
		if(dp[0][i][0].b){
			if(ans<dp[0][i][0].a){
				ans=dp[0][i][0].a;
				indx=i;
				hh=dp[0][i][0].c;
			}
		}
	}
	cout<<ans<<"\n";
	if(ans==-1) return;
	cout<<hh+1<<"\n";
	cout<<trie[0][indx][0]<<"\n";
	
 
 
}
int main(){
	cout<<setprecision(7);
	// int T;
	// cin>>T;
	//while(T--)
	test_case();
}