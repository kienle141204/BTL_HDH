#include <stdio.h>
#include <limits.h>

// Hàm kiểm tra xem trang đang vào có tồn tại trong khung không
int checkHit(int incomingPage, int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        if (incomingPage == queue[i])
            return 1; // Page hit
    }
    return 0; // Page miss
}

// Hàm in trạng thái hiện tại của khung trang
void printFrame(int queue[], int occupied) {
    for (int i = 0; i < occupied; i++)
        printf("%d\t\t\t", queue[i]);
}

int main() {
    // Mảng đại diện cho các yêu cầu trang vào
    int incomingStream[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]); // Số lượng trang vào
    int frames = 3; // Số lượng khung trang
    int queue[n]; // Mảng để giữ các trang trong khung
    int distance[n]; // Mảng để giữ khoảng cách cho tính toán LRU
    int occupied = 0; // Số lượng khung đang được sử dụng
    int pagefault = 0; // Bộ đếm lỗi trang

    // In tiêu đề cho kết quả đầu ra
    printf("Trang\t Khung1 \t Khung2 \t Khung3\n");

    // Xử lý từng yêu cầu trang vào
    for (int i = 0; i < n; i++) {
        printf("%d:  \t\t", incomingStream[i]);

        // Kiểm tra xem trang vào có trúng không
        if (checkHit(incomingStream[i], queue, occupied)) {
            printFrame(queue, occupied); // In trạng thái khung hiện tại nếu trúng
        } else if (occupied < frames) {
            // Nếu có khung trống, thêm trang vào khung
            queue[occupied] = incomingStream[i];
            pagefault++; // Tăng số lượng lỗi trang
            occupied++; // Tăng số lượng khung đang sử dụng

            printFrame(queue, occupied); // In trạng thái khung hiện tại
        } else {
            // Nếu khung đầy, cần thay thế trang bằng LRU
            int max = INT_MIN; // Khởi tạo khoảng cách lớn nhất
            int index = 0; // Chỉ số của trang sẽ bị thay thế

            // Tính toán khoảng cách LRU cho từng trang trong khung
            for (int j = 0; j < frames; j++) {
                distance[j] = 0; // Đặt lại khoảng cách cho khung hiện tại
                // Duyệt ngược mảng trang vào để tìm lần cuối xuất hiện của trang trong khung
                for (int k = i - 1; k >= 0; k--) {
                    ++distance[j];
                    if (queue[j] == incomingStream[k])
                        break; // Dừng lại khi tìm thấy trang
                }

                // Tìm trang có khoảng cách lớn nhất (LRU)
                if (distance[j] > max) {
                    max = distance[j];
                    index = j; // Chỉ số của trang LRU
                }
            }

            // Thay thế trang LRU bằng trang đang vào
            queue[index] = incomingStream[i];
            printFrame(queue, occupied); // In trạng thái khung hiện tại
            pagefault++; // Tăng số lượng lỗi trang
        }

        printf("\n"); // Chuyển sang dòng mới cho yêu cầu trang vào tiếp theo
    }

    // In tổng số lỗi trang
    printf("Lỗi trang: %d", pagefault);

    return 0;
}
