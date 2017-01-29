#include <iomanip>
#include <iostream>

#include <array>
#include <vector>
using namespace std;

using byte_t = unsigned char;

#if 1

template<typename... Bools>
auto Make(Bools... bools) {
    const vector<bool> b{static_cast<bool>(bools)...};
    vector<byte_t> a(b.size()/8);
    for(auto i=0u; i<a.size(); ++i)
        a[a.size()-i-1] =
                (b[8*i+7] << 7) | (b[8*i+6] << 6) | (b[8*i+5] << 5) | (b[8*i+4] << 4)
              | (b[8*i+3] << 3) | (b[8*i+2] << 2) | (b[8*i+1] << 1) |  b[8*i+0];
    return a;
}

//template<typename... Bools>
//auto Make(Bools... bools) {
//    constexpr auto nBools = sizeof...(bools);
//    const array<bool, nBools> b{static_cast<bool>(bools)...};
//    array<byte_t, nBools/8> a;
//    for(auto i=0u; i<a.size(); ++i)
//        a[a.size()-i-1] =
//                (b[8*i+7] << 7) | (b[8*i+6] << 6) | (b[8*i+5] << 5) | (b[8*i+4] << 4)
//              | (b[8*i+3] << 3) | (b[8*i+2] << 2) | (b[8*i+1] << 1) |  b[8*i+0];
//    return a;
//}

#else

template<size_t N>
void Fill(array<byte_t, N>&, size_t) {}

template<size_t N, typename... Bools>
void Fill(array<byte_t, N>& a,
          size_t i,
          bool b7, bool b6, bool b5, bool b4,
          bool b3, bool b2, bool b1, bool b0,
          Bools... bools) {
    a[N-i] =  (b7 << 7) | (b6 << 6) | (b5 << 5) | (b4 << 4)
            | (b3 << 3) | (b2 << 2) | (b1 << 1) |  b0;
    Fill(a, i-1, bools...);
}

template<typename... Bools>
auto Make(Bools... bools) {
    constexpr auto nBools = sizeof...(bools);
    static_assert(nBools % 8 == 0, "Number of bools must be divisible by 8");
    auto a = array<byte_t, nBools/8>();
    Fill(a, nBools/8, bools...);
    return a;
}

#endif

int main() {
    auto bytepacked = Make(0,1,1,0,
                           1,0,0,1,
                           1,0,0,1,
                           0,1,1,0);
    for(const auto& i : bytepacked)
        cout << setw(2) << setfill('0') << hex << (unsigned)i << " ";
    cout << endl;



//    using p_t = unique_ptr<int>;
//    p_t init[] = {make_unique<int>(1),make_unique<int>(2)};
//    const vector<p_t> ptrs(make_move_iterator(begin(init)),
//                           make_move_iterator(end(init)));
//    for(const auto& p : ptrs)
//      *p *= 2; // constness?!

//    for(const auto& p : ptrs)
//        cout << *p << endl;

}
