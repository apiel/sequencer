int between(int val, int minVal, int maxVal) {
    return min(max(val, minVal), maxVal);
}

int getVal(int baseVal, int val, int isInc, unsigned int multi) {
    return isInc ? baseVal + val * multi : val;
}

int getVal(int baseVal, int val, int isInc) {
    return getVal(baseVal, val, isInc, 1);
}

int mod(int n, int m) { return ((n % m) + m) % m; }
