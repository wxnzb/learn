//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(sb->alloc<sb->len+1+extra)
    sb->alloc=sb->len+1+extra;
    sb->buf=(char*)realloc(sb->buf,sb->alloc*sizeof(char));
    if(sb->buf==NULL)
    {
        exit(EXIT_FAILURE);
    
    }
}
//向 sb 追加长度为 len 的数据 data
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    strbuf_grow(sb,len);
    // strcat(sb->buf,(char*)data);不对！！
    for(int i=0;i<len;i++)
    {
        sb->buf[sb->len+i]=((char *)data)[i];
    }
    sb->buf[sb->len+len]='\0';
    sb->len=sb->len+len;
}
//向 sb 追加一个字符 
void strbuf_addch(struct strbuf *sb, int c)
{
        strbuf_grow(sb,1);
        sb->buf[sb->len]=(char)c;
        sb->buf[sb->len+1]='\0';
        sb->len=sb->len+1;
}
//向 sb 追加一个字符串 s
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    int n=strlen(s);
    strbuf_grow(sb,n);
    // strcat(sb->buf,s);为啥我想出的第一个过不了！！
    for(int i=0;i<n;i++)
    sb->buf[sb->len+i]=s[i];
    sb->buf[sb->len+n]='\0';
    sb->len=sb->len+n;
}
//向一个 sb 追加另一个 strbuf的数据
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    int n=strlen(sb2->buf);
     strbuf_grow(sb,n);
     for(int i=0;i<n;i++)
    sb->buf[sb->len+i]=sb2->buf[i];
    sb->buf[sb->len+n]='\0';
    sb->len=sb->len+n;
}
//设置 sb 的长度 len
void strbuf_setlen(struct strbuf *sb, size_t len)
{
    sb->len=len;
    strbuf_grow(sb,len+1);
    sb->buf[len]='\0';
}
//7.计算 sb 目前仍可以向后追加的字符串长度
size_t strbuf_avail(const struct strbuf *sb)
{
    int n=sb->alloc-sb->len-1;
    return n;
}

