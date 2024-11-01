int l = 1, r = *max_element(all(c));
    while (l < r - 1)
    {
        int mid1 = (l + r) >> 1;
        int mid2 = (mid1 - 1);
        int mid3 = (mid1 + 1);

        int sum1 = 0, sum2 = 0;
        for (auto i : c)
        {
            sum1 += cnt(i, mid2);
            sum2 += cnt(i, mid3);
        }
        sum1 *= b;
        sum2 *= b;
        sum1 -= (mid2 - 1) * x;
        sum2 -= (mid3 - 1) * x;
        if (sum1 > sum2)
        {
            r = mid1;
        }
        else
            l = mid1;
    }