## Widnows環境下のDockerコンテナ(ubuntu)に搭載したMySQLメモ
- DBのテーブルを表示  
`show tables from 'DB名';`

- インストールした後  
`mysql_secure_installation`を実行

- パスワード設定のポリシー表示  
`show variables like 'validate_passward%';`

- パスワード設定のポリシーを変更  
`set global validate_password.policy=low;`

- テーブルのカラム表示  
`show columns from mysql.user;`  

- ユーザー作成  
`create user pelo@192.168.3.4 identified by pass;`  

- テーブル作成  
`mysql> create table testable(  
    -> id int,  
    -> name varchar(255),  
    -> pass char(30)  
    -> );`  

- テーブルにデータを追加  
`insert into TEST_DB.testable values (2, 'kuma', '0819b');`

- ユーザにDBアクセス権限付与  
`grant all privileges on dbname.TEST_DB to pelo@'%';`

- MySQLへのアクセス制御  
/etc/mysql/mysql.conf.d/mysqld.cnf  
の  
`bind-address = 127.0.0.1`  
をコメントアウト

- error.log  
/var/log/mysql/error.log  

- general-log(access log)  
上記アクセス制御と同じフォルダ内の  
general_log_file        = /var/log/mysql/query.log  
general_log             = 1
をコメントアウト解除  

