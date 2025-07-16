from controller import Robot, Motor, Keyboard

class MyRobotController:
    def __init__(self):
        self.robot = Robot()
        self.timestep = int(self.robot.getBasicTimeStep())

        # Khởi tạo bàn phím
        self.keyboard = Keyboard()
        self.keyboard.enable(self.timestep)

        # Motors
        self.left_motor = self.robot.getDevice('left_motor')
        self.right_motor = self.robot.getDevice('right_motor')
        self.left_motor.setPosition(float('inf'))
        self.right_motor.setPosition(float('inf'))

        # Servos
        self.servo_head = self.robot.getDevice('head_servo')
        self.servo_right_arm = self.robot.getDevice('right_arm_servo')
        self.servo_left_arm = self.robot.getDevice('left_arm_servo')

        self.servo_head.setPosition(0.0)
        self.servo_right_arm.setPosition(0.0)
        self.servo_left_arm.setPosition(0.0)

        # Trạng thái ban đầu
        self.text = ""
        self.head_angle = 0.0
        self.right_arm_pos = 0.0
        self.left_arm_pos = 0.0

    def run(self):
        max_speed = 6.28

        while self.robot.step(self.timestep) != -1:
            key = self.keyboard.getKey()

            # Reset vận tốc mỗi vòng lặp
            left_speed = 0.0
            right_speed = 0.0

            # Đọc phím và điều khiển
            if key == ord('W'):
                left_speed = max_speed
                right_speed = max_speed
                self.text = "Moving Forward"
            elif key == ord('S'):
                left_speed = -max_speed
                right_speed = -max_speed
                self.text = "Moving Backward"
            elif key == ord('A'):
                left_speed = -0.5 * max_speed
                right_speed = 0.5 * max_speed
                self.text = "Turning Left"
            elif key == ord('D'):
                left_speed = 0.5 * max_speed
                right_speed = -0.5 * max_speed
                self.text = "Turning Right"
            else:
                self.text = "Stopped"

            # Điều khiển servo đầu (Q/E)
            if key == ord('Q'):
                self.head_angle += 0.05
            elif key == ord('E'):
                self.head_angle -= 0.05
            self.head_angle = max(-1.0, min(1.0, self.head_angle))

            # Tay trái (Z/X)
            if key == ord('Z'):
                self.left_arm_pos += 0.05
            elif key == ord('X'):
                self.left_arm_pos -= 0.05
            self.left_arm_pos = max(-1.0, min(1.0, self.left_arm_pos))

            # Tay phải (C/V)
            if key == ord('C'):
                self.right_arm_pos += 0.05
            elif key == ord('V'):
                self.right_arm_pos -= 0.05
            self.right_arm_pos = max(-1.0, min(1.0, self.right_arm_pos))

            # Cập nhật động cơ
            self.left_motor.setVelocity(left_speed)
            self.right_motor.setVelocity(right_speed)

            # Cập nhật servo
            self.servo_head.setPosition(self.head_angle)
            self.servo_right_arm.setPosition(self.right_arm_pos)
            self.servo_left_arm.setPosition(self.left_arm_pos)

            # Hiển thị trạng thái
            print("Display text:", self.text)

if __name__ == "__main__":
    controller = MyRobotController()
    controller.run()
