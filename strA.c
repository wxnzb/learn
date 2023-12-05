struct strbuf {
    int len;
    int alloc;
    char *buf;
}
//初始化 sb 结构体，容量为 alloc
void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->buf=(char*)malloc(alloc*sizeof(char));
    if(sb->buf==NULL)
    {
        exit(EXIT_FAILURE);
    }
    sb->len=0;
    sb->alloc=alloc;
};
//将字符串填充到 sb 中，长度为 len, 容量为 alloc
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
   sb->len=len;
   sb->alloc=alloc;
   sb->buf=(char*)str;
}
//   释放 sb 结构体的内存（！！释放缓冲区，而不是整个结构体）
void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
    sb->buf=NULL;
}
