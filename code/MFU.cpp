#include <bits/stdc++.h>
using namespace std;

// Đếm số lần lỗi trang
int pageFaults(int n, int c, int pages[]) {
    // Khởi tạo biến đếm bằng 0
    int count = 0;
    // Để lưu trữ các phần tử trong bộ nhớ có kích thước c
    vector<int> v;
    // Để lưu trữ tần suất xuất hiện của các trang
    unordered_map<int, int> mp;
    
    for (int i = 0; i < n; i++) {
        // Kiểm tra xem phần tử có trong bộ nhớ hay không
        auto it = find(v.begin(), v.end(), pages[i]);
        // Nếu phần tử không có trong bộ nhớ
        if (it == v.end()) {
            // Nếu bộ nhớ đầy
            if (v.size() == c) {
                // Tìm trang có tần suất xuất hiện cao nhất để thay thế
                int maxFrequency = INT_MIN;
                int replacePage;
                for (auto page : v) {
                    if (mp[page] > maxFrequency) {
                        maxFrequency = mp[page];
                        replacePage = page;
                    }
                }
                // Xóa trang có tần suất xuất hiện cao nhất
                v.erase(remove(v.begin(), v.end(), replacePage), v.end());
                // Xóa tần suất xuất hiện của trang đó trong map
                mp.erase(replacePage);
            }
            // Thêm phần tử mới vào cuối bộ nhớ
            v.push_back(pages[i]);
            // Tăng tần suất xuất hiện của nó
            mp[pages[i]]++;
            // Tăng biến đếm
            count++;
        } else {
            // Nếu phần tử có trong bộ nhớ
            // Tăng tần suất xuất hiện của nó
            mp[pages[i]]++;
        }
    }
    // Trả về tổng số lần lỗi trang
    return count;
}

// Chương trình chính để kiểm tra hàm pageFaults
int main() {
    int pages[] = { 1, 2, 3, 4, 2, 1, 5 };
    int n = 7, c = 3;
    cout << "Page Faults = " << pageFaults(n, c, pages) << endl;
    cout << "Page Hits = " << n - pageFaults(n, c, pages);
    return 0;
}
