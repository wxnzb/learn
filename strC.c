//1.去除 sb 缓冲区左端的所有 空格，tab, '\t'
void strbuf_ltrim(struct strbuf *sb)
{
    int i=0;
    int n=0;
   while(i<sb->len&&isspace((unsigned char)sb->buf[i]))
   {
    if(sb->buf[i]==' '||sb->buf[i]=='\t')
      n++;
      i++;
   }
   for(int j=0;j+n<sb->len;j++)
   sb->buf[j]=sb->buf[j+n];
   sb->len=sb->len-n;
}
//2.去除 sb 缓冲区右端的所有 空格，tab, '\t'
void strbuf_rtrim(struct strbuf *sb)
{
   int i=sb->len-1;
   int n=0;
   while(i>=0&&isspace((unsigned char)sb->buf[i]))
   {
    if(sb->buf[i]==' '||sb->buf[i]=='\t')
     n++;
     i--;
   }
  sb->len=sb->len-n;
}

