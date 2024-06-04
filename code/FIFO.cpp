#include<bits/stdc++.h> 
using namespace std; 

// Hàm tìm lỗi trang bằng giải thuật FIFO
int pageFaults(int pages[], int n, int capacity) 
{ 
	// Để biểu diễn các trang hiện tại, ta sử dụng một unordered_set
	// để có thể dễ dàng kiểm tra có lỗi trang hay không. 
	unordered_set<int> s; 

	// Queue dùng để lưu trữ các trang cho thuật toán FIFO 
	queue<int> indexes; 

	// Bắt đầu với khởi tạo 
	int page_faults = 0; 
	for (int i=0; i<n; i++) 
	{ 
		// Kiểm tra xem có thể chứa thêm trang không
		if (s.size() < capacity) 
		{ 
			// Đưa nó vào trong set nếu chưa tồn tại
			// Đây là một thể hiện của lỗi trang
			if (s.find(pages[i])==s.end()) 
			{ 
				// Đưa trang hiện tại vào set 
				s.insert(pages[i]); 

				// Tăng biến page_faults
				page_faults++; 

				// Đây trang hiện tại vào hàng chờ
				indexes.push(pages[i]); 
			} 
		} 

		// Nếu set đã đầy thì cần thực hiện thuật toán FIFO
		// Xóa trang đầu tiên của queue trong set và queue
		// và thêm trang hiện tại vào
		else
		{ 
			// Kiểm tra xem trang hiện tại có trong set hay chưa
			if (s.find(pages[i]) == s.end()) 
			{ 
				// Lưu lại trang đầu tiên của queue để sử dụng tìm và xóa trang khỏi set
				int val = indexes.front(); 
				
				// Xóa trang đầu tiên của queue
				indexes.pop(); 

				// Xóa tran đó khỏi set
				s.erase(val); 

				// Thêm trang hiện tại
				s.insert(pages[i]); 

				// Thêm trang hiện tại vào queue
				indexes.push(pages[i]); 

				// Tăng page_faults
				page_faults++; 
			} 
		} 
	} 

	return page_faults; 
} 

int main() 
{ 
	int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; 
	int n = sizeof(pages)/sizeof(pages[0]); 
	int capacity = 4; 
	cout << pageFaults(pages, n, capacity); 
	return 0; 
} 
