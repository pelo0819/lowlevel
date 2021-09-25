## すぐ忘れるのでlinuxコマンドのメモ

- ユーザの追加  
 useradd user_name

- ユーザの削除  
 userdel user_name 

- ユーザの一覧表示  
 car /etc/passwd  

- ユーザが所属するグループの変更  
 usermod -G user_name dst_group  

- ユーザがどのグループに所属しているか  
 groups user_name

- グループの一覧表示  
 cat /etc/group  

- グループに誰が所属しているか  
 getent group group_name

- ユーザをグループから削除  
 deluser user_name group_name  

- グループそのものを削除  
 groupdel group_name  
 誰かがグループに所属していても供せ定期にグループを削除したいときは、  
 groupdel -f group_name  

- ユーザにグループを追加  
 gpasswd -a user_name group_name