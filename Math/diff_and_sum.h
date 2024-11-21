//use 1-n
//diff
vector<int> diff(maxn);
void diff_init(vector<int> &ori)
{
    diff.resize(ori.size()+10);
    diff[1]=ori[1];
    for(int i=2;i<ori.size();i++)
    {
        diff[i]=ori[i]-ori[i-1];
    }
    return;
}
//[l,r]
void add(int l,int r,int val)
{
    diff[l]+=val;
    diff[r+1]-=val;
}
void find(int target)
{
    int sum=0;
    for(int i=1;i<diff.size()&&i<=target;i++)
    {
        sum+=diff[i];
        //now sum is the current value of ori[i]
        //you can do anything on it
    }
    return;
}
//sum
vector<int> summ(maxn);
void summ_init(vector<int> &ori)
{
    summ.resize(ori.size()+10);
    for(int i=1;i<ori.size();i++)
    {
        summ[i]=summ[i-1]+ori[i];
    }
    return;
}
long long search(int l,int r)
{
    return summ[r]-summ[l-1];
}