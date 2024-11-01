int t[maxn];
int srt(vector<int> &a, int l ,int r){
    if (l == r) return 0;
    int mid = (l + r )>> 1;
    int res = srt(a, l , mid) + srt(a, mid + 1, r);
    int i = l , j = mid + 1, k = 0;
    while (i <= mid && j <= r){
        if (a[i] <= a[j]) t[k++] = a[i++];
        else{
            t[k++] = a[j++];
            res += mid - i + 1;
        }
    }
    while (i <= mid) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    for (int i = 0 , j = l ; j <= r ; i ++ , j ++) a[j] = t[i];
    return res;
}
//1-n index
//如果直接引用调用，会排序数组a