## すぐ忘れるのでdockerfileのメモ

- Dockerfileのビルド  
  1. Dockerfileのあるディレクトリまで移動  
  1. docker build -t tagName .

- コンテナの時刻がずれる  
pcがスリープとか電源切れる？とホストとコンテナの時間がずれる  
そうなると`apt update`した時に`~ is not valid yet ~`的なエラーを吐く  
解決方法は管理者権限でpowershell開いて下記コマンドを実行してWSLを再起動  
`net stop LxssManager`  
`net start LxssManager`  
