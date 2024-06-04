# BÀI TẬP LỚN HỆ ĐIỀU HÀNH


CHỦ ĐỀ XÂY DỰNG CHƯƠNG TRÌNH MINH HỌA CHO THUẬT TOÁN THAY THẾ TRANG 

> Link sản phẩm  :https://kienle141204.github.io/Page-Replacement-Algorithms/




- [BÀI TẬP LỚN HỆ ĐIỀU HÀNH](#bài-tập-lớn-hệ-điều-hành)
  - [I. Tổng quan về Quản lý bộ nhớ trong Hệ điều hành.](#i-tổng-quan-về-quản-lý-bộ-nhớ-trong-hệ-điều-hành)
  - [II. Tổng quan về thuật toán thay thế trang.](#ii-tổng-quan-về-thuật-toán-thay-thế-trang)
    - [Cơ chế hoạt động :](#cơ-chế-hoạt-động-)
    - [Vai trò của thuật toán thay thế trang :](#vai-trò-của-thuật-toán-thay-thế-trang-)
  - [III. Một số thuật toán thay thế phổ biến.](#iii-một-số-thuật-toán-thay-thế-phổ-biến)
    - [1.FIFO -First In First Out .](#1fifo--first-in-first-out-)
      - [1.1 . Khái niệm](#11--khái-niệm)
      - [1.2 . Mô tả thuật toán](#12--mô-tả-thuật-toán)
      - [1.3 .Bất thường Belady](#13-bất-thường-belady)
      - [1.4 . Nhận xét .](#14--nhận-xét-)
    - [2 . OPT - Optimal Page Replacement](#2--opt---optimal-page-replacement)
      - [2.1 . Khái niệm](#21--khái-niệm)
      - [2.2 . Mô tả thuật toán](#22--mô-tả-thuật-toán)
      - [2.3 . Nhận xét](#23--nhận-xét)
    - [3 . LRU - Least Recently Used](#3--lru---least-recently-used)
      - [3.1 . Khái niệm](#31--khái-niệm)
      - [3.2 . Mô tả thuật toán](#32--mô-tả-thuật-toán)
      - [3.3 . Nhận xét](#33--nhận-xét)
    - [4 . LFU - Least Frequently Used](#4--lfu---least-frequently-used)
      - [4.1 . Khái niệm](#41--khái-niệm)
      - [4.2 . Mô tả thuật toán](#42--mô-tả-thuật-toán)
      - [4.3 . Nhận xét](#43--nhận-xét)
    - [5 . NRU - Not Recently Used](#5--nru---not-recently-used)
      - [5.1 .Khái niệm](#51-khái-niệm)
      - [5.2 . Mô tả thuật toán](#52--mô-tả-thuật-toán)
      - [5.3 .Nhận xét](#53-nhận-xét)

## I. Tổng quan về Quản lý bộ nhớ trong Hệ điều hành.

Quản lý bộ nhớ là quá trình kiểm soát và điều phối bộ nhớ chính của máy tính. Nó đảm bảo rằng các khối không gian bộ nhớ được quản lý và phân bổ hợp lý để hệ điều hành (OS), ứng dụng và các tiến trình đang chạy khác có bộ nhớ cần thiết để thực hiện các hoạt động của chúng.

Là một phần của hoạt động này, quản lý bộ nhớ xem xét các giới hạn dung lượng của thiết bị bộ nhớ, giải phóng không gian bộ nhớ khi không còn cần thiết hoặc mở rộng không gian đó thông qua bộ nhớ ảo. Quản lý bộ nhớ cố gắng tối ưu hóa việc sử dụng bộ nhớ để CPU có thể truy cập hiệu quả các lệnh và dữ liệu cần thiết để thực hiện các quy trình khác nhau.

Tại sao lại cần quản lý bộ nhớ :
- Phân bổ và giải phóng bộ nhớ trước và sau khi thực hiện quy trình.
- Để theo dõi không gian bộ nhớ đã sử dụng theo quy trình.
- Để giảm thiểu các vấn đề phân mảnh .
- Để sử dụng hợp lý bộ nhớ chính.
- Để duy trì tính toàn vẹn dữ liệu trong khi thực hiện quá trình.

## II. Tổng quan về thuật toán thay thế trang.

Thuật toán thay thế trang (page replacement algorithm) là một phương pháp được sử dụng trong quản lý bộ nhớ ảo để xác định trang nào trong bộ nhớ chính sẽ được thay thế khi cần tải một trang mới vào nhưng không còn đủ không gian.

**Lỗi trang:** Lỗi trang xảy ra khi một chương trình đang chạy truy cập vào trang bộ nhớ được ánh xạ vào không gian địa chỉ ảo nhưng không được tải vào bộ nhớ vật lý. Vì bộ nhớ vật lý thực tế nhỏ hơn nhiều so với bộ nhớ ảo nên sẽ xảy ra lỗi trang. Trong trường hợp xảy ra lỗi trang, Hệ điều hành có thể phải thay thế một trong các trang hiện có bằng trang mới cần thiết. Các thuật toán thay thế trang khác nhau đề xuất những cách khác nhau để quyết định trang nào cần thay thế. Mục tiêu của tất cả các thuật toán là giảm số lượng lỗi trang. 

### Cơ chế hoạt động :
- **1.Phát hiện thiếu trang:** Khi một tiến trình yêu cầu một trang không có trong bộ nhớ chính, một sự kiện gọi là thiếu trang (page fault) xảy ra.
- **2.Tìm trang thay thế:** Hệ điều hành phải chọn một trang hiện có trong bộ nhớ chính để thay thế bằng trang mới. Đây là lúc thuật toán thay thế trang được sử dụng.
- **3.Tải trang mới:** Trang mới được tải vào vị trí của trang đã bị thay thế trong bộ nhớ chính.
- **4.Cập nhật bảng trang:** Bảng trang (page table) được cập nhật để phản ánh các thay đổi về vị trí của các trang.

### Vai trò của thuật toán thay thế trang : 
- **Tối ưu hóa hiệu suất hệ thống :**

    Thuật toán thay thế trang giúp giảm thiểu số lượng lỗi trang, từ đó giảm thời gian cần thiết để truy xuất dữ liệu từ bộ nhớ thứ cấp và cải thiện hiệu suất hệ thống. Bằng cách giữ các trang thường xuyên được truy cập trong bộ nhớ, các thuật toán này giúp CPU truy cập nhanh chóng vào dữ liệu và mã lệnh, tăng tốc độ thực thi của chương trình.
- **Quản lý hiệu quả tài nguyên bộ nhớ :**

    Các thuật toán thay thế trang đảm bảo rằng bộ nhớ vật lý được sử dụng một cách hiệu quả nhất. Chúng giải phóng không gian bộ nhớ bằng cách thay thế các trang không còn cần thiết hoặc ít được sử dụng, từ đó tối ưu hóa việc sử dụng bộ nhớ và tránh lãng phí tài nguyên.  

- **Đảm bảo tính liên tục của chương trình :**

    Bằng cách quản lý bộ nhớ một cách thông minh, các thuật toán thay thế trang giúp duy trì luồng công việc liên tục mà không gây gián đoạn cho người dùng hoặc chương trình. Điều này đặc biệt quan trọng trong môi trường đa nhiệm, nơi nhiều tiến trình cần truy cập bộ nhớ đồng thời.

- **Cân bằng giữa tốc độ và tài nguyên :**

    Việc lựa chọn chiến lược thay thế trang phù hợp giúp cân bằng giữa tốc độ truy cập và việc sử dụng tài nguyên. Các thuật toán khác nhau như FIFO, LRU, LFU, và Clock cung cấp các phương pháp khác nhau để đạt được sự cân bằng này, tối ưu hóa hiệu suất theo các điều kiện và yêu cầu cụ thể của hệ thống.

    
Thuật toán thay thế trang đóng vai trò then chốt trong việc quản lý bộ nhớ của hệ điều hành, giúp tối ưu hóa hiệu suất, quản lý tài nguyên hiệu quả, duy trì tính liên tục của chương trình, cân bằng giữa tốc độ và tài nguyên, và hỗ trợ các tính năng nâng cao của hệ điều hành. Việc lựa chọn và triển khai đúng thuật toán thay thế trang là một yếu tố quan trọng để đảm bảo hệ thống hoạt động mượt mà và hiệu quả.


## III. Một số thuật toán thay thế phổ biến.
### 1.FIFO -First In First Out .

#### 1.1 . Khái niệm

Đây là thuật toán thay thế trang đơn giản nhất. Trong thuật toán này, hệ điều hành sẽ theo dõi tất cả các trang trong bộ nhớ dưới dạng một hàng đợi, trang cũ nhất sẽ nằm ở đầu hàng đợi. Khi cần thay thế một trang, trang ở đầu hàng đợi sẽ được chọn để loại bỏ.

#### 1.2 . Mô tả thuật toán 

Đầu vào :
>P = Là một mảng các tham chiều tới các trang đầu vào<br>
>N = Tổng số trang<br>
>C = Sức chứa của bộ nhớ<br>

Đầu ra :
>PF = Tổng số trang lỗi (page faults)

**Mã giả**
````
START
FUNCTION pageFaults(pages[], n, capacity)
    SET s AS unordered_set
    SET indexes AS queue
    SET page_faults AS 0
    FOR i FROM 0 TO n-1 DO
        IF size of s < capacity THEN
            IF pages[i] is not in s THEN
                INSERT pages[i] INTO s
                INCREMENT page_faults BY 1
                PUSH pages[i] INTO indexes
            ENDIF
        ELSE
            IF pages[i] is not in s THEN
                SET val AS indexes.front()
                POP the front element from indexes
                REMOVE val FROM s
                INSERT pages[i] INTO s
                PUSH pages[i] INTO indexes
                INCREMENT page_faults BY 1
            ENDIF
        ENDIF
    ENDFOR
    RETURN page_faults
ENDFUNCTION

FUNCTION main()
    SET pages AS {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}
    SET n AS size of pages
    SET capacity AS 4
    OUTPUT pageFaults(pages, n, capacity)
ENDFUNCTION

````

**Code C++**
```cpp
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

```
**Ví dụ :**
> Input : 0, 2, 1, 6, 4, 0, 1, 0, 3, 1, 2, 1

![](image/fifo.png)

> Page faults = 9

#### 1.3 .Bất thường Belady

Sự bất thường Belady, còn được gọi là "Belady's anomaly," là một hiện tượng đặc biệt trong hệ thống quản lý bộ nhớ của máy tính, cụ thể là trong các thuật toán thay thế trang (page replacement algorithms). Hiện tượng này được đặt tên theo Laszlo Belady, người đã phát hiện ra nó vào năm 1969.

Trong một số trường hợp của thuật toán thay thế trang FIFO (First-In, First-Out), khi tăng kích thước của bộ nhớ đệm (cache) thì số lượng lỗi trang (page faults) lại tăng lên thay vì giảm đi như mong đợi. Điều này đi ngược lại trực giác, vì người ta thường cho rằng việc có nhiều bộ nhớ đệm hơn sẽ giúp giảm số lỗi trang.

**Bất thường Belady trên thuật toán FIFO**

Giả sử một hệ thống không có trang nào được tải lên và sử dụng thuật toán thay thế trang FIFO. Xem sét chuỗi tham chiếu trang sau:

> Input : 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5

Trường hợp 1: Nếu hệ thống bao gồm 3 khung trang. Thuật toán FIFO sẽ thực hiện và trả về kết quả là 9 trang lỗi (page fault).

![](image/belady1.png)

Trường hợp 2: Nếu hệ thống gồm có 4 khung trang, với chuỗi tham chiếu trang trên, thuật toán FIFO sẽ thực hiện và trả về kết quả gồm có 10 trang lỗi.

![](image/belady2.png)

**Làm thế nào để loại bỏ bất thường Belady:**

Bất thường Belady có thể được loại bỏ bằng cách sử dụng các thuật toán dựa trên ngăn xếp. Chúng không bao giờ gặp phải Sự bất thường Belady vì các loại thuật toán này gán một mức độ ưu tiên cho một trang (để thay thế) mà không phụ thuộc vào số lượng khung trang. Các ví dụ về chính sách này bao gồm Thuật toán Tối ưu (Optimal), LRU và LFU. Ngoài ra, các thuật toán này còn có một đặc tính tốt cho việc mô phỏng, đó là tỷ lệ lỗi (hoặc tỷ lệ trúng) có thể được tính toán cho bất kỳ số lượng khung trang nào chỉ với một lần duyệt qua chuỗi tham chiếu.

#### 1.4 . Nhận xét .

**Ưu điểm :**
- **Đơn giản và dễ triển khai:** Thuật toán FIFO rất dễ hiểu và dễ triển khai. Nó chỉ yêu cầu duy trì một hàng đợi để theo dõi thứ tự các trang được nạp vào bộ nhớ.
- **Hiệu suất chấp nhận được trong một số trường hợp:** Trong một số tình huống nhất định, đặc biệt là khi các trang có xu hướng được truy cập theo thứ tự nạp vào, FIFO có thể hoạt động khá tốt.

**Nhược điểm :**
- **Sự bất thường Belady:** Một trong những nhược điểm lớn nhất của FIFO là sự bất thường Belady, khi tăng số lượng khung trang (frames) có thể dẫn đến việc tăng số lượng lỗi trang thay vì giảm. Điều này làm cho FIFO không phải là lựa chọn tối ưu trong nhiều trường hợp.
- **Thiếu tính hiệu quả:** FIFO không xem xét tần suất hoặc thời điểm truy cập các trang. Nó có thể thay thế một trang quan trọng vừa được truy cập nhiều lần, dẫn đến hiệu suất thấp hơn so với các thuật toán khác như LRU (Least Recently Used) hoặc LFU (Least Frequently Used).
- **Không tối ưu:** FIFO không đảm bảo rằng trang được thay thế là trang ít quan trọng nhất cho các hoạt động tương lai. Điều này có thể dẫn đến việc thay thế các trang cần thiết và làm

### 2 . OPT - Optimal Page Replacement

#### 2.1 . Khái niệm 

Thuật toán OPT (Optimal Page Replacement) là một thuật toán thay thế trang lý tưởng được sử dụng trong quản lý bộ nhớ ảo của hệ điều hành. Mục tiêu của thuật toán này là giảm thiểu số lần xảy ra lỗi trang (page fault) bằng cách thay thế trang sẽ không được sử dụng trong thời gian dài nhất trong tương lai. Tuy nhiên, việc thực hiện thuật toán này trong thực tế gặp nhiều khó khăn do yêu cầu về thông tin truy cập trong tương lai, vốn không thể biết trước được.

#### 2.2 . Mô tả thuật toán 

Thuật toán OPT hoạt động theo các bước sau:

- Giám sát lịch sử truy cập trang: Theo dõi các trang đang có trong bộ nhớ và lịch sử truy cập của chúng.<br>
- Dự đoán tương lai: Đối với mỗi trang hiện đang có trong bộ nhớ, tính toán khoảng cách đến lần truy cập tiếp theo của trang đó.<br>
- Chọn trang cần thay thế: Trang có khoảng cách xa nhất đến lần truy cập tiếp theo sẽ được chọn để thay thế, vì nó sẽ không cần sử dụng trong thời gian dài nhất.


**Mã giả**
````
START
FUNCTION isInMemory(frames[], numFrames, page)
    FOR i FROM 0 TO numFrames-1 DO
        IF frames[i] EQUALS page THEN
            RETURN true
        ENDIF
    ENDFOR
    RETURN false
ENDFUNCTION

FUNCTION findReplacementIndex(frames[], numFrames, referenceString[], currentReferenceIndex, totalReferences)
    SET farthest AS currentReferenceIndex
    SET indexToReplace AS -1
    FOR i FROM 0 TO numFrames-1 DO
        FOR j FROM currentReferenceIndex TO totalReferences-1 DO
            IF frames[i] EQUALS referenceString[j] THEN
                IF j > farthest THEN
                    SET farthest AS j
                    SET indexToReplace AS i
                ENDIF
                BREAK
            ENDIF
        ENDFOR
        IF j EQUALS totalReferences THEN
            RETURN i
        ENDIF
    ENDFOR
    RETURN (indexToReplace EQUALS -1) ? 0 : indexToReplace
ENDFUNCTION

FUNCTION main()
    SET numFrames, numReferences AS integer
    SET frames[MAX_FRAMES], referenceString[MAX_REFERENCES] AS arrays of integers

    PRINT "Nhap so khung trang: "
    READ numFrames

    PRINT "Nhap so trang tham chieu: "
    READ numReferences

    PRINT "Nhap chuoi trang tham chieu: "
    FOR i FROM 0 TO numReferences-1 DO
        READ referenceString[i]
    ENDFOR

    FOR i FROM 0 TO numFrames-1 DO
        frames[i] = -1
    ENDFOR

    SET pageFaults AS 0
    FOR i FROM 0 TO numReferences-1 DO
        SET currentPage AS referenceString[i]
        IF NOT isInMemory(frames, numFrames, currentPage) THEN
            SET replacementIndex AS findReplacementIndex(frames, numFrames, referenceString, i + 1, numReferences)
            frames[replacementIndex] = currentPage
            INCREMENT pageFaults BY 1
            PRINT "Khung trang sau khi truy cap trang ", currentPage, ": "
            FOR j FROM 0 TO numFrames-1 DO
                IF frames[j] EQUALS -1 THEN
                    PRINT "- "
                ELSE
                    PRINT frames[j], " "
                ENDIF
            ENDFOR
            PRINT "\n"
        ENDIF
    ENDFOR

    PRINT "Tong so loi trang: ", pageFaults, "\n"
ENDFUNCTION

````
**Code C**
```cpp
#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 30

// Ham kiem tra xem trang co trong bo nho khong
bool isInMemory(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Ham tim vi tri cua trang can thay the theo thuat toan OPT
int findReplacementIndex(int frames[], int numFrames, int referenceString[], int currentReferenceIndex, int totalReferences) {
    int farthest = currentReferenceIndex;
    int indexToReplace = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentReferenceIndex; j < totalReferences; j++) {
            if (frames[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }

        // Neu khong tim thay trang trong chuoi tham chieu con lai
        if (j == totalReferences) {
            return i;
        }
    }

    return (indexToReplace == -1) ? 0 : indexToReplace;
}

int main() {
    int numFrames, numReferences;
    int frames[MAX_FRAMES], referenceString[MAX_REFERENCES];

    // Nhap so khung trang
    printf("Nhap so khung trang: ");
    scanf("%d", &numFrames);

    // Nhap chuoi tham chieu trang
    printf("Nhap so trang tham chieu ");
    scanf("%d", &numReferences);

    printf("Nhap chuoi trang tham chieu: ");
    for (int i = 0; i < numReferences; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Khoi tao khung trang
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    int pageFaults = 0;
    for (int i = 0; i < numReferences; i++) {
        int currentPage = referenceString[i];

        // Kiem tra xem trang hien tai da co trong bo nho chua
        if (!isInMemory(frames, numFrames, currentPage)) {
            int replacementIndex = findReplacementIndex(frames, numFrames, referenceString, i + 1, numReferences);
            frames[replacementIndex] = currentPage;
            pageFaults++;

            // In trang thai cua khung trang
            printf("Khung trang sau khi truy cap trang %d: ", currentPage);
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }

    printf("Tong so loi trang: %d\n", pageFaults);

    return 0;
}
```
**Ví dụ :**
> Input : 7,0,1,2,0,3,0,4,2,3

![](image/opt.png)

> Page faults : 6

#### 2.3 . Nhận xét

**Ưu điểm :**
Giảm thiểu số lần xảy ra lỗi trang tối đa có thể.

**Nhược điểm :**
Không thể thực hiện trong thực tế vì không thể biết trước các truy cập trang tương lai.

**Nhận xét thuật toán:** Thuật toán OPT cung cấp một cái nhìn lý tưởng về việc quản lý bộ nhớ ảo, mặc dù không thể thực hiện trong thực tế. Nó giúp các nhà nghiên cứu hiểu rõ hơn về hiệu quả của các thuật toán thay thế trang khác bằng cách cung cấp một chuẩn mực tối ưu để so sánh.


### 3 . LRU - Least Recently Used 

#### 3.1 . Khái niệm 

Là một chiến lược thay thế trang phổ biến hoạt động theo nguyên tắc địa phương tham chiếu. Nó giả định rằng nếu một trang được tham chiếu gần đây thí nó có khả năng được tham chiếu lại trong tương lai gần.

Cách triển khai thuật toán LRU, hệ thống duy trì một danh sách hoặc hàng đợi các trang trong bộ nhớ chính. Khi một trang cần được thay thế, thuật toán sẽ chọn trang có thời gian truy cập sớm nhất, cho biết rằng trang đó ít được sử dụng gần đây nhất. Trang đã chọn này sau đó sẽ được hoán đổi với trang mới.

#### 3.2 . Mô tả thuật toán 

Các hệ điều hành thường triển khai thuật toán LRU để quản lý bộ nhớ ảo và bộ đệm đĩa. Thuật toán LRU có thể được triển khai bằng nhiều cấu trúc dữ liệu khác nhau như danh sách liên kết, bảng băm hoặc hàng đợi ưu tiên.

Các cấu trúc dữ liệu này cho phép theo dõi hiệu quả thời gian truy cập trang và tạo điều kiện thuận lợi cho việc lựa chọn trang ít được sử dụng gần đây nhất để thay thế.

**Mã giả**
````
START
FUNCTION checkHit(incomingPage, queue[], occupied)
    FOR i FROM 0 TO occupied-1 DO
        IF incomingPage EQUALS queue[i] THEN
            RETURN 1 // Trang trúng
        ENDIF
    ENDFOR
    RETURN 0 // Trang không trúng
ENDFUNCTION

FUNCTION printFrame(queue[], occupied)
    FOR i FROM 0 TO occupied-1 DO
        PRINT queue[i], "\t\t\t"
    ENDFOR
ENDFUNCTION

FUNCTION main()
    SET incomingStream[] AS array of integers
    SET n AS integer
    SET frames AS integer
    SET queue[] AS array of integers
    SET distance[] AS array of integers
    SET occupied, pagefault AS integers

    // Nhập dãy yêu cầu trang và số lượng khung trang
    // (Đã giả sử giá trị của MAX_FRAMES và MAX_REFERENCES)
    SET incomingStream[] AS {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3}
    SET n AS size of incomingStream
    SET frames AS 3

    // Khởi tạo mảng khung trang và các biến đếm
    SET queue[] AS array of size frames
    SET distance[] AS array of size frames
    SET occupied AS 0
    SET pagefault AS 0

    // In tiêu đề cho kết quả đầu ra
    PRINT "Trang\t Khung1 \t Khung2 \t Khung3"

    // Xử lý từng yêu cầu trang vào
    FOR i FROM 0 TO n-1 DO
        PRINT incomingStream[i], ":  \t\t"

        // Kiểm tra trang vào có trúng không
        IF NOT checkHit(incomingStream[i], queue, occupied) THEN
            IF occupied < frames THEN
                // Nếu còn khung trống, thêm trang vào
                queue[occupied] = incomingStream[i]
                INCREMENT pagefault BY 1 // Tăng số lỗi trang
                INCREMENT occupied BY 1 // Tăng số khung trang sử dụng
                printFrame(queue, occupied) // In trạng thái khung
            ELSE
                // Nếu khung đầy, thực hiện thay thế trang bằng LRU
                SET max AS INT_MIN // Khởi tạo khoảng cách lớn nhất
                SET index AS 0 // Chỉ số của trang sẽ bị thay thế

                // Tính toán khoảng cách LRU cho từng trang trong khung
                FOR j FROM 0 TO frames-1 DO
                    SET distance[j] AS 0 // Đặt lại khoảng cách cho khung hiện tại
                    // Duyệt ngược mảng trang vào để tìm lần cuối xuất hiện của trang trong khung
                    FOR k FROM i - 1 DOWNTO 0 DO
                        INCREMENT distance[j] BY 1
                        IF queue[j] EQUALS incomingStream[k] THEN
                            BREAK // Dừng lại khi tìm thấy trang
                        ENDIF
                    ENDFOR

                    // Tìm trang có khoảng cách lớn nhất (LRU)
                    IF distance[j] > max THEN
                        SET max AS distance[j]
                        SET index AS j // Chỉ số của trang LRU
                    ENDIF
                ENDFOR

                // Thay thế trang LRU bằng trang đang vào
                SET queue[index] AS incomingStream[i]
                printFrame(queue, occupied) // In trạng thái khung
                INCREMENT pagefault BY 1 // Tăng số lỗi trang
            ENDIF
        ELSE
            printFrame(queue, occupied) // In trạng thái khung nếu trúng
        ENDIF

        PRINT "\n" // Chuyển sang dòng mới cho yêu cầu trang vào tiếp theo
    ENDFOR

    // In tổng số lỗi trang
    PRINT "Lỗi trang: ", pagefault
ENDFUNCTION
````
**Code C**
```cpp
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
```
**Ví dụ :**
> Input :

![]()

> Page faults = 

#### 3.3 . Nhận xét 

**Ưu điểm :**
- 	Không có sự bất thường của Belady
- 	Dễ dàng lựa chọn trang bị lỗi, lâu không được sử dụng
-   **Hiệu suất tốt:** LRU được thiết kế để thay thế trang không được truy cập trong thời gian dài nhất. Nó được coi là một thuật toán “thông minh” vì nó tính đến lịch sử sử dụng của các trang và có thể dẫn đến ít lỗi trang hơn và thời gian phản hồi ứng dụng nhanh hơn.
-   **Sử dụng bộ nhớ hiệu quả:** LRU dẫn đến việc sử dụng bộ nhớ hiệu quả vì nó thay thế trang không được sử dụng trong thời gian dài nhất. Điều này có nghĩa là các trang hiếm khi được sử dụng hoặc không quan trọng sẽ có nhiều khả năng bị hoán đổi, giải phóng bộ nhớ cho các trang quan trọng hơn.


**Nhược điểm :**
- Nó yêu cầu Cấu trúc dữ liệu bổ sung để được thực hiện.
- Hỗ trợ phần cứng cao.
- Trong LRU việc phát hiện lỗi rất khó so với các thuật toán khác.
- Nó có khả năng chấp nhận hạn chế.
- LRU rất tốn kém để vận hành.


### 4 . LFU - Least Frequently Used
#### 4.1 . Khái niệm 

Thuật toán LFU (Least Frequently Used) là một kỹ thuật quản lý bộ nhớ đệm (cache) hoặc thay thế trang (page replacement) được sử dụng để quyết định trang nào cần được thay thế khi bộ nhớ đệm đầy. LRU sử dụng khái niệm phân trang để quản lý bộ nhớ. Một thuật toán thay thế trang là cần thiết để quyết định trang nào cần được thay thế khi có trang mới được đưa vào. Mỗi khi một trang mới được tham chiếu và không có trong bộ nhớ, lỗi trang (page fault) xảy ra và Hệ Điều Hành thay thế một trong các trang hiện có bằng trang mới cần thiết. Thuật toán LFU thay thế trang ít được truy cập nhất. Cụ thể, nó theo dõi tần suất sử dụng của từng trang và khi cần thay thế trang, nó chọn trang có số lần truy cập thấp nhất.

#### 4.2 . Mô tả thuật toán 

Thuật toán LFU (Least Frequently Used) là một thuật toán quản lý bộ nhớ và thay thế trang trong đó trang ít được sử dụng nhất sẽ bị thay thế trước. Thuật toán này theo dõi tần suất sử dụng của các trang và ưu tiên giữ lại các trang được truy cập thường xuyên hơn.

**Mã giả**

````
START
FUNCTION pageFaults(n, c, pages[])
    // Khởi tạo biến đếm số lỗi trang
    SET count TO 0

    // Khởi tạo danh sách lưu các phần tử trong bộ nhớ có kích thước c
    DECLARE v AS empty list

    FOR i FROM 0 TO n-1 DO
        // Tìm xem phần tử có trong bộ nhớ hay không
        SET it TO FIND pages[i] IN v

        // Nếu phần tử không có trong bộ nhớ
        IF it EQUALS end of v THEN
            // Nếu bộ nhớ đầy
            IF size of v EQUALS c THEN
                // Xóa phần tử đầu tiên vì đó là phần tử ít được sử dụng nhất
                REMOVE first element from v
            ENDIF

            // Thêm phần tử mới vào bộ nhớ
            APPEND pages[i] TO v

            // Tăng biến đếm số lỗi trang
            INCREMENT count BY 1
        ELSE
            // Nếu phần tử có trong bộ nhớ
            // Xóa phần tử đó
            REMOVE element it from v
            // Thêm nó vào cuối vì nó là phần tử được sử dụng gần đây nhất
            APPEND pages[i] TO v
        ENDIF
    ENDFOR

    // Trả về tổng số lỗi trang
    RETURN count
ENDFUNCTION

FUNCTION main()
    // Khởi tạo mảng trang
    SET pages TO [1, 2, 1, 4, 2, 3, 5]
    SET n TO 7
    SET c TO 3

    // Gọi hàm pageFaults và in kết quả
    PRINT "Lỗi trang = ", pageFaults(n, c, pages)
ENDFUNCTION
````

**Code C++**

```cpp
#include <bits/stdc++.h>

using namespace std ;
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

```
**Ví dụ :**
> Input : 5 , 3 , 6 , 9 , 6 ,2 , 3 , 5 , 2 , 1 , 3 , 6 , 2 , 6 , 5 , 3 , 6 , 5 , 2 , 1

![](image/lfu.png)

> Page faults = 15


#### 4.3 . Nhận xét 

**Ưu điểm :**

- **Hiệu quả trong môi trường ổn định:** LFU có hiệu quả trong các trường hợp mà các trang được truy cập với tần suất tương đối ổn định theo thời gian.

**Nhược điểm :**

- **Không thích ứng với các thay đổi đột ngột:** LFU có thể không thích ứng tốt với các thay đổi đột ngột trong mẫu truy cập, dẫn đến tình trạng giữ lại các trang cũ không còn cần thiết nữa (được gọi là vấn đề "cache pollution").

- **Chi phí quản lý:** Cần phải duy trì và cập nhật các bộ đếm cho mỗi trang, điều này có thể tăng thêm chi phí tính toán và bộ nhớ.


### 5 . NRU - Not Recently Used
#### 5.1 .Khái niệm 
NRU là một thuật toán được sử dụng trong các hệ điều hành để xác định trang nào sẽ được thay thế trong bộ nhớ khi xảy ra lỗi trang. Thuật toán NRU chia các trang thành bốn loại dựa trên lịch sử sử dụng của chúng. Bốn loại này là:

- Loại 0: Các trang không được tham chiếu và không bị sửa đổi gần đây.
- Loại 1: Các trang không được tham chiếu gần đây nhưng đã bị sửa đổi gần đây.
- Loại 2: Các trang được tham chiếu gần đây nhưng không bị sửa đổi gần đây.
- Loại 3: Các trang được tham chiếu và bị sửa đổi gần đây.

Sử dụng 2 bit là reference bit và modified bit để xác định loại của trang. 
![](image/nru1.png)

Sau khi phân loại, thuật toán sẽ lựa chọn ngẫu nhiên trang thuộc nhóm loại thấp nhất không rỗng để thực hiện thay thế.

#### 5.2 . Mô tả thuật toán 

**Mã giả**
````
````
**Code C**
```cpp
```


#### 5.3 .Nhận xét 

**Ưu điểm :**
- **Đơn giản:** Thuật toán dễ hiểu và dễ triển khai.
- **Hiệu quả tương đối:** Thường hoạt động tốt trong việc giảm số lỗi trang so với các thuật toán cơ bản khác như FIFO.

**Nhược điểm :**
- **Ngẫu nhiên:** Việc chọn trang ngẫu nhiên trong cùng loại có thể không tối ưu.
- **Không hoàn toàn tối ưu:** Không đạt hiệu suất cao như các thuật toán phức tạp hơn (ví dụ: LRU hoặc Optimal).








   
