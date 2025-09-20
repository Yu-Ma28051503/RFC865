/* 引用: https://qiita.com/syouekiko/items/a7fe7ecd9790041da31c */
package tcp;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.time.LocalDate;

public class tcp_server {
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
        ServerSocket serverSocket = null;
        Socket socket = null;
        OutputStream out = null;
        

        try {
            /* 1. 接続を受け付けるポート設定 */
            serverSocket = new ServerSocket(17);

            while (true) {
                /* 2. 接続準備 */
                socket = serverSocket.accept();
                System.out.println("接続されました: " + socket.getInetAddress());

                /* 3. クライアントへ名言を送信 */
                try {
                    out = socket.getOutputStream();
                    String quote = "Quote of the Day:\n" + getDailyQuote() + "\r\n";
                    out.write(quote.getBytes(StandardCharsets.UTF_8));
                    out.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    out.close();
                    socket.close();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
