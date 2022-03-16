#include <iostream>
#include <vector>

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pii>;
using vvii = vector<vii>;
using vb = vector<bool>;

vvi getSubs(int n, const vi& lst) {
	auto ret = vvi{};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; i + j < n; ++j) {
			auto sub = vi{};
			for (int k = i; k < n - j; ++k) {
				sub.push_back(lst[k]);
			}

			ret.push_back(sub);
		}
	}

	return ret;
}

vvi memo;
int mex(int len, const vi& sub, int b, int e) {
	if (memo[b][e] < 0) {
		auto mn = sub[b];
		auto mx = sub[b];
		for (int i = b; i <= e; ++i) {
			if (sub[i] < mn) {
				mn = sub[i];
			}

			if (mx < sub[i]) {
				mx = sub[i];
			}
		}

		if (0 < mn) {
			memo[b][e] = 0;
			return memo[b][e];
		}

		auto isOccur = vb(mx + 1, false);
		for (int i = b; i <= e; ++i) {
			isOccur[sub[i]] = true;
		}

		for (int i = 0; i < mx; ++i) {
			if (!isOccur[i]) {
				memo[b][e] = i;
				return memo[b][e];
			}
		}

		memo[b][e] = mx + 1;
	}

	return memo[b][e];
}

int getCost(int len, const vi& sub) {
	auto ans = len;
	for (const auto& x : sub) {
		if (0 == x) {
			++ans;
		}
	}

	return ans;
}

int getValue(int len, const vi& sub) {
	auto ans = int{ 0 };
	const auto& c = getCost(len, sub);

	if (ans < c) {
		ans = c;
	}

	return ans;
}

int solve(int n, const vi& lst) {
	auto ans = int{ 0 };

	const auto& subs = getSubs(n, lst);
	for (const auto& sub : subs) {
		auto sz = static_cast<int>(sub.size());
		memo = vvi(sz, vi(sz, -1));

		ans += getValue(sz, sub);
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	cin >> t;
	while (0 < (t--)) {
		int n;
		cin >> n;

		auto lst = vi(n);
		for (int i = 0; i < n; ++i) {
			cin >> lst[i];
		}

		cout << solve(n, lst) << '\n';
	}

	return 0;
}