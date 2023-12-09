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
}}
