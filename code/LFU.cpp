#include <bits/stdc++.h>
#define TASK "dfuc"
#define FOR(i,x,y) for(int i = x; i <= y ; i ++)
#define FORT(i,x,y) for(int i = x; i < y ; i ++)
#define FORD(i,x,y) for(int i = x; i >= y ; i --)
#define clean(x, val) memset(x, val, sizeof(x))
#define F first
#define S second
#define pii pair<int,int>
#define ll long long
#define db double
#define pb push_back
#define endl "\n"
#define yes cout << "Yes" << "\n"
#define no  cout << "No" << "\n"
#define all(x) (x).begin(), (x).end()
#define resized(x) (x).resize(unique(all(x)) - (x).begin())
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std ;
// Doan Dai Phuc 20224890
/* Đếm số lần lỗi trang */
int pageFaults(int n, int c, int pages[])
{
    // Khởi tạo biến đếm bằng 0
    int count = 0;

    // Để lưu các phần tử trong bộ nhớ có kích thước c
    vector<int> v;
    int i;
    for (i = 0; i <= n - 1; i++) {

        // Tìm xem phần tử có trong bộ nhớ hay không
        auto it = find(v.begin(), v.end(), pages[i]);

        // Nếu phần tử không có trong bộ nhớ
        if (it == v.end()) {

            // Nếu bộ nhớ đầy
            if (v.size() == c) {

                // Xóa phần tử đầu tiên
                // Vì đó là phần tử ít được sử dụng nhất
                v.erase(v.begin());
            }

            // Thêm phần tử mới vào bộ nhớ
            v.push_back(pages[i]);

            // Tăng biến đếm
            count++;
        }
        else {

            // Nếu phần tử có trong bộ nhớ
            // Xóa phần tử đó
            // Và thêm nó vào cuối vì nó là
            // phần tử được sử dụng gần đây nhất
            v.erase(it);
            v.push_back(pages[i]);
        }
    }

    // Trả về tổng số lỗi trang
    return count;
}

/* Chương trình chính để kiểm tra hàm pageFaults */
int main()
{

    int pages[] = { 1, 2, 1, 4, 2, 3, 5 };
    int n = 7, c = 3;

    cout << "Loi trang = " << pageFaults(n, c, pages);
    return 0;
}
