#include <bits/stdc++.h>
using namespace std;

#define inf 1000*1000*1000
#define sz(x) static_cast<int>((x).size())
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define forn(i,n) for(int i = 0; i < (n); ++i)

template<typename I> inline void out(I l,I r,char A = ' ',char B = '\n')
{if(l!=r){cout<<*l;while(++l!=r)cout<<A<<*l;}cout << B;}
template<typename I> inline void in(I l,I r)
{while(l!=r) cin>>*l,++l;}

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

	int n;
	while( cin >> n ) {
		n += 2;
		vector<string> board(n, string(n, '#'));
		forn(i,n-2)
			in(board[i+1].begin() + 1, board[i+1].end() - 1);

		const int dr[] = {0,-1,0,1};
		const int dc[] = {1,0,-1,0};

		int result = 0;

		board[1][1] = board[n-2][n-2] = 'X';
		queue<pair<int,int>> q;
		q.push(mp(1,1)); q.push(mp(n-2,n-2));
		while( !q.empty() ) {
			int r = q.front().first,
			    c = q.front().second;
			q.pop();
			forn(i,4) {
				int nr = r + dr[i], nc = c + dc[i];
				if( board[nr][nc] == '.' ) {
					board[nr][nc] = 'X';
					q.push(mp(nr,nc));
				}
				if( board[nr][nc] == '#' ) {
					result += 9;
				}
			}
		}

		cout << result - 4*9 << "\n";
	}

	return 0;
}
