import indydcp_client as client
import indy_program_maker as JsonProgramComponent
import threading

robot_ip = "192.168.215.123"
robot_name = "NRMK-Indy7"
indy = client.IndyDCPClient(robot_ip, robot_name)

indy.connect() # 로봇 연결

def status():
    robot_status = indy.get_robot_status()
    print(robot_status) # {'ready': 1, 'emergency': 0, 'collision': 0, 'error': 0, 'busy': 0, 'movedone': 0, 'home': 0, 'zero': 0, 'resetting': 0, 'teaching': 0, 'direct_teaching': 0}

def pos():
    joint_pos = indy.get_joint_pos()  # [q1, q2, q3, q4, q5, q6]
    task_pos = indy.get_task_pos()  # [x, y, z, u, v, w]
    print(joint_pos, task_pos)

def home():
    indy.go_home()

def zero():
    indy.go_zero()

def read_value():
    print(indy.get_joint_vel())
    print(indy.get_task_vel())
    print(indy.get_control_torque())



indy.disconnect() # 로봇 연결 해제