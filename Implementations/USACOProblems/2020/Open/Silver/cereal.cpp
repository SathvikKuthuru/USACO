#include <iostream>
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;
//result: 10/10

#define maxn 100000
#define maxm 100000
typedef pair<int,int> pii;
#define f first
#define s second
int n,m,ans,choice[maxn]; deque<int> cereal[maxm]; pii cowvals[maxn];
bool firstcheck[maxm]; //look at cow i

#define problemname "cereal"

#define first_cereal_q cereal[firstchoice]

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen(problemname ".in", "r", stdin); freopen(problemname ".out", "w", stdout);
  cin >> n >> m;
  for(int i=0; i<n; i++){
    int a,b; cin >> a >> b; a--,b--;
    cowvals[i].f=a; cowvals[i].s=b;
    if(!firstcheck[a]){
      firstcheck[a]=1;
      choice[i]=1; ans++;
    }
    else if(!firstcheck[b]){
      firstcheck[b]=1; cereal[a].push_back(i);
      choice[i]=2; ans++;
    }
    else {choice[i]=3; cereal[a].push_back(i); cereal[b].push_back(i);}
  } cout << ans << "\n";
  //process
  for(int i=0; i<n-1; i++){
    ans--;
    int firstchoice=cowvals[i].f;
    int nxt;
    while(1){
    	//deque<int> first_cereal_q=cereal[firstchoice];
		if(!first_cereal_q.empty()){//nxt needs to update
            nxt=first_cereal_q.front();
			first_cereal_q.pop_front();
			while(nxt<=i || choice[nxt]<=((cowvals[nxt].f==firstchoice)?1:((cowvals[nxt].s==firstchoice)?2:3))){
				if(!first_cereal_q.empty()) {nxt=first_cereal_q.front(); first_cereal_q.pop_front();}
                else{break;}
			}
		} else {break;}
		if(choice[nxt]==3){
            ans++;
			choice[nxt]=(cowvals[nxt].f==firstchoice)?1:2;
			break;
		}
		else{
			firstchoice=cowvals[nxt].s;
		}
		choice[nxt]=((cowvals[nxt].f==firstchoice)?1:((cowvals[nxt].s==firstchoice)?2:3));
    }
    cout << ans << "\n";
  }
  return 0; //if not at the front, doesn't get cereal
}
