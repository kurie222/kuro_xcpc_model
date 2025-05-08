//求1-x的前缀异或
auto pre = [&](int x)
    {
        if (x % 4 == 0)
        {
            return (x);
        }
        else if (x % 4 == 1)
        {
            return (1ll);
        }
        else if (x % 4 == 2)
        {
            return ((x + 1));
        }
        rt 0ll;
    };