# pam_nfc_auth

NFCカードを使用したPAM認証モジュール

## 依存関係

- nfc-reader
  - 内部で `/usr/local/bin/nfc-reader --timeout=30 --allow-list-file=/usr/local/etc/allowed-list.txt --user=ユーザー名` を呼び出す

## インストール

### ビルド手順

1. 以下のコマンドを実行してビルドします：

   ```bash
   make
   ```

2. 以下のコマンドでインストールします：

   ```bash
   sudo make install
   ```

### アンインストール

以下のコマンドでアンインストールできます：

```bash
sudo make uninstall
```

### 成果物の削除

以下のコマンドでビルド成果物を削除できます：

```bash
make clean
```

## 設定

### PAMの設定ファイル

例) `/etc/pam.d/common-auth`

```conf
# NFCカードログイン
auth [success=3 default=ignore] pam_nfc_auth.so
```

通常のパスワードログインは `pam_unix.so` を呼ぶのでその前に設定しておく  
success=3 は成功した場合に次の3行をスキップする  
もともと以下のような記述がある場合、これに先駆けて実行することでデフォルトのパスワード認証をスキップできる

```
auth  [success=2 default=ignore]  pam_unix.so nullok
auth  [success=1 default=ignore]  pam_sss.so use_first_pass
auth  requisite     pam_deny.so
```
