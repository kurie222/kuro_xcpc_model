
using ui64 = unsigned long long;
using PUU = pair<ui64, ui64>;
using i64 = long long;

// N 为字符串最长长度 p为seed  mod1/mod2 为两个模数
const ui64 N = 1e5 + 10, p = 131, mod1 = 998244853, mod2 = 1e9 + 7;

ui64 a1[N], a2[N], hs1[N], hs2[N];

void init() {//初始化 a 数组
	a1[0] = a2[0] = 1;
	for (int i = 1; i < N; ++i) {
		a1[i] = a1[i - 1] * p % mod1;
		a2[i] = a2[i - 1] * p % mod2;
	}
}

void hashstr(string& str) {//将str哈希化
	int n = str.size();
	//默认str下标从0开始 如果从1开始则需要修改str[i - 1]为str[i]
	for (int i = 1; i <= n; ++i) {
		hs1[i] = (hs1[i - 1] * p % mod1 + str[i - 1]) % mod1;
		hs2[i] = (hs2[i - 1] * p % mod2 + str[i - 1]) % mod2;
	}
}

ui64 geths1(int l, int r) {//得到str[l -- r]的第一哈希值 定义域[1, n]
	return (hs1[r] - hs1[l - 1] * a1[r - l + 1] % mod1 + mod1) % mod1;
}

ui64 geths2(int l, int r) {//得到str[l -- r]的第二哈希值 定义域[1, n]
	return (hs2[r] - hs2[l - 1] * a2[r - l + 1] % mod2 + mod2) % mod2;
}

使用: 给出一个字符串 str，且 len 为 str 的长度
*init() <初始化预处理>
*hashstr(str) <将字符串str哈希化预处理>

-hs1[len] / hs2[len] <str整串的第一/二哈希值>
-geths1(l, r) / geths2(l, r) <得到str[l--r]的第一/二哈希值> 


<将哈希值存入 map<PUU, int>s, set<PUU> s 进一步处理>
例如:
map[{ geths1(l, r), geths2(l, r) }];
set,insert({ geths1(l, r), geths2(l, r) });
(注意: l，r严格在闭区间[1, n]内)

