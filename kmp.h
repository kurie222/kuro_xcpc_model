string str, match;//str是模式串 match是匹配串

void getnxt(vector<int>& nxt, int len, string matcht)
{
	for (int i = 2; i < len; ++i)
	{
		nxt[i] = nxt[i - 1];
		while (nxt[i] && matcht[i] != matcht[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
		nxt[i] += (matcht[i] == matcht[nxt[i] + 1]);//补正nxt[i]
	}
}

bool kmp(string str, string match)
{
	//使字符串下标从 1 开始
	string strt = '?' + str + '.', matcht = '?' + match;
	vector<int> nxt(matcht.size());
	getnxt(nxt, matcht.size(), matcht);
	//开始匹配: i为str下标 j 为match下标
	for (int i = 1, j = 1; i <= strt.size();)
	{
		while (j != 1 && strt[i] != matcht[j]) j = nxt[j - 1] + 1;//回溯 j
		if (strt[i] == matcht[j]) ++i, ++j;
		else ++i;
		if (j == matcht.size())
		{
			//此时 i - match.size() 即为第一个开始匹配元素的下标
			j = nxt[match.size()] + 1;
			//匹配成功后要做的事
			//return true;
		}
	}
	//匹配失败后要做的事
	//return false;
}

使用: 
-kmp(str, match) (模式串, 匹配串)
-if(kmp(str, match)) <判断>

注意:如果要多个模式串匹配一个匹配串，请务必开一个全局nxt数组保证复杂度

