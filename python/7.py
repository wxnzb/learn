def is_palindrome(s):
    # 去除非字母和数字字符，并转换为小写
    clean_s = ''.join(c.lower() for c in s if c.isalnum())
    return clean_s == clean_s[::-1]

# 读取输入
input_str = input().strip()

# 判断是否为回文字符串
if is_palindrome(input_str):
    print("yes")
else:
    print("no")

