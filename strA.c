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
