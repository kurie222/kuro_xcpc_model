#include<bits/stdc++.h>
using namespace std;
#define ll long long 
int T;
struct SAM {
	//edited by piaoyun from some other's code 
	//必须#define int long long 
 
	static const int MAXN=1000010,MAXS=28;
 
    int tot=1,last=1,link[MAXN << 1],ch[MAXN << 1][MAXS],len[MAXN << 1],endpos[MAXN << 1];
	//总点数tot，点的index属于[1-tot]，空串/根为1 
	//last为上一次插入的点
	//link为点的parent树父节点 / 最长 出现位置与自己不同 的后缀
	//ch[n][s] 指节点n末尾加字符s所转移到的点
	//len指该节点的串的 最长长度，注意到 最短长度 等于 len[link[n]] + 1 即父节点最长 + 1
	//endpos[n] 参考get_endpos()的注释 
    //可以不用define int ll 注意空间复杂度
	void clear(){
        for(int i = 0; i <= tot; i++){
            link[i] = len[i] = endpos[i] = 0;
            for(int k = 0; k < MAXS; k++) ch[i][k] = 0;
        }
        tot=1;last=1;
    }
 
    //延长一个字符，通常为[1-26] 
    void extend(int w){
        int p=++tot,x=last,r,q;
        endpos[p]=1;
        for(len[last=p]=len[x]+1; x&&!ch[x][w]; x=link[x]) ch[x][w]=p;
        if(!x)link[p]=1;
        else if(len[x]+1==len[q=ch[x][w]]) link[p]=q;
        else {
            link[r=++tot]=link[q];
            memcpy(ch[r],ch[q],sizeof ch[r]);
			//ch[r] = ch[q]; 修改成map时使用
            len[r]=len[x]+1;
            link[p]=link[q]=r;
            for(; x&&ch[x][w]==q; x=link[x])ch[x][w]=r;
        }
    }
 
    //*注意vector占用的空间 
    vector<int> p[MAXN << 1]; //建立parent树，以便从上到下dfs 
    void dfs(int u){
    	int v;
    	for(int i=0;i<p[u].size();i++){
        	v=p[u][i];
        	dfs(v);
        	endpos[u]+=endpos[v];
   		}
	}
 
    //注意！在使用该方法前，endpos[]代表每个点作为“终结点”的次数
	//使用该方法后，endpos[]指在串中出现总次数，即原数组的子树求和
    void get_endpos(){
    	for(int i = 1;i <= tot; i++) p[i].clear();
    	for(int i = 2;i <= tot; i++){
        	p[link[i]].push_back(i); //建立parent树，以便从上到下dfs 
   		}
   		dfs(1);
   		for(int i = 1;i <= tot; i++) p[i].clear();
	}
 
 
    //*在您不确定是否有抄写错误时再使用该方法 
    //*必须在输入任何数据前自检，此前的数据会被清空 
    static const int STC = 998244353;
    void self_test(){
		clear();
		for(int i = 1;i <= 1000; i++) extend(i * i % 26 + 1);
		int tmp = 107 * last + 301 * tot;
		for(int i = 1;i <= tot; i++){
			tmp = (tmp * 33 + link[i] * 101 + len[i] * 97) % STC;
			for(int k = 1; k < MAXS; k++) tmp = (tmp + k * ch[i][k]) % STC;
		}
		assert("stage 1" && tmp == 393281314); // stage1 : 检查建树是否正确
		tmp = 0;
		get_endpos();
		for(int i = 1;i <= tot; i++) tmp = (tmp * 33 + endpos[i]) % STC;
		assert("stage 2" && tmp == 178417668); // stage2 : 检查endpos计算是否正确，如果您修改了endpos[]的含义则会报错
		cout<<"Self Test Passed.Remember to delete this function's use."<<endl;
		clear();
	}
 
	//调试时可调用 
	void debug_print(){
		for(int i = 1;i <= tot; i++){
			cout<<"node:"<<i<<" father:"<<link[i]<<" endpos:"<<endpos[i]<<" len:"<<len[i]<<endl;
		}
	} 
 
	ll solve(){
		//在这里输入你自己的解题逻辑
		ll ans = 0;
		get_endpos();
		for(int i = 1;i <= tot; i++) if(endpos[i] >= 2) ans = max(ans,(ll)endpos[i] * len[i]);
		return ans;
	}
}sam;
 
 struct SAM2
 //map版
{
    // edited by piaoyun from some other's code
    // 必须#define int long long

    static const int MAXN = 100000, MAXS = 28;

    int tot = 1, last = 1, link[MAXN << 1], len[MAXN << 1], endpos[MAXN << 1];
    map<int, int> ch[MAXN << 1];
    // 总点数tot，点的index属于[1-tot]，空串/根为1
    // last为上一次插入的点
    // link为点的parent树父节点 / 最长 出现位置与自己不同 的后缀
    // ch[n][s] 指节点n末尾加字符s所转移到的点
    // len指该节点的串的 最长长度，注意到 最短长度 等于 len[link[n]] + 1 即父节点最长 + 1
    // endpos[n] 参考get_endpos()的注释
    void clear()
    {
        for (int i = 0; i <= tot; i++)
        {
            link[i] = len[i] = endpos[i] = 0;
            ch[i].clear();
        }
        tot = 1;
        last = 1;
    }

    // 延长一个字符，通常为[1-26]
    void extend(int w)
    {
        int p = ++tot, x = last, r, q;
        endpos[p] = 1;
        for (len[last = p] = len[x] + 1; x && !ch[x].contains(w); x = link[x])
            ch[x][w] = p;
        if (!x)
            link[p] = 1;
        else if (len[x] + 1 == len[q = ch[x][w]])
            link[p] = q;
        else
        {
            link[r = ++tot] = link[q];
            ch[r] = ch[q];
            len[r] = len[x] + 1;
            link[p] = link[q] = r;
            for (; x && ch[x][w] == q; x = link[x])
                ch[x][w] = r;
        }
    }

    //*注意vector占用的空间
    vector<int> p[MAXN << 1]; // 建立parent树，以便从上到下dfs
    void dfs(int u)
    {
        int v;
        for (int i = 0; i < p[u].size(); i++)
        {
            v = p[u][i];
            dfs(v);
            endpos[u] += endpos[v];
        }
    }

    // 注意！在使用该方法前，endpos[]代表每个点作为“终结点”的次数
    // 使用该方法后，endpos[]指在串中出现总次数，即原数组的子树求和
    void get_endpos()
    {
        for (int i = 1; i <= tot; i++)
            p[i].clear();
        for (int i = 2; i <= tot; i++)
        {
            p[link[i]].push_back(i); // 建立parent树，以便从上到下dfs
        }
        dfs(1);
        for (int i = 1; i <= tot; i++)
            p[i].clear();
    }

    //*在您不确定是否有抄写错误时再使用该方法
    //*必须在输入任何数据前自检，此前的数据会被清空
    static const int STC = 998244353;
    void self_test()
    {
        clear();
        for (int i = 1; i <= 1000; i++)
            extend(i * i % 26 + 1);
        int tmp = 107 * last + 301 * tot;
        for (int i = 1; i <= tot; i++)
        {
            tmp = (tmp * 33 + link[i] * 101 + len[i] * 97) % STC;
            for (int k = 1; k < MAXS; k++)
                tmp = (tmp + k * ch[i][k]) % STC;
        }
        assert("stage 1" && tmp == 393281314); // stage1 : 检查建树是否正确
        tmp = 0;
        get_endpos();
        for (int i = 1; i <= tot; i++)
            tmp = (tmp * 33 + endpos[i]) % STC;
        assert("stage 2" && tmp == 178417668); // stage2 : 检查endpos计算是否正确，如果您修改了endpos[]的含义则会报错
        cout << "Self Test Passed.Remember to delete this function's use." << endl;
        clear();
    }

    // 调试时可调用
    void debug_print()
    {
        for (int i = 1; i <= tot; i++)
        {
            cout << "node:" << i << " father:" << link[i] << " endpos:" << endpos[i] << " len:" << len[i] << endl;
        }
    }

    ll solve()
    {
        // 在这里输入你自己的解题逻辑
        ll ans = 0;
        get_endpos();
        for (int i = 1; i <= tot; i++)
            if (endpos[i] >= 2)
                ans = max(ans, (ll)endpos[i] * len[i]);
        return ans;
    }
} sam;
string tmp;
 
void prepare() {
	//sam.self_test();
    cin>>tmp;
    sam.clear();
    for(int i = 0; i < tmp.size(); i++) sam.extend(tmp[i]-'a'+1);
    cout<<sam.solve();
}
 
signed main() {
    T=1;
    while(T--) {
        prepare();
    }
    return 0;
}