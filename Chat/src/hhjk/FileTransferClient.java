package hhjk;

import java.io.DataOutputStream;  
import java.io.File;  
import java.io.FileInputStream;  
import java.net.Socket;  
  
/** 
 * �ļ�����Client��<br> 
 * ����˵���� 
 * 
 * @author �������޵�С�� 
 * @Date 2016��09��01�� 
 * @version 1.0 
 */  
public class FileTransferClient extends Socket {  
  
	public static final String IP_ADDR = "localhost";//��������ַ  
    private static final int SERVER_PORT = 8899; // ����˶˿�  
  
    private Socket client;  
  
    private FileInputStream fis;  
  
    private DataOutputStream dos;  
  
    /** 
     * ���캯��<br/> 
     * ��������������� 
     * @throws Exception 
     */  
    public FileTransferClient() throws Exception {  
        super(IP_ADDR, SERVER_PORT);  
        this.client = this;  
        System.out.println("Cliect[port:" + client.getLocalPort() + "] �ɹ����ӷ����");  
    }  
  
    /** 
     * �����˴����ļ� 
     * @throws Exception 
     */  
    public void sendFile() throws Exception {  
        try {  
            File file = new File("history.txt");  
            if(file.exists()) {  
                fis = new FileInputStream(file);  
                dos = new DataOutputStream(client.getOutputStream());  
  
                // �ļ����ͳ���  
                dos.writeUTF(file.getName());  
                dos.flush();  
                dos.writeLong(file.length());  
                dos.flush();  
  
                // ��ʼ�����ļ�  
                System.out.println("======== ��ʼ�����ļ� ========");  
                byte[] bytes = new byte[1024];  
                int length = 0;  
                long progress = 0;  
                while((length = fis.read(bytes, 0, bytes.length)) != -1) {  
                    dos.write(bytes, 0, length);  
                    dos.flush();  
                    progress += length;  
                    System.out.print("| " + (100*progress/file.length()) + "% |");  
                }  
                System.out.println();  
                System.out.println("======== �ļ�����ɹ� ========");  
            }  
        } catch (Exception e) {  
            e.printStackTrace();  
        } finally {  
            if(fis != null)  
                fis.close();  
            if(dos != null)  
                dos.close();  
            client.close();  
        }  
    }  
  
    /** 
     * ��� 
     * @param args 
     */  
   
  
}  