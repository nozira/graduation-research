from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

# 認証を行う
gauth = GoogleAuth()
gauth.CommandLineAuth(GoogleAuth())

 # Google Driveのオブジェクトを得る --- (*1)
drive = GoogleDrive(gauth)

 # 画像ファイルをアップロード --- (*2)
f = drive.CreateFile({
    'title': 't.txt',
    'mimeType': 'txt'})
f.SetContentFile(r'./0/out/t.txt')
f.Upload()

 # アップロード結果を表示 --- (*3)
print(f['title'], f['id'])