1.打开终端，创建一个文件夹，git init,git clone 你的仓库，eg:https://github.com/wxnzb/learngit
2.进入github,点你的图像，点settings
3.点ssh and gpg keys,点new ssh key
4.title,随便起一个，key,打开终端，执行ssh-keygen -t ed25519 -C "your_email@example.com",问你沙都点enter,然后会生成一个公钥和siyao,vim /home/sweet/.ssh/id_ed25519.pub，查看你的公钥，然后复制张贴
5.git remote set-url origin git@github.com:wxnzb/learngit.git，执行完这一步就ok了
