## すぐ忘れるのでapache2のメモ

- apache2の起動

- DocumentRootの変更  
`/etc/apache2/sites-available/000-default.conf`の`DocumentRoot`を変更

- urlにipアドレスのみを指定した場合に任意のファイルが表示するためには  
  1. ステップ1
`/etc/apache2/apache2.conf`の`AllowOverride None`を`AllowOverrideAll`に変更  
これで下記の`.htaccess`が有効になる
  2. ステップ2  
`/var/www`の直下に`.htaccess`を置く  
`.htaccess`に`DirectoryIndex first.php`を追記、ここで`first.php`は表示したいファイル  

- `http://example.com/list`を指定した時、`http://example.com/index.php/list`と解釈するようにする  
  1. ステップ1  
  `/var/www/php/.htaccess`を修正する  
  参考URL  
  `https://abhp.net/net/NET_htaccess_850000.html`
  2. [QSA,L]について  
  QSAは、クエリーをつける
  Lは終了