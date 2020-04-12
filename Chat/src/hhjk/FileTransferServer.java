package hhjk;

import java.io.DataInputStream;  
import java.io.File;  
import java.io.FileOutputStream;  
import java.math.RoundingMode;  
import java.net.ServerSocket;  
import java.net.Socket;  
import java.text.DecimalFormat;  
  

public class FileTransferServer extends ServerSocket {  
  
    private static final int SERVER_PORT = 8899; // ����˶˿�  
  
    private static DecimalFormat df = null;  
  
    static {  
        // �������ָ�ʽ������һλ��ЧС��  
        df = new DecimalFormat("#0.0");  
        df.setRoundingMode(RoundingMode.HALF_UP);  
        df.setMinimumFractionDigits(1);  
        df.setMaximumFractionDigits(1);  
    }  
  
    public FileTransferServer() throws Exception {  
        super(SERVER_PORT);  
    }  
  
    /** 
     * ʹ���̴߳���ÿ���ͻ��˴�����ļ� 
     * @throws Exception 
     */  
    public void load() throws Exception {  
        while (true) {  
            // server���Խ�������Socket����������server��accept����������ʽ��  
            Socket socket = this.accept();  
            // ÿ���յ�һ��Socket�ͽ���һ���µ��߳���������  
            new Thread(new Task(socket)).start();  
        }  
    }  
  
    /** 
     * ����ͻ��˴���������ļ��߳��� 
     */  
    class Task implements Runnable {  
  
        private Socket socket;  
  
        private DataInputStream dis;  
  
        private FileOutputStream fos;  
  
        public Task(Socket socket) {  
            this.socket = socket;  
        }  
  
        @Override  
        public void run() {  
            try {  
                dis = new DataInputStream(socket.getInputStream());  
  
                // �ļ����ͳ���  
                String fileName = dis.readUTF();  
                long fileLength = dis.readLong();  
                File directory = new File("121321");  
                if(!directory.exists()) {  
                    directory.mkdir();  
                }  
                File file = new File(directory.getAbsolutePath() + File.separatorChar + fileName);  
                fos = new FileOutputStream(file);  
  
                // ��ʼ�����ļ�  
                byte[] bytes = new byte[1024];  
                int length = 0;  
                while((length = dis.read(bytes, 0, bytes.length)) != -1) {  
                    fos.write(bytes, 0, length);  
                    fos.flush();  
                }  
                System.out.println("======== �ļ����ճɹ� [File Name��" + fileName + "] [Size��" + getFormatFileSize(fileLength) + "] ========");  
            } catch (Exception e) {  
                e.printStackTrace();  
            } finally {  
                try {  
                    if(fos != null)  
                        fos.close();  
                    if(dis != null)  
                        dis.close();  
                    socket.close();  
                } catch (Exception e) {}  
            }  
        }  
    }  
  
    /** 
     * ��ʽ���ļ���С 
     */  
    private String getFormatFileSize(long length) {  
        double size = ((double) length) / (1 << 30);  
        if(size >= 1) {  
            return df.format(size) + "GB";  
        }  
        size = ((double) length) / (1 << 20);  
        if(size >= 1) {  
            return df.format(size) + "MB";  
        }  
        size = ((double) length) / (1 << 10);  
        if(size >= 1) {  
            return df.format(size) + "KB";  
        }  
        return length + "B";  
    }  
  
}  

