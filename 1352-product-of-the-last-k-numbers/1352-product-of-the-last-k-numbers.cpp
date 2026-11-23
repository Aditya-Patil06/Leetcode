class ProductOfNumbers {
private:
    vector<int> pref;      // pref[0] = 1; pref[i] = product of elements since last zero
    int countSinceZero;    // number of elements after the most recent zero

public:
    ProductOfNumbers() {
        pref = {1};
        countSinceZero = 0;
    }

    void add(int num) {
        if (num == 0) {
            // A zero resets all products before it.
            pref = {1};
            countSinceZero = 0;
        } else {
            pref.push_back(pref.back() * num);
            ++countSinceZero;
        }
    }

    int getProduct(int k) {
        // If k reaches back past the most recent zero, the product is 0.
        if (k > countSinceZero) return 0;

        int n = pref.size();
        return pref[n - 1] / pref[n - 1 - k];
    }
};