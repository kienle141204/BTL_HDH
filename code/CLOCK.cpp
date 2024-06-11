#include <stdio.h>
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
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2};
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]); // Số lượng trang vào
    int frames = 3; // Số lượng khung trang
    int queue[frames]; // Mảng để giữ các trang trong khung
    int reference[frames]; // Mảng bit tham chiếu cho các khung
    int occupied = 0; // Số lượng khung đang được sử dụng
    int pagefault = 0; // Bộ đếm lỗi trang
    int pointer = 0; // Con trỏ chỉ vị trí trong vòng tròn Clock

    // Khởi tạo các khung và bit tham chiếu
    for (int i = 0; i < frames; i++) {
        queue[i] = -1;
        reference[i] = 0;
    }
    // In tiêu đề cho kết quả đầu ra
    printf("Trang\t Khung1 \t Khung2 \t Khung3\n");
    // Xử lý từng yêu cầu trang vào
    for (int i = 0; i < n; i++) {
        printf("%d:  \t\t", incomingStream[i]);
        // Kiểm tra xem trang vào có trúng không
        if (checkHit(incomingStream[i], queue, occupied)) {
            // Cập nhật bit tham chiếu cho trang trúng
            for (int j = 0; j < occupied; j++) {
                if (queue[j] == incomingStream[i]) {
                    reference[j] = 1;
                }
            }
            printFrame(queue, occupied); // In trạng thái khung hiện tại nếu trúng
        } else {
            // Nếu khung đầy, cần thay thế trang bằng thuật toán Clock
            while (occupied >= frames && reference[pointer] == 1) {
                reference[pointer] = 0;
                pointer = (pointer + 1) % frames;
            }
            // Thay thế trang tại vị trí con trỏ
            queue[pointer] = incomingStream[i];
            reference[pointer] = 1;
            pointer = (pointer + 1) % frames;
            pagefault++; // Tăng số lượng lỗi trang

            if (occupied < frames) {
                occupied++; // Tăng số lượng khung đang sử dụng
            }
            printFrame(queue, occupied); // In trạng thái khung hiện tại
        }
        printf("\n"); // Chuyển sang dòng mới cho yêu cầu trang vào tiếp theo
    }
    // In tổng số lỗi trang
    printf("Lỗi trang: %d", pagefault);P
    return 0;
}
