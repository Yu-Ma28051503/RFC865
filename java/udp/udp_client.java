package udp;

import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class udp_client {
    public static void main(String[] args) {
        InetAddress serverIP = null;
        int port = 0;
        DatagramSocket socket = null;
        byte[] buffer = new byte[512];
        int len = 0;
        DatagramPacket data = null;

        try {
            /* 1. 接続したいサーバーのIPアドレスとポート番号 */
            serverIP = InetAddress.getByAddress(new byte[]{127,0,0,1});
            port = 17;

            /* 2. ソケット作成 */
            socket = new DatagramSocket();

            /* 3. リクエスト送信(サーバに空文字を送る) */
            byte[] requestData = new byte[1]; // 空のデータ
            DatagramPacket requestPacket = new DatagramPacket(requestData, requestData.length, serverIP, port);
            socket.send(requestPacket);

            /* 4. サーバから名言を取得 */
            data = new DatagramPacket(buffer, buffer.length);
            socket.receive(data);
            len = data.getLength();
            System.out.println(new String(data.getData(), 0, len));
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            /* 接続を遮断する */
            if (socket != null) {
                socket.close();
            }
        }
    }
}
