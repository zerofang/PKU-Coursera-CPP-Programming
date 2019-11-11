struct CMy_add{
        int& sum;
        CMy_add(int& s) : sum(s){};
        void operator()(int n){
            sum += (n&7);
        }
};