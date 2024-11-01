
const int N = 3e6 + 10, M = 26 + 26 + 10 + 10;//N 字符串总长度 M 字符种类数目
int trie[N][M], cnt[N], idx = 0;
bool exist[N];

void clear()
{
	fill(trie[0], trie[0] + idx * M, 0);
	fill(exist, exist + idx + 1, false);
	fill(cnt, cnt + idx + 1, 0);
	idx = 0;
}
int pos(char x)
{
	if (x >= 'a' && x <= 'z') return x - 'a' + 1;
	if (x >= 'A' && x <= 'Z') return x -'A' + 27;
	if (x >= '0' && x <= '9') return x -'0' + 53;
}
void insert(string & str)//插入字符串 str
{
	int now = 0;
	for (auto& x : str)
	{
		if (!trie[now][pos(x)]) trie[now][pos(x)] = ++idx;
		now = trie[now][pos(x)];
		++cnt[now];
	}
	exist[now] = true;
}
int findpre(string & str)//查询有多少个相同前缀 str
{
	int now = 0;
	for (auto& x : str)
	{
		if (!trie[now][pos(x)]) return 0;
		now = trie[now][pos(x)];
	}
	return cnt[now];
}
bool findstr(string & str)//查询是否存在字符串 str
{
	int now = 0;
	for (auto& x : str)
	{
		if (!trie[now][pos(x)]) return false;
		now = trie[now][pos(x)];
	}
	return exist[now];
}


使用: 给出字符串 <str>

-clear() <清空字典树>
-insert(str) <向树上插入str字符串>
-findpre(str) <查询是否有前缀串str>
-findstr(str) <查询是否存在字符串str>

