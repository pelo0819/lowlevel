## すぐ忘れるのでlaravelのメモ

- Versionの確認  
`php artisan -V`を実行  
ただし、ディレクトリを`artisan`があるところまで移動  

- ルート設定  
ver8.0からルート設定が少し違くなったらしい  
とりあえず、名前空間を明示的に教えてあげればよい  
8.0より前  
`Route::get('/', 'HelloController@index');`  
8.0より後  
`Route::get('/', 'App\Http\Controllers\HelloController@index');`

- `/`以外のuriにアクセスできない場合  
`/etc/apache2/apache2.conf`の制限をとりあえずAllにする  
`a2enmod rewrite`してapache2再起動`service apache2 restart`    
