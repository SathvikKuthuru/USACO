/*
 * Aryansh Shrivastava 
 * USACO Template 
 * Last Updated: 4/18/20
 */

#include <bits/stdc++.h> 
using namespace std; //STL 

/* Policy Based Data Structures (GCC)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
*/

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define maxpq priority_queue
#define maxpqi maxpq<int> 
#define minpqi maxpq<int, vi, greater<int> >
#define pb push_back
#define ins insert
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
#define rsz resize
#define lb lower_bound
#define ub upper_bound
#define all(x) begin(x),end(x)
#define trav(a,x) for(auto&(a):(x))
#define FOR(i,a,b) for(__typeof(b)i=(a)-((a)>(b));i!=(b)-((a)>(b));i+=((a)>(b))?-1:1) //go from i=lb to i=ub-1
#define FOR_(i,a,b,d) for(__typeof(b)i=(a)-((a)>(b));(a>b)?(i>b-1):(i<b);i+=(((a)>(b))?-1:1)*abs(d)) //go from i=lb to i=ub-1 by size d increments
#define F0R(i,b) FOR(i,0,b)
#define F0R_(i,b,d) FOR_(i,0,b,d)
#define R0F(i,n) FOR(i,n,0)
#define R0F_(i,b,d) FOR_(i,b,0,d)
#define F1R(i,b) FOR(i,1,b+1)
#define R1F(i,b) FOR(i,b+1,1)
#define F1R_(i,b,d) FOR_(i,1,b+1,d)
#define R1F_(i,b,d) FOR_(i,b+1,1,d)
#define what(x) out((#x),"is",(x))
#define big (int)1e5
#define bigg (int)(1e9+7)
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-8

void in(){} void outln(){} void out_(){cout << "\n";} //for fast, easy IO
template<typename T, typename...Types> void in(T& var1, Types&...var2){cin >> var1; in(var2...);}
template<typename T> void out(T var1){cout << var1 << "\n";}
template<typename T, typename...Types> void out(T var1, Types...var2){cout << var1 << " "; out(var2...);}
template<typename T, typename...Types> void outln(T var1, Types...var2){cout << var1 << "\n"; outln(var2...);}
template<typename T> void out_(T var1){cout << var1 << " ";}

bool comps(const pii&p1, const pii&p2){return (p1.s!=p2.s)?(p1.s<p2.s):(p1.f<p2.f);} //sort and search with special pair conditions & compare int-pair
struct intpairf{bool operator()(const pii&a, const int&b){return(a.f!=b)?(a.f<b):(a.s<b);}
bool operator()(const int&a, const pii&b){return(a!=b.f)?(a<b.f):(a<b.s);}};
struct intpairs{bool operator()(const pii&a, const int&b){return(a.s!=b)?(a.s<b):(a.f<b);}
bool operator()(const int&a, const pii&b){return(a!=b.s)?(a<b.s):(a<b.f);}};

struct DSU{ //from 0 to n
	vi e; void init(int n) { e = vi(n,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
	int compnum(){ //return the number of components
		int ret=1;
		F0R(i,sz(e)-1) if(get(i)!=get(i+1)) ret++;
		return ret;
	}
};

template<class T> struct SEG{ //UPD literally updates!!
	const T orz=-10*big;
	char choice='s'; //'m' is min, 'M' is max, 's' is sum
	void choose(char ch){choice=ch;}
	T comb(T a, T b){
		if(a==orz){if(b==orz){return 0;} return b;}
		if(b==orz) return a;
		if(choice=='m') return min(a,b);
		if(choice=='s') return a+b;
		if(choice=='M') return max(a,b);
	}
	int n; vector<T> seg;
		void init(int _n) { n = _n; seg.assign(4*n+1,orz); }
		void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
		void upd(int p, T val) { // set val at position p
			seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
		T query(int l, int r) {	// query choice on interval [l, r]
			T ra = orz, rb = orz;
			for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
				if (l&1) ra = comb(ra,seg[l++]);
				if (r&1) rb = comb(seg[--r],rb);
			}
			return comb(ra,rb);
	}
};

char /*global*/ bevvlazy='s';
int IDENN=0;
template<class T> pair<T,T> operator+(const pair<T,T>& l, const pair<T,T>& r) {
	if(bevvlazy=='s') IDENN=0;
	if(bevvlazy=='m') IDENN=bigg;
	if(bevvlazy=='M') IDENN=-bigg;
	if(bevvlazy=='s') {return mp(l.f+r.f,l.s+r.s);}
	if (l.f != r.f){
		if(bevvlazy=='m') {return min(l,r);}
		if(bevvlazy=='M') {return max(l,r);}
	}
	return mp(l.f,l.s+r.s);
}
template<class T, int SZ> struct LSEG{ //updates by adding, 1 indexed
	pair<T,T> sum[4*SZ+1];
	T lazy[4*SZ+1];
	LSEG() {
		memset(sum,0,sizeof sum);
		memset(lazy,0,sizeof lazy);
	}
	void choose(char choice){bevvlazy=choice; /*m for min, M for max, s for sum*/}
	void push(int ind, int L, int R) { // modify values for current node
		sum[ind].f += lazy[ind];
		if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
		lazy[ind] = 0; // pushed lazy to children
	}
	void pull(int ind) { // recalc values for current node
		sum[ind] = sum[2*ind]+sum[2*ind+1]; }
	void build() {
		FOR(i,SZ,2*SZ) sum[i] = mp(0,1);
		FOR(i,1,SZ) pull(i);
	}
	void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc;
			push(ind,L,R); return;
		}
		int M = (L+R)/2;
		upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
		pull(ind);
	}
	pair<T,T> qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) { //count # of min or # of max
		push(ind,L,R);
		if (lo > R || L > hi) return mp(IDENN,0);
		if (lo <= L && R <= hi) return sum[ind];
		int M = (L+R)/2;
		return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=SZ-1){
		return qsum(lo,hi,ind,L,R).f;
	}
};


template <class T, int ...Ns> struct BIT{ //UPD only adds!!
	//general Fenwick BIT struct with range sum queries and point updates for D dimensions
	T val = 0; void upd(T v) {val += v;} //map<int,BIT> preferable to BIT array
	T query() {return val;} // * Usage: \texttt{BIT<int,10,10>} gives 2D BIT * Time: O((\log N)^D)
};
template <class T, int N, int... Ns> struct BIT<T, N, Ns...> { //general format (l1,r1,l2,r2,...) for queries
	BIT<T,Ns...> bit[N+1];
	template<typename... Args> void upd(int pos, Args... args) { //general format (pos1,pos2,...,val) for upd
		for (; pos<=N; pos+=pos&-pos) bit[pos].upd(args...); } //indexed by 1
	template<typename... Args> T sum(int r, Args... args) {
		T res=0; for (;r;r-=r&-r) res += bit[r].query(args...);
		return res; }
	template<typename... Args> T query(int l, int r, Args...
		args) { return sum(r,args...)-sum(l-1,args...); }
};
template<class T, int SZ> struct BIT_r{ //range update, range query
	BIT<T,SZ> bit[2]; // piecewise linear functions
	// let cum[x] = sum_{i=1}^{x}a[i]
	void upd(int hi, T val) { // add val to a[1..hi]
		// if x <= hi, cum[x] += val*x
		bit[1].upd(1,val), bit[1].upd(hi+1,-val);
		// if x > hi, cum[x] += val*hi
		bit[0].upd(hi+1,hi*val);
	}
	void upd(int lo,int hi,T val){upd(lo-1,-val),upd(hi,val);}
	T sum(int x) { return bit[1].sum(x)*x+bit[0].sum(x); }
	T query(int x, int y) { return sum(y)-sum(x-1); }
};
template <const int maxN> struct OST{ //goal: alternative to R&B ordered statistic tree policy -- operations rank & find kth smallest
	BIT<int, maxN> tree;
	void ins(int x){if(!tree.query(x,x)) tree.upd(x,1);}
	void del(int x){if(tree.query(x,x)) tree.upd(x,-1);}
	int ofk(int x){return (tree.query(x,x))?(tree.sum(x)-1):tree.sum(x);} //order of key (small to large)
	int fbo(int k){ //find by order
		k++;
		int l = 0; //check to make sure this exists!!!
		int h = maxN;
		while(l<h){
		   int mid=(l+h)/2;
		   if(k<=tree.sum(mid)) h=mid;
		   else l = mid+1;
		}
		return l;
	} //coordinate compression is a good idea when possible!!
};

#define PNAME ""

int main(){
	cin.tie(0)->sync_with_stdio(0); if(fopen(PNAME ".in","r")){freopen(PNAME ".in","r",stdin); freopen(PNAME ".out","w",stdout);}
	return 0;
}
