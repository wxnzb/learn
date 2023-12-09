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
