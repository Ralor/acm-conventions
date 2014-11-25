#include <bits/stdc++.h>
using namespace std;

struct Node {
	int v, l, r;
	Node(int v, int l, int r) : v(v), l(l), r(r) { }
};
vector<Node> bst;

void bst_build(vector<int>& a, int id, int l, int r) {
	bst.push_back(Node(a[id],-1,-1));
	if( l>r )
		return;
	int mid=-1;
	for(int i=l;i<=r;i++)
		if( a[i]<bst[id].v ) {
			mid=i;
			break;
		}

	if( mid!=-1 && mid>l ) {
		bst_build(a, bst[id].r = l, l+1, mid-1);
		bst_build(a, bst[id].l = mid, mid+1, r);
	} else if( mid==-1 ) {
		bst_build(a, bst[id].r = l, l+1, r);
	} else if( mid!=-1 ) {
		bst_build(a, bst[id].l = l, l+1, r);
	}
}

void bst_print(int v) {
	if( v != -1 ) {
		bst_print(bst[v].r);
		bst_print(bst[v].l);
		cout<<bst[v].v<<"\n";
	}
}

int main() {

	int n;
	while(cin>>n){
		vector<int> a(n);
		for(int i=0;i<n;i++)cin>>a[i];
		reverse(a.begin(), a.end());
		bst.clear();
		bst_build(a,0,1,n-1);
		bst_print(0);
	}

	return 0;
}
