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

int getValue(int len, const vi& sub) {
	auto ans = len;
	for (const auto& x : sub) {
		if (0 == x) {
			++ans;
		}
	}

	return ans;
}

int solve(int n, const vi& lst) {
	auto ans = int{ 0 };

	const auto& subs = getSubs(n, lst);
	for (const auto& sub : subs) {
		auto sz = static_cast<int>(sub.size());
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