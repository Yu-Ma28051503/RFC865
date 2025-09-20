/* 引用: https://qiita.com/syouekiko/items/a7fe7ecd9790041da31c */
package tcp;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;

public class tcp_client {
    public static void main(String[] args) throws IOException {
        InetAddress serverIp = null;
        int port = 0;
        Socket socket = null;
        InputStream in = null;
        byte[] buffer = new byte[512];
        ByteArrayOutputStream data = new ByteArrayOutputStream();
        int len = 0;

        try {
            /* 1. 接続したいサーバーのIPアドレスとポート番号 */
            serverIp = InetAddress.getByAddress(new byte[]{127,0,0,1});
            port = 17;

            /* 2. コネクション */
            socket = new Socket(serverIp, port);

            /* 4. サーバから名言を取得 */
            in = socket.getInputStream();
            while ((len = in.read(buffer)) != -1) {
                data.write(buffer, 0, len);
            }
            System.out.println(data.toString());

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            /* 接続を遮断する */
            if (socket != null) {
                socket.close();
            }
            if (in != null) {
                in.close();
            }
        }
    }
}
