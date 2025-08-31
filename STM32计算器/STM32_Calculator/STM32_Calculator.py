#!python3

def menu():
    print('菜单选择')
    print(f"1、软件延时计算器\n2、输入捕获计算\n3、PWM计算")
    return int(input('_ '))

def delay_calculate(a):
    main_frq = int(input('主频(MHz)：'))
    PSC = int(input('TIM_Prescaler(0~65535)：'))
    ARR = int(input('TIM_Period(0~65535)：'))


def main():
    if(menu() == 1):


if __name__ == '__main__':
    main()