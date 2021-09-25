## すぐ忘れるのでsudoのメモ

- sbinとbinの違い  
 1. sbinは、rootとユーザが実行できるコマンド  
 2. binは、rootしか実行できないので、sudoで実行することになる

- インストール  
 `apt install -y sudo`  

- sudoersで設定    
 `/etc/sudoers`にどのユーザがどのコマンドを実行できるのかが設定されている  
 sudoersを編集する場合は、`visudo`で実行すること(`vi`ではダメ)  
 `visudo`は、タイプミス、設定ミスがあった時に教えてくれる、かつ、保存できない  

- sudoersの設定例  
 `pelo ALL=(ALL:ALL) /sbin/service apache2 restart , /sbin/service apache2 stop`  
 上記でユーザpeloは、apache2をリスタート、ストップができる(しかできない)   
