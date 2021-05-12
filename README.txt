Tankcar

- Cách chơi: Game bắn xe tăng, người chơi sẽ điều khiển 1 xe tăng di chuyển trong một bản đồ và tiêu diệt các xe tăng do máy tính điều khiển. Sử dụng 4 nút WASD để di chuyển và SPACE để bắn.

- Mô tả code:
+ Các đối tượng Player, Enemy, Bullet được đóng gói trong các class.
+ Enemy, Bullet được sinh vô hạn và chứa trong 2 vector.
+ Kiểm tra va chạm từ hình SDL_Rect.
+ Enemy được sinh ra nhanh hơn dựa trên bộ đếm thời gian.

- Điểm yếu:
+ Các Enemy đang sử dụng chung bộ điều khiển di chuyển và bắn đạn nên nhìn rất đồng điệu, không tự nhiên.
+ Cần các yếu tố khác để game hấp dẫn hơn.