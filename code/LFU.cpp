#include <bits/stdc++.h>
using namespace std ;
/* Đếm số lần lỗi trang */
int pageFaults(int n, int c, int pages[])
{
    // Khởi tạo biến đếm bằng 0
    int count = 0;
    // Để lưu trữ các phần tử trong bộ nhớ có kích thước c
    vector<int> v;
    // Để lưu trữ tần suất xuất hiện của các trang
    unordered_map<int, int> mp;
    int i;
    for (i = 0; i <= n - 1; i++) {
        // Kiểm tra xem phần tử có trong bộ nhớ hay không
        auto it = find(v.begin(), v.end(), pages[i]);
        // Nếu phần tử không có trong bộ nhớ
        if (it == v.end()) {
            // Nếu bộ nhớ đầy
            if (v.size() == c) {
                // Giảm tần suất xuất hiện
                mp[v[0]]--;
                // Xóa phần tử đầu tiên vì
                // Nó ít được sử dụng nhất
                v.erase(v.begin());
            }
            // Thêm phần tử vào cuối bộ nhớ
            v.push_back(pages[i]);
            // Tăng tần suất xuất hiện của nó
            mp[pages[i]]++;
            // Tăng biến đếm
            count++;
        }
        else {

            // Nếu phần tử có trong bộ nhớ
            // Xóa phần tử đó
            // Và thêm nó vào cuối
            // Tăng tần suất xuất hiện của nó
            mp[pages[i]]++;
            v.erase(it);
            v.push_back(pages[i]);
        }
        // So sánh tần suất xuất hiện với các trang khác
        // bắt đầu từ trang đứng thứ hai từ cuối lên
        int k = v.size() - 2;
        // Sắp xếp các trang dựa trên tần suất xuất hiện
        // Và thời gian chúng xuất hiện
        // nếu tần suất xuất hiện bằng nhau
        // thì trang nào xuất hiện trước sẽ được đặt trước
        while (mp[v[k]] > mp[v[k + 1]] && k > -1) {
            swap(v[k + 1], v[k]);
            k--;
        }
    }
    // Trả về tổng số lần lỗi trang
    return count;
}
/* Chương trình chính để kiểm tra hàm pageFaults */
int main()
{
    int pages[] = { 1, 2, 3, 4, 2, 1, 5 };
    int n = 7, c = 3;
    cout << "Page Faults = " << pageFaults(n, c, pages)
         << endl;
    cout << "Page Hits = " << n - pageFaults(n, c, pages);
    return 0;
}
