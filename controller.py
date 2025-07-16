from controller import Robot, Motor

TIME_STEP = 64

class MyRobotController:
    def __init__(self):
        self.robot = Robot()
        self.timestep = int(self.robot.getBasicTimeStep())

        # Motors (2 bánh xe)motor
        self.left_motor = self.robot.getDevice('left_motor')
        self.right_motor = self.robot.getDevice('right_motor')
        self.left_motor.setPosition(float('inf'))  # chế độ velocity
        self.right_motor.setPosition(float('inf'))

        # Servo motor (giả lập servo bằng motor với giới hạn góc)
        self.servo_head = self.robot.getDevice('head_servo')
        self.servo_right_arm = self.robot.getDevice('right_arm_servo')
        self.servo_left_arm = self.robot.getDevice('left_arm_servo')

        # Giới hạn góc servo (radian) - giả định
        self.servo_head.setPosition(0.0)
        self.servo_right_arm.setPosition(0.0)
        self.servo_left_arm.setPosition(0.0)

        # Khởi tạo các biến joystick/nút
        self.joystick_x = 0
        self.joystick_y = 0
        self.text = ""
        self.head_button = 0
        self.right_arm_pos = 0
        self.left_arm_pos = 0

    def update_inputs(self):
        # TODO: Ở đây bạn nên lấy giá trị thực từ các cảm biến hoặc controller khác
        # Mình giả lập input tĩnh để demo:
        self.joystick_x = 0
        self.joystick_y = 50  # tiến lên
        self.text = "Robot Moving"
        self.head_button = 0.5  # rad
        self.right_arm_pos = 0.3
        self.left_arm_pos = -0.3

    def run(self):
        while self.robot.step(self.timestep) != -1:
            self.update_inputs()

            # Tính toán tốc độ motor dựa trên joystick Y và X (đơn giản)
            speed_left = 0.0
            speed_right = 0.0
            max_speed = 6.28  # rad/s, giả định

            # Map joystick Y - tiến lùi, joystick X - quẹo
            if self.joystick_y > 50:
                speed_left = max_speed * (self.joystick_y / 100.0)
                speed_right = max_speed * (self.joystick_y / 100.0)
            elif self.joystick_y < -50:
                speed_left = max_speed * (self.joystick_y / 100.0)
                speed_right = max_speed * (self.joystick_y / 100.0)
            if self.joystick_x > 50:
                speed_left += max_speed * (self.joystick_x / 100.0)
                speed_right -= max_speed * (self.joystick_x / 100.0)
            elif self.joystick_x < -50:
                speed_left -= max_speed * (abs(self.joystick_x) / 100.0)
                speed_right += max_speed * (abs(self.joystick_x) / 100.0)

            # Giới hạn tốc độ
            speed_left = max(-max_speed, min(max_speed, speed_left))
            speed_right = max(-max_speed, min(max_speed, speed_right))

            # Gán tốc độ motor
            self.left_motor.setVelocity(speed_left)
            self.right_motor.setVelocity(speed_right)

            # Cập nhật servo (góc)
            self.servo_head.setPosition(self.head_button)
            self.servo_right_arm.setPosition(self.right_arm_pos)
            self.servo_left_arm.setPosition(self.left_arm_pos)

            # Hiển thị text trên console thay cho OLED
            print("Display text:", self.text)

if __name__ == "__main__":
    controller = MyRobotController()
    controller.run()
