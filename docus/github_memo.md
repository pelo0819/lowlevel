## すぐ忘れるのでgithubのメモ

- ssh key(秘密鍵、公開鍵)を作成  
 1. GitBashを起動(たぶんある)  
 1. `.ssh`フォルダを作成  
  `mkdir ~/.ssh`  
 1. 秘密鍵、公開鍵を作成  
  下記コマンドを実行すると`.ssh`にid_ras、id_rsa.pubを作成される  
  `ssh-keygen -t rsa -b 4096 -C "hoge@example.com" -f ~/.ssh/id_rsa`  
  `ssh-keygen`だけの方が良いかも
 1. githubに公開鍵を設置  
  githubにログイン、右上のアイコンの`Settings`を選択  
  `SSH and GPG keys`を選択  
  `New SSH key`を選択し、id_rsa.pubの中身をkeyにコピペ  
  `Add SSH kye`を選択  
  passphrase入れるとなぜか次のステップでエラー

- githubとsource treeをssh連携  
 1. 「ツール」タブのオプションを選択  
 1. 「認証」タブからgithubアカウントを登録  
 1. 「プロトコル」をSSHに変更  
 1. Pageantからid_rsa.ppkをadd  

 - アクセストークン使った方がよいかも  
 参考urlの3つ目  

- コマンド
1. プルしたいとき  
 `git pull origin [name]`  

2. remoteのブランチをチェックアウトしたいとき  
 `git fetch origin [branch]`  
 `git merge origin/[branch]`

- 参考url  
https://qiita.com/reflet/items/5c6ba6e29fe8436c3185  
https://qiita.com/reflet/items/4f7b5c4a312bc27df10e  
https://qiita.com/_mkt_/items/689b49bb9b58239f6165

  