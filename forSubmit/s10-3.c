int sum(int a[], int n, int (*function)(int)){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += (*function)(a[i]);
    }
    return sum;
}