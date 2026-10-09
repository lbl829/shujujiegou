def hello(name="World"):
    """打招呼函数"""
    return f"Hello {name}!"

if __name__ == "__main__":
    # 循环打印
    for i in range(3):
        msg = hello()
        print(f"第{i+1}次输出：{msg}")
    # 自定义名字
    print(hello("Python"))