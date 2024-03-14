s=input().strip();
c=input().strip();
a=s.split(str(c.upper()));
a=''.join(a).split(str(c.lower()));
print("result:",''.join(a));
# strip用来去除字符串开头和结尾的空格
# join用来将列表连接成一个新的字符串
# 而 ''表示用 ' '连接
