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
