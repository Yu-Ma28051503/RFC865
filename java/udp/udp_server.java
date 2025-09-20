package udp;

import java.time.LocalDate;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class udp_server {
        /* 名言集 */
    private static final String[] quotes = {
        "The only way to do great work is to love what you do. - Steve Jobs",
        "Success is not the key to happiness. Happiness is the key to success. - Albert Schweitzer",
        "In the middle of every difficulty lies opportunity. - Albert Einstein",
        "The best way to predict the future is to create it. - Peter Drucker",
        "Your time is limited, so don't waste it living someone else's life. - Steve Jobs"
    };

    /* 乱数で明言を決定 */
    private static String getQuote() {
        return quotes[(int)(Math.random() * quotes.length)];
    }

    private static LocalDate lastDate = LocalDate.now();
    private static String curQuote = getQuote();

    /* 日付が変わっているか確認 */
    private static String getDailyQuote() {
        LocalDate today = LocalDate.now();
        if (!today.equals(lastDate)) {
            lastDate = today;
            curQuote = getQuote();
        }
        return curQuote;
    }
    
    public static void main(String[] args) {
        DatagramSocket socket = null;
        byte[] buffer = new byte[512];
        int port = 17;
        DatagramPacket packet = null;

        try {
            /* 1. 接続を受け付けるポート設定 */
            socket = new DatagramSocket(port);
            System.out.println("UDPサーバーがポート " + port + " で起動しました。");

            while (true) {
                /* 2. クライアントからの接続準備 */
                packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                System.out.println("接続されました: " + packet.getAddress());

                /* 3. クライアントへ名言を送信 */
                String quote = "Quote of the Day:\n" + getDailyQuote() + "\r\n";
                byte[] data = quote.getBytes("UTF-8");
                DatagramPacket sendPacket = new DatagramPacket(data, data.length, packet.getAddress(), packet.getPort());
                socket.send(sendPacket);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            /* 接続を遮断する */
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        }
    }
}
