#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct MinStack {
	stack< pair<T,T> > st;
	void push(const T& value) {
		if( !st.empty() && st.top().second < value)
			st.push(make_pair(value, st.top().second));
		else
			st.push(make_pair(value, value));
	}
	void pop() {
		st.pop();
	}
	T top() const {
		return st.top().first;
	}
	T min() const {
		return st.top().second;
	}
	bool empty() const {
		return st.empty();
	}
};

template<typename T>
struct MinQueue {
	MinStack<T> st1, st2;
	void push(const T& value) {
		st1.push(value);
	}
	void pop() {
		if( st2.empty() )
			while( !st1.empty() )
				st2.push(st1.top()), st1.pop();
		st2.pop();
	}
	T front() const {
		if( st2.empty() )
			while( !st1.empty() )
				st2.push(st1.top()), st1.pop();
		return st2.top();
	}
	T min() const {
		if( st1.empty() || st2.empty() )
			return st1.empty() ? st2.min() : st1.min();
		else
			return st1.min() < st2.min() ? st1.min() : st2.min();
	}
};

int main() {


	// find minimums in "window" with length m
	// in n values (m <= n)
	int n,m;
	while( cin >> n >> m ) {
		MinQueue<int> u;
		vector<int> a; a.reserve(n);
		for(int i = 0; i < n; i++) {
			int t; cin >> t; u.push(t); // O(1) push
			a.push_back(u.min()); // O(1) minimum
			if( i >= m-1 ) u.pop();
		}
		for(int i = m-1; i < n; i++)
			cout << a[i] << " ";
		cout << "\n";
	}

	return 0;
}
